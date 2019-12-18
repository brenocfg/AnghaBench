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
 unsigned long AG_PATH_MAX ; 
#define  NUL 128 
 unsigned int strlen (char const*) ; 

__attribute__((used)) static char *
extract_colon_unit(char * pzDir, char const * string, int * p_index)
{
    char * pzDest = pzDir;
    int    ix     = *p_index;

    if (string == NULL)
        return NULL;

    if ((unsigned)ix >= strlen( string ))
        return NULL;

    {
        char const * pzSrc = string + ix;

        while (*pzSrc == ':')  pzSrc++;

        for (;;) {
            char ch = (*(pzDest++) = *(pzSrc++));
            switch (ch) {
            case ':':
                pzDest[-1] = NUL;
                /* FALLTHROUGH */
            case NUL:
                goto copy_done;
            }

            if ((unsigned long)(pzDest - pzDir) >= AG_PATH_MAX)
                break;
        } copy_done:;

        ix = (int)(pzSrc - string);
    }

    if (*pzDir == NUL)
        return NULL;

    *p_index = ix;
    return pzDir;
}