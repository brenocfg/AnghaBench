#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ dl_object; int /*<<< orphan*/ * dl_os; int /*<<< orphan*/ * dl_phys; int /*<<< orphan*/ * dl_dbuf; int /*<<< orphan*/  dl_lock; int /*<<< orphan*/  dl_tree; scalar_t__ dl_havetree; int /*<<< orphan*/  dl_bpobj; scalar_t__ dl_oldfmt; } ;
typedef  TYPE_1__ dsl_deadlist_t ;
struct TYPE_9__ {int /*<<< orphan*/  dle_bpobj; } ;
typedef  TYPE_2__ dsl_deadlist_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ B_FALSE ; 
 int /*<<< orphan*/  avl_destroy (int /*<<< orphan*/ *) ; 
 TYPE_2__* avl_destroy_nodes (int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  bpobj_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_buf_rele (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  dsl_deadlist_is_open (TYPE_1__*) ; 
 int /*<<< orphan*/  kmem_free (TYPE_2__*,int) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 

void
dsl_deadlist_close(dsl_deadlist_t *dl)
{
	void *cookie = NULL;
	dsl_deadlist_entry_t *dle;

	ASSERT(dsl_deadlist_is_open(dl));

	if (dl->dl_oldfmt) {
		dl->dl_oldfmt = B_FALSE;
		bpobj_close(&dl->dl_bpobj);
		dl->dl_os = NULL;
		dl->dl_object = 0;
		return;
	}

	if (dl->dl_havetree) {
		while ((dle = avl_destroy_nodes(&dl->dl_tree, &cookie))
		    != NULL) {
			bpobj_close(&dle->dle_bpobj);
			kmem_free(dle, sizeof (*dle));
		}
		avl_destroy(&dl->dl_tree);
	}
	dmu_buf_rele(dl->dl_dbuf, dl);
	mutex_destroy(&dl->dl_lock);
	dl->dl_dbuf = NULL;
	dl->dl_phys = NULL;
	dl->dl_os = NULL;
	dl->dl_object = 0;
}