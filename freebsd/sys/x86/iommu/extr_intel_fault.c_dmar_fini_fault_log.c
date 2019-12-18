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
struct dmar_unit {scalar_t__ fault_log_tail; scalar_t__ fault_log_head; int /*<<< orphan*/ * fault_log; int /*<<< orphan*/  fault_lock; int /*<<< orphan*/ * fault_taskqueue; int /*<<< orphan*/  fault_task; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMAR_LOCK (struct dmar_unit*) ; 
 int /*<<< orphan*/  DMAR_UNLOCK (struct dmar_unit*) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  dmar_disable_fault_intr (struct dmar_unit*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_drain (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_free (int /*<<< orphan*/ *) ; 

void
dmar_fini_fault_log(struct dmar_unit *unit)
{

	if (unit->fault_taskqueue == NULL)
		return;

	DMAR_LOCK(unit);
	dmar_disable_fault_intr(unit);
	DMAR_UNLOCK(unit);

	taskqueue_drain(unit->fault_taskqueue, &unit->fault_task);
	taskqueue_free(unit->fault_taskqueue);
	unit->fault_taskqueue = NULL;
	mtx_destroy(&unit->fault_lock);

	free(unit->fault_log, M_DEVBUF);
	unit->fault_log = NULL;
	unit->fault_log_head = unit->fault_log_tail = 0;
}