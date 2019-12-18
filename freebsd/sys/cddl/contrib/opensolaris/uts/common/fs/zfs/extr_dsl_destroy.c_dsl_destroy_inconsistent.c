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
typedef  int /*<<< orphan*/  objset_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ B_FALSE ; 
 scalar_t__ DS_IS_INCONSISTENT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  dmu_objset_ds (int /*<<< orphan*/ *) ; 
 scalar_t__ dmu_objset_hold (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dmu_objset_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ dsl_dataset_has_resume_receive_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_destroy_head (char const*) ; 

int
dsl_destroy_inconsistent(const char *dsname, void *arg)
{
	objset_t *os;

	if (dmu_objset_hold(dsname, FTAG, &os) == 0) {
		boolean_t need_destroy = DS_IS_INCONSISTENT(dmu_objset_ds(os));

		/*
		 * If the dataset is inconsistent because a resumable receive
		 * has failed, then do not destroy it.
		 */
		if (dsl_dataset_has_resume_receive_state(dmu_objset_ds(os)))
			need_destroy = B_FALSE;

		dmu_objset_rele(os, FTAG);
		if (need_destroy)
			(void) dsl_destroy_head(dsname);
	}
	return (0);
}