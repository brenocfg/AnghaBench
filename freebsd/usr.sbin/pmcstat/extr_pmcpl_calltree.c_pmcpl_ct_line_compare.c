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
struct pmcpl_ct_line {scalar_t__ ln_sum; } ;

/* Variables and functions */

__attribute__((used)) static int
pmcpl_ct_line_compare(const void *a, const void *b)
{
	const struct pmcpl_ct_line *ct1, *ct2;

	ct1 = (const struct pmcpl_ct_line *) a;
	ct2 = (const struct pmcpl_ct_line *) b;

	/* Sort in reverse order */
	if (ct1->ln_sum < ct2->ln_sum)
		return (1);
	if (ct1->ln_sum > ct2->ln_sum)
		return (-1);
	return (0);
}