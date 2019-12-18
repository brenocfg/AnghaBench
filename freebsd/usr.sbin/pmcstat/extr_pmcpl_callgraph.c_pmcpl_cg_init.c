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
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int PMCSTAT_NHASH ; 
 int /*<<< orphan*/ * pmcstat_cgnode_hash ; 
 scalar_t__ pmcstat_cgnode_hash_count ; 
 int /*<<< orphan*/ * pmcstat_previous_filename_printed ; 

int
pmcpl_cg_init(void)
{
	int i;

	pmcstat_cgnode_hash_count = 0;
	pmcstat_previous_filename_printed = NULL;

	for (i = 0; i < PMCSTAT_NHASH; i++) {
		LIST_INIT(&pmcstat_cgnode_hash[i]);
	}

	return (0);
}