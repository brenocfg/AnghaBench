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
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 char* strdup (char*) ; 

__attribute__((used)) static char *
canonicalize_pathname( char *path )
{
    int i, start;
    char stub_char, *result;

    /* The result cannot be larger than the input PATH. */
    result = strdup( path );
	if (result == NULL) {
	return NULL;    /* couldn't allocate memory    */
	}
    stub_char = (*path == '/') ? '/' : '.';

    /* Walk along RESULT looking for things to compact. */
    i = 0;
    while (result[i]) {
        while (result[i] != '\0' && result[i] != '/')
            i++;

        start = i++;

        /* If we didn't find any  slashes, then there is nothing left to
         * do.
         */
        if (!result[start])
            break;

        /* Handle multiple `/'s in a row. */
        while (result[i] == '/')
            i++;

#if !defined (apollo)
        if ((start + 1) != i)
#else
        if ((start + 1) != i && (start != 0 || i != 2))
#endif /* apollo */
        {
            strcpy( result + start + 1, result + i );
            i = start + 1;
        }

        /* Handle backquoted `/'. */
        if (start > 0 && result[start - 1] == '\\')
            continue;

        /* Check for trailing `/', and `.' by itself. */
        if ((start && !result[i])
            || (result[i] == '.' && !result[i+1])) {
            result[--i] = '\0';
            break;
        }

        /* Check for `../', `./' or trailing `.' by itself. */
        if (result[i] == '.') {
            /* Handle `./'. */
            if (result[i + 1] == '/') {
                strcpy( result + i, result + i + 1 );
                i = (start < 0) ? 0 : start;
                continue;
            }

            /* Handle `../' or trailing `..' by itself. */
            if (result[i + 1] == '.' &&
                (result[i + 2] == '/' || !result[i + 2])) {
                while (--start > -1 && result[start] != '/')
                    ;
                strcpy( result + start + 1, result + i + 2 );
                i = (start < 0) ? 0 : start;
                continue;
            }
        }
    }

    if (!*result) {
        *result = stub_char;
        result[1] = '\0';
    }

    return result;
}