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
 size_t strlen (char*) ; 

__attribute__((used)) static void
trim_trailing_slash(char * path)
{
    size_t l;

    l = strlen(path);
    while (l > 0 && (path[l - 1] == '/'
#ifdef BACKSLASH_PATH_DELIM
                     || path[l - 1] == '\\'
#endif
               )) {
        path[--l] = '\0';
    }
}