#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  obj ;
struct TYPE_8__ {int /*<<< orphan*/  ds_object; TYPE_2__* ds_dir; } ;
typedef  TYPE_3__ dsl_dataset_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
struct TYPE_7__ {TYPE_1__* dd_pool; } ;
struct TYPE_6__ {int /*<<< orphan*/  dp_meta_objset; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  DS_FIELD_REMAP_DEADLIST ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_dataset_zapify (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,scalar_t__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dsl_dataset_set_remap_deadlist_object(dsl_dataset_t *ds, uint64_t obj,
    dmu_tx_t *tx)
{
	ASSERT(obj != 0);
	dsl_dataset_zapify(ds, tx);
	VERIFY0(zap_add(ds->ds_dir->dd_pool->dp_meta_objset, ds->ds_object,
	    DS_FIELD_REMAP_DEADLIST, sizeof (obj), 1, &obj, tx));
}