#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  os_spa; TYPE_2__* os_dsl_dataset; } ;
typedef  TYPE_1__ objset_t ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_5__ {int /*<<< orphan*/  ds_dir; } ;
typedef  TYPE_2__ dsl_dataset_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  dmu_tx_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_dir_willuse_space (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_pool_dirty_space (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_get_worst_case_asize (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
dmu_objset_willuse_space(objset_t *os, int64_t space, dmu_tx_t *tx)
{
	dsl_dataset_t *ds = os->os_dsl_dataset;
	int64_t aspace = spa_get_worst_case_asize(os->os_spa, space);

	if (ds != NULL) {
		dsl_dir_willuse_space(ds->ds_dir, aspace, tx);
		dsl_pool_dirty_space(dmu_tx_pool(tx), space, tx);
	}
}