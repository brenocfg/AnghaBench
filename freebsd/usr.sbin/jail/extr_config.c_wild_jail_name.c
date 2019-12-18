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
 char* strchr (char const*,char) ; 

int
wild_jail_name(const char *wname)
{
	const char *wc;

	for (wc = strchr(wname, '*'); wc; wc = strchr(wc + 1, '*'))
		if ((wc == wname || wc[-1] == '.') &&
		    (wc[1] == '\0' || wc[1] == '.'))
			return 1;
	return 0;
}