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
 int strlen (char const*) ; 

__attribute__((used)) static int ends_with_dirsep(const char *path)
{
    if (*path != '\0')
        path += strlen(path) - 1;
# if defined __VMS
    if (*path == ']' || *path == '>' || *path == ':')
        return 1;
# elif defined _WIN32
    if (*path == '\\')
        return 1;
# endif
    return *path == '/';
}