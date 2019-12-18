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
struct pf_rule {char* ifname; scalar_t__ ifnot; } ;

/* Variables and functions */
 scalar_t__ strcmp (char*,char*) ; 

int
skip_cmp_ifp(struct pf_rule *a, struct pf_rule *b)
{
	if (strcmp(a->ifname, b->ifname) || a->ifname[0] == '\0')
		return (1);
	return (a->ifnot != b->ifnot);
}