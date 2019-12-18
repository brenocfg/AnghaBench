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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  minor_t ;
typedef  int /*<<< orphan*/  dsl_dataset_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  dsl_dataset_get_spa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_dataset_user_hold_sync_one_impl (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_onexit_hold_cleanup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 

void
dsl_dataset_user_hold_sync_one(dsl_dataset_t *ds, const char *htag,
    minor_t minor, uint64_t now, dmu_tx_t *tx)
{
	nvlist_t *tmpholds;

	if (minor != 0)
		tmpholds = fnvlist_alloc();
	else
		tmpholds = NULL;
	dsl_dataset_user_hold_sync_one_impl(tmpholds, ds, htag, minor, now, tx);
	dsl_onexit_hold_cleanup(dsl_dataset_get_spa(ds), tmpholds, minor);
}