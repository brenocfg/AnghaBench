#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 char* scalloc (int,int) ; 

char *parse_string(const char **walk, bool as_word) {
    const char *beginning = *walk;
    /* Handle quoted strings (or words). */
    if (**walk == '"') {
        beginning++;
        (*walk)++;
        for (; **walk != '\0' && **walk != '"'; (*walk)++)
            if (**walk == '\\' && *(*walk + 1) != '\0')
                (*walk)++;
    } else {
        if (!as_word) {
            /* For a string (starting with 's'), the delimiters are
             * comma (,) and semicolon (;) which introduce a new
             * operation or command, respectively. Also, newlines
             * end a command. */
            while (**walk != ';' && **walk != ',' &&
                   **walk != '\0' && **walk != '\r' &&
                   **walk != '\n')
                (*walk)++;
        } else {
            /* For a word, the delimiters are white space (' ' or
             * '\t'), closing square bracket (]), comma (,) and
             * semicolon (;). */
            while (**walk != ' ' && **walk != '\t' &&
                   **walk != ']' && **walk != ',' &&
                   **walk != ';' && **walk != '\r' &&
                   **walk != '\n' && **walk != '\0')
                (*walk)++;
        }
    }
    if (*walk == beginning)
        return NULL;

    char *str = scalloc(*walk - beginning + 1, 1);
    /* We copy manually to handle escaping of characters. */
    int inpos, outpos;
    for (inpos = 0, outpos = 0;
         inpos < (*walk - beginning);
         inpos++, outpos++) {
        /* We only handle escaped double quotes and backslashes to not break
         * backwards compatibility with people using \w in regular expressions
         * etc. */
        if (beginning[inpos] == '\\' && (beginning[inpos + 1] == '"' || beginning[inpos + 1] == '\\'))
            inpos++;
        str[outpos] = beginning[inpos];
    }

    return str;
}