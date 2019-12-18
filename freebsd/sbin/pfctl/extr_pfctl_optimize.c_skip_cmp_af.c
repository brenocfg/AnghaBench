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
struct pf_rule {scalar_t__ af; } ;

/* Variables and functions */

int
skip_cmp_af(struct pf_rule *a, struct pf_rule *b)
{
	if (a->af != b->af || a->af == 0)
		return (1);
	return (0);
}