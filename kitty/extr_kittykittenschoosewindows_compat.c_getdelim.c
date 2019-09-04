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
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 char EOF ; 
 int /*<<< orphan*/  ERANGE ; 
 int SSIZE_MAX ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 char getc (int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (size_t) ; 
 scalar_t__ realloc (char*,size_t) ; 

ssize_t
getdelim(char **lineptr, size_t *n, int delim, FILE *stream) {
    char c, *cur_pos, *new_lineptr;
    size_t new_lineptr_len;

    if (lineptr == NULL || n == NULL || stream == NULL) {
        errno = EINVAL;
        return -1;
    }

    if (*lineptr == NULL) {
        *n = 8192; /* init len */
        if ((*lineptr = (char *)malloc(*n)) == NULL) {
            errno = ENOMEM;
            return -1;
        }
    }

    cur_pos = *lineptr;
    for (;;) {
        c = getc(stream);

        if (ferror(stream) || (c == EOF && cur_pos == *lineptr))
            return -1;

        if (c == EOF)
            break;

        if ((*lineptr + *n - cur_pos) < 2) {
            if (SSIZE_MAX / 2 < *n) {
#ifdef EOVERFLOW
                errno = EOVERFLOW;
#else
                errno = ERANGE; /* no EOVERFLOW defined */
#endif
                return -1;
            }
            new_lineptr_len = *n * 2;

            if ((new_lineptr = (char *)realloc(*lineptr, new_lineptr_len)) == NULL) {
                errno = ENOMEM;
                return -1;
            }
            *lineptr = new_lineptr;
            *n = new_lineptr_len;
        }

        *cur_pos++ = c;

        if (c == delim)
            break;
    }

    *cur_pos = '\0';
    return (ssize_t)(cur_pos - *lineptr);
}