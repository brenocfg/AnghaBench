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
typedef  scalar_t__ FICL_UNS ;

/* Variables and functions */
 int tolower (char) ; 

int strincmp(char *cp1, char *cp2, FICL_UNS count)
{
    int i = 0;

    for (; 0 < count; ++cp1, ++cp2, --count)
    {
        i = tolower(*cp1) - tolower(*cp2);
        if (i != 0)
            return i;
        else if (*cp1 == '\0')
            return 0;
    }
    return 0;
}