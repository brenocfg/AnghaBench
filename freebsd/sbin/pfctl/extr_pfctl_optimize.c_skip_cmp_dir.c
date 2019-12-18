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
struct pf_rule {scalar_t__ direction; } ;

/* Variables and functions */

int
skip_cmp_dir(struct pf_rule *a, struct pf_rule *b)
{
	if (a->direction == 0 || a->direction != b->direction)
		return (1);
	return (0);
}