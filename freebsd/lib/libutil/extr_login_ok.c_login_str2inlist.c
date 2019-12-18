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
 scalar_t__ login_strinlist (char const**,char const*,int) ; 

int
login_str2inlist(const char **ttlst, const char *str1, const char *str2, int flags)
{
    int	    rc = 0;

    if (login_strinlist(ttlst, str1, flags))
	rc = 1;
    else if (login_strinlist(ttlst, str2, flags))
	rc = 1;
    return rc;
}