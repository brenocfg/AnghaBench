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
 int NS_MAXDNAME ; 
 scalar_t__ ns_makecanon (char const*,char*,int) ; 
 scalar_t__ strcasecmp (char*,char*) ; 

int
ns_samename(const char *a, const char *b) {
	char ta[NS_MAXDNAME], tb[NS_MAXDNAME];

	if (ns_makecanon(a, ta, sizeof ta) < 0 ||
	    ns_makecanon(b, tb, sizeof tb) < 0)
		return (-1);
	if (strcasecmp(ta, tb) == 0)
		return (1);
	else
		return (0);
}