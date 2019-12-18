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
typedef  char const Char ;

/* Variables and functions */

__attribute__((used)) static int
findvv(Char **vv, const char *cp)
{
    for (; vv && *vv; vv++) {
	size_t i;
	for (i = 0; (*vv)[i] && (*vv)[i] == cp[i]; i++)
	    continue;
	if ((*vv)[i] == '\0' && cp[i] == '\0')
	    return 1;
    }
    return 0;
}