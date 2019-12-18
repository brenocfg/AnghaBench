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
 int /*<<< orphan*/  IS_VALUE_NAME_CHAR (int) ; 
 char NUL ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char const*) ; 
 unsigned int strlen (char const*) ; 

__attribute__((used)) static bool
add_env_val(char * buf, int buf_sz, char const * name)
{
    char * dir_part = buf;

    for (;;) {
        int ch = (int)*++name;
        if (! IS_VALUE_NAME_CHAR(ch))
            break;
        *(dir_part++) = (char)ch;
    }

    if (dir_part == buf)
        return false;

    *dir_part = NUL;

    dir_part = getenv(buf);

    /*
     *  Environment value not found -- skip the home list entry
     */
    if (dir_part == NULL)
        return false;

    if (strlen(dir_part) + 1 + strlen(name) >= (unsigned)buf_sz)
        return false;

    sprintf(buf, "%s%s", dir_part, name);
    return true;
}