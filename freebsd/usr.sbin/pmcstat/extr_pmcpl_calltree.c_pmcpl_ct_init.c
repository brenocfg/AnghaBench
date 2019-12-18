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
 int PMCSTAT_NHASH ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmcpl_ct_callid ; 
 int /*<<< orphan*/  pmcpl_ct_node_allocate () ; 
 int /*<<< orphan*/ * pmcpl_ct_node_hash ; 
 int /*<<< orphan*/  pmcpl_ct_root ; 
 int /*<<< orphan*/  pmcpl_ct_samples_init (int /*<<< orphan*/ *) ; 

int
pmcpl_ct_init(void)
{
	int i;

	pmcpl_ct_root = pmcpl_ct_node_allocate();

	for (i = 0; i < PMCSTAT_NHASH; i++)
		STAILQ_INIT(&pmcpl_ct_node_hash[i]);

	pmcpl_ct_samples_init(&pmcpl_ct_callid);

	return (0);
}