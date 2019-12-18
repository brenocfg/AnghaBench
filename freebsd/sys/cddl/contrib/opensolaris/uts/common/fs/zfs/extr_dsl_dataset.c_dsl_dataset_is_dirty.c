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
struct TYPE_8__ {TYPE_2__* ds_dir; } ;
typedef  TYPE_3__ dsl_dataset_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_7__ {TYPE_1__* dd_pool; } ;
struct TYPE_6__ {int /*<<< orphan*/  dp_dirty_datasets; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int TXG_SIZE ; 
 scalar_t__ txg_list_member (int /*<<< orphan*/ *,TYPE_3__*,int) ; 

boolean_t
dsl_dataset_is_dirty(dsl_dataset_t *ds)
{
	for (int t = 0; t < TXG_SIZE; t++) {
		if (txg_list_member(&ds->ds_dir->dd_pool->dp_dirty_datasets,
		    ds, t))
			return (B_TRUE);
	}
	return (B_FALSE);
}