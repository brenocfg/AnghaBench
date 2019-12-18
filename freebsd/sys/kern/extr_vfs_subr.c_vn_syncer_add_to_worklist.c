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
struct bufobj {int bo_flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_BO_WLOCKED (struct bufobj*) ; 
 int BO_ONWORKLST ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct bufobj*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct bufobj*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bo_synclist ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sync_mtx ; 
 int syncer_delayno ; 
 int syncer_mask ; 
 int syncer_maxdelay ; 
 int /*<<< orphan*/ * syncer_workitem_pending ; 
 int /*<<< orphan*/  syncer_worklist_len ; 

__attribute__((used)) static void
vn_syncer_add_to_worklist(struct bufobj *bo, int delay)
{
	int slot;

	ASSERT_BO_WLOCKED(bo);

	mtx_lock(&sync_mtx);
	if (bo->bo_flag & BO_ONWORKLST)
		LIST_REMOVE(bo, bo_synclist);
	else {
		bo->bo_flag |= BO_ONWORKLST;
		syncer_worklist_len++;
	}

	if (delay > syncer_maxdelay - 2)
		delay = syncer_maxdelay - 2;
	slot = (syncer_delayno + delay) & syncer_mask;

	LIST_INSERT_HEAD(&syncer_workitem_pending[slot], bo, bo_synclist);
	mtx_unlock(&sync_mtx);
}