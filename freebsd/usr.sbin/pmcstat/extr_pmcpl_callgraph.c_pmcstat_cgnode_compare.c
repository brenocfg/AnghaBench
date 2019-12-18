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
struct pmcstat_cgnode {scalar_t__ pcg_count; } ;

/* Variables and functions */

__attribute__((used)) static int
pmcstat_cgnode_compare(const void *a, const void *b)
{
	const struct pmcstat_cgnode *const *pcg1, *const *pcg2, *cg1, *cg2;

	pcg1 = (const struct pmcstat_cgnode *const *) a;
	cg1 = *pcg1;
	pcg2 = (const struct pmcstat_cgnode *const *) b;
	cg2 = *pcg2;

	/* Sort in reverse order */
	if (cg1->pcg_count < cg2->pcg_count)
		return (1);
	if (cg1->pcg_count > cg2->pcg_count)
		return (-1);
	return (0);
}