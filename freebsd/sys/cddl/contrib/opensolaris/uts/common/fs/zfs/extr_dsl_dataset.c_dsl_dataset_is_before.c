#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  dsl_pool_t ;
struct TYPE_11__ {scalar_t__ ds_object; TYPE_3__* ds_dir; scalar_t__ ds_is_snapshot; } ;
typedef  TYPE_1__ dsl_dataset_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_14__ {int /*<<< orphan*/  ds_creation_txg; } ;
struct TYPE_13__ {int /*<<< orphan*/ * dd_pool; } ;
struct TYPE_12__ {scalar_t__ dd_origin_obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  FTAG ; 
 int dsl_dataset_hold_obj (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,TYPE_1__**) ; 
 TYPE_6__* dsl_dataset_phys (TYPE_1__*) ; 
 int /*<<< orphan*/  dsl_dataset_rele (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_dir_is_clone (TYPE_3__*) ; 
 TYPE_2__* dsl_dir_phys (TYPE_3__*) ; 
 int dsl_pool_config_held (int /*<<< orphan*/ *) ; 

boolean_t
dsl_dataset_is_before(dsl_dataset_t *later, dsl_dataset_t *earlier,
    uint64_t earlier_txg)
{
	dsl_pool_t *dp = later->ds_dir->dd_pool;
	int error;
	boolean_t ret;

	ASSERT(dsl_pool_config_held(dp));
	ASSERT(earlier->ds_is_snapshot || earlier_txg != 0);

	if (earlier_txg == 0)
		earlier_txg = dsl_dataset_phys(earlier)->ds_creation_txg;

	if (later->ds_is_snapshot &&
	    earlier_txg >= dsl_dataset_phys(later)->ds_creation_txg)
		return (B_FALSE);

	if (later->ds_dir == earlier->ds_dir)
		return (B_TRUE);
	if (!dsl_dir_is_clone(later->ds_dir))
		return (B_FALSE);

	if (dsl_dir_phys(later->ds_dir)->dd_origin_obj == earlier->ds_object)
		return (B_TRUE);
	dsl_dataset_t *origin;
	error = dsl_dataset_hold_obj(dp,
	    dsl_dir_phys(later->ds_dir)->dd_origin_obj, FTAG, &origin);
	if (error != 0)
		return (B_FALSE);
	ret = dsl_dataset_is_before(origin, earlier, earlier_txg);
	dsl_dataset_rele(origin, FTAG);
	return (ret);
}