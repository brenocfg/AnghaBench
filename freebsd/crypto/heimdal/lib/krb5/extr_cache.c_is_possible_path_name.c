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
 int FALSE ; 
 int TRUE ; 
 char* strchr (char const*,char) ; 

__attribute__((used)) static int
is_possible_path_name(const char * name)
{
    const char * colon;

    if ((colon = strchr(name, ':')) == NULL)
        return TRUE;

#ifdef _WIN32
    /* <drive letter>:\path\to\cache ? */

    if (colon == name + 1 &&
        strchr(colon + 1, ':') == NULL)
        return TRUE;
#endif

    return FALSE;
}