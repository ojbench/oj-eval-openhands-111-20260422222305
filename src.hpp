#pragma once

#undef strtok

char *strtok(char * __restrict str, const char * __restrict delim);

static inline int __is_delim(char c, const char * __restrict delim) {
    const char *d = delim;
    while (*d) {
        if (*d == c) return 1;
        ++d;
    }
    return 0;
}

char *strtok(char * __restrict str, const char * __restrict delim) {
    static char *next = nullptr;
    if (!delim) return nullptr;

    char *s = str ? str : next;
    if (!s) return nullptr;

    if (*delim == '\0') {
        if (*s == '\0') { next = nullptr; return nullptr; }
        char *token = s;
        while (*s) ++s;
        next = nullptr;
        return token;
    }

    while (*s && __is_delim(*s, delim)) ++s;
    if (*s == '\0') { next = nullptr; return nullptr; }

    char *token = s;
    while (*s) {
        if (__is_delim(*s, delim)) {
            *s = '\0';
            next = s + 1;
            return token;
        }
        ++s;
    }
    next = nullptr;
    return token;
}
