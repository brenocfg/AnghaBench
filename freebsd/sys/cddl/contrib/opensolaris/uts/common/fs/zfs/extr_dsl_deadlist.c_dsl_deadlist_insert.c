#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {int /*<<< orphan*/  dl_lock; int /*<<< orphan*/  dl_tree; TYPE_1__* dl_phys; int /*<<< orphan*/  dl_os; int /*<<< orphan*/  dl_dbuf; int /*<<< orphan*/  dl_bpobj; scalar_t__ dl_oldfmt; } ;
typedef  TYPE_2__ dsl_deadlist_t ;
struct TYPE_22__ {int /*<<< orphan*/  dle_mintxg; } ;
typedef  TYPE_3__ dsl_deadlist_entry_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
struct TYPE_23__ {int /*<<< orphan*/  blk_birth; } ;
typedef  TYPE_4__ blkptr_t ;
typedef  int /*<<< orphan*/  avl_index_t ;
struct TYPE_20__ {int /*<<< orphan*/  dl_uncomp; int /*<<< orphan*/  dl_comp; int /*<<< orphan*/  dl_used; } ;

/* Variables and functions */
 int /*<<< orphan*/  AVL_BEFORE ; 
 TYPE_3__* AVL_PREV (int /*<<< orphan*/ *,TYPE_3__*) ; 
 scalar_t__ BP_GET_PSIZE (TYPE_4__ const*) ; 
 scalar_t__ BP_GET_UCSIZE (TYPE_4__ const*) ; 
 TYPE_3__* avl_find (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *) ; 
 TYPE_3__* avl_nearest (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bp_get_dsize_sync (int /*<<< orphan*/ ,TYPE_4__ const*) ; 
 int /*<<< orphan*/  bpobj_enqueue (int /*<<< orphan*/ *,TYPE_4__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dle_enqueue (TYPE_2__*,TYPE_3__*,TYPE_4__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_buf_will_dirty (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_objset_spa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_deadlist_load_tree (TYPE_2__*) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

void
dsl_deadlist_insert(dsl_deadlist_t *dl, const blkptr_t *bp, dmu_tx_t *tx)
{
	dsl_deadlist_entry_t dle_tofind;
	dsl_deadlist_entry_t *dle;
	avl_index_t where;

	if (dl->dl_oldfmt) {
		bpobj_enqueue(&dl->dl_bpobj, bp, tx);
		return;
	}

	mutex_enter(&dl->dl_lock);
	dsl_deadlist_load_tree(dl);

	dmu_buf_will_dirty(dl->dl_dbuf, tx);
	dl->dl_phys->dl_used +=
	    bp_get_dsize_sync(dmu_objset_spa(dl->dl_os), bp);
	dl->dl_phys->dl_comp += BP_GET_PSIZE(bp);
	dl->dl_phys->dl_uncomp += BP_GET_UCSIZE(bp);

	dle_tofind.dle_mintxg = bp->blk_birth;
	dle = avl_find(&dl->dl_tree, &dle_tofind, &where);
	if (dle == NULL)
		dle = avl_nearest(&dl->dl_tree, where, AVL_BEFORE);
	else
		dle = AVL_PREV(&dl->dl_tree, dle);
	dle_enqueue(dl, dle, bp, tx);
	mutex_exit(&dl->dl_lock);
}