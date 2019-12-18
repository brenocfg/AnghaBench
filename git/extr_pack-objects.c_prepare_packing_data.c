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
struct repository {int dummy; } ;
struct packing_data {int /*<<< orphan*/  odb_lock; void* oe_delta_size_limit; void* oe_size_limit; struct repository* repo; } ;

/* Variables and functions */
 unsigned long OE_DELTA_SIZE_BITS ; 
 unsigned int OE_SIZE_BITS ; 
 scalar_t__ git_env_bool (char*,int /*<<< orphan*/ ) ; 
 void* git_env_ulong (char*,unsigned long) ; 
 int /*<<< orphan*/  init_recursive_mutex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepare_in_pack_by_idx (struct packing_data*) ; 

void prepare_packing_data(struct repository *r, struct packing_data *pdata)
{
	pdata->repo = r;

	if (git_env_bool("GIT_TEST_FULL_IN_PACK_ARRAY", 0)) {
		/*
		 * do not initialize in_pack_by_idx[] to force the
		 * slow path in oe_in_pack()
		 */
	} else {
		prepare_in_pack_by_idx(pdata);
	}

	pdata->oe_size_limit = git_env_ulong("GIT_TEST_OE_SIZE",
					     1U << OE_SIZE_BITS);
	pdata->oe_delta_size_limit = git_env_ulong("GIT_TEST_OE_DELTA_SIZE",
						   1UL << OE_DELTA_SIZE_BITS);
	init_recursive_mutex(&pdata->odb_lock);
}