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
 scalar_t__ fnmatch (char const*,char const*,int) ; 

int
login_strinlist(const char **list, char const *str, int flags)
{
    int rc = 0;

    if (str != NULL && *str != '\0') {
	int	i = 0;

	while (rc == 0 && list[i] != NULL)
	    rc = fnmatch(list[i++], str, flags) == 0;
    }
    return rc;
}