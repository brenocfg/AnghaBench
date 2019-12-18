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
 unsigned long UINT_MAX ; 
 scalar_t__ errno ; 
 unsigned long strtoul (char const*,char**,int) ; 

__attribute__((used)) static int
str2number(const char *p, int *portp)
{
	char *ep;
	unsigned long v;

	if (*p == '\0')
		return -1;
	ep = NULL;
	errno = 0;
	v = strtoul(p, &ep, 10);
	if (errno == 0 && ep && *ep == '\0' && v <= UINT_MAX) {
		*portp = v;
		return 0;
	} else
		return -1;
}