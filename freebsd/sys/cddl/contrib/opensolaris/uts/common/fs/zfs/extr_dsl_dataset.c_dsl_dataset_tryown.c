#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  ds_lock; int /*<<< orphan*/ * ds_owner; TYPE_1__* ds_dir; } ;
typedef  TYPE_2__ dsl_dataset_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_6__ {int /*<<< orphan*/  dd_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DS_IS_INCONSISTENT (TYPE_2__*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  dsl_dataset_long_hold (TYPE_2__*,void*) ; 
 int /*<<< orphan*/  dsl_pool_config_held (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

boolean_t
dsl_dataset_tryown(dsl_dataset_t *ds, void *tag)
{
	boolean_t gotit = FALSE;

	ASSERT(dsl_pool_config_held(ds->ds_dir->dd_pool));
	mutex_enter(&ds->ds_lock);
	if (ds->ds_owner == NULL && !DS_IS_INCONSISTENT(ds)) {
		ds->ds_owner = tag;
		dsl_dataset_long_hold(ds, tag);
		gotit = TRUE;
	}
	mutex_exit(&ds->ds_lock);
	return (gotit);
}