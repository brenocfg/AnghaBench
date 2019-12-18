#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {void* cbr_arg; TYPE_1__* cbr_pr; } ;
typedef  TYPE_2__ dsl_prop_cb_record_t ;
struct TYPE_13__ {int /*<<< orphan*/  dd_lock; } ;
typedef  TYPE_3__ dsl_dir_t ;
struct TYPE_14__ {int /*<<< orphan*/  ds_prop_cbs; TYPE_3__* ds_dir; } ;
typedef  TYPE_4__ dsl_dataset_t ;
struct TYPE_11__ {int /*<<< orphan*/  pr_cbs; } ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_free (TYPE_2__*,int) ; 
 TYPE_2__* list_head (int /*<<< orphan*/ *) ; 
 TYPE_2__* list_next (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

void
dsl_prop_unregister_all(dsl_dataset_t *ds, void *cbarg)
{
	dsl_prop_cb_record_t *cbr, *next_cbr;

	dsl_dir_t *dd = ds->ds_dir;

	mutex_enter(&dd->dd_lock);
	next_cbr = list_head(&ds->ds_prop_cbs);
	while (next_cbr != NULL) {
		cbr = next_cbr;
		next_cbr = list_next(&ds->ds_prop_cbs, cbr);
		if (cbr->cbr_arg == cbarg) {
			list_remove(&ds->ds_prop_cbs, cbr);
			list_remove(&cbr->cbr_pr->pr_cbs, cbr);
			kmem_free(cbr, sizeof (dsl_prop_cb_record_t));
		}
	}
	mutex_exit(&dd->dd_lock);
}