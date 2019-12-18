#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  dsl_pool_t ;
struct TYPE_11__ {TYPE_1__* ds_dir; } ;
typedef  TYPE_2__ dsl_dataset_t ;
struct TYPE_12__ {int /*<<< orphan*/  ds_prev_snap_obj; } ;
struct TYPE_10__ {int /*<<< orphan*/ * dd_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  FTAG ; 
 int dsl_dataset_hold_obj (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__**) ; 
 TYPE_7__* dsl_dataset_phys (TYPE_2__*) ; 
 int /*<<< orphan*/  dsl_dataset_rele (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int dsl_dataset_space_written (TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
dsl_get_written(dsl_dataset_t *ds, uint64_t *written)
{
	dsl_pool_t *dp = ds->ds_dir->dd_pool;
	dsl_dataset_t *prev;
	int err = dsl_dataset_hold_obj(dp,
	    dsl_dataset_phys(ds)->ds_prev_snap_obj, FTAG, &prev);
	if (err == 0) {
		uint64_t comp, uncomp;
		err = dsl_dataset_space_written(prev, ds, written,
		    &comp, &uncomp);
		dsl_dataset_rele(prev, FTAG);
	}
	return (err);
}