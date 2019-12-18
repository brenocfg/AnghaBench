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
struct dmar_unit {scalar_t__ inv_seq_waiters; scalar_t__ qi_enabled; scalar_t__ inv_queue_size; scalar_t__ inv_queue; int /*<<< orphan*/  unit; int /*<<< orphan*/ * qi_taskqueue; int /*<<< orphan*/  qi_task; } ;
struct dmar_qi_genseq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMAR_LOCK (struct dmar_unit*) ; 
 int /*<<< orphan*/  DMAR_UNLOCK (struct dmar_unit*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  dmar_disable_qi (struct dmar_unit*) ; 
 int /*<<< orphan*/  dmar_disable_qi_intr (struct dmar_unit*) ; 
 int /*<<< orphan*/  dmar_qi_advance_tail (struct dmar_unit*) ; 
 int /*<<< orphan*/  dmar_qi_emit_wait_seq (struct dmar_unit*,struct dmar_qi_genseq*,int) ; 
 int /*<<< orphan*/  dmar_qi_ensure (struct dmar_unit*,int) ; 
 int /*<<< orphan*/  dmar_qi_wait_for_seq (struct dmar_unit*,struct dmar_qi_genseq*,int) ; 
 int /*<<< orphan*/  kmem_free (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  taskqueue_drain (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_free (int /*<<< orphan*/ *) ; 

void
dmar_fini_qi(struct dmar_unit *unit)
{
	struct dmar_qi_genseq gseq;

	if (!unit->qi_enabled)
		return;
	taskqueue_drain(unit->qi_taskqueue, &unit->qi_task);
	taskqueue_free(unit->qi_taskqueue);
	unit->qi_taskqueue = NULL;

	DMAR_LOCK(unit);
	/* quisce */
	dmar_qi_ensure(unit, 1);
	dmar_qi_emit_wait_seq(unit, &gseq, true);
	dmar_qi_advance_tail(unit);
	dmar_qi_wait_for_seq(unit, &gseq, false);
	/* only after the quisce, disable queue */
	dmar_disable_qi_intr(unit);
	dmar_disable_qi(unit);
	KASSERT(unit->inv_seq_waiters == 0,
	    ("dmar%d: waiters on disabled queue", unit->unit));
	DMAR_UNLOCK(unit);

	kmem_free(unit->inv_queue, unit->inv_queue_size);
	unit->inv_queue = 0;
	unit->inv_queue_size = 0;
	unit->qi_enabled = 0;
}