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
typedef  int /*<<< orphan*/  uint64_t ;
struct dmar_unit {int fault_log_size; int /*<<< orphan*/  unit; int /*<<< orphan*/  fault_taskqueue; int /*<<< orphan*/  fault_task; int /*<<< orphan*/  fault_log; int /*<<< orphan*/  fault_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMAR_LOCK (struct dmar_unit*) ; 
 int /*<<< orphan*/  DMAR_UNLOCK (struct dmar_unit*) ; 
 int /*<<< orphan*/  MTX_SPIN ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  PI_AV ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dmar_unit*) ; 
 int /*<<< orphan*/  TUNABLE_INT_FETCH (char*,int*) ; 
 int /*<<< orphan*/  dmar_clear_faults (struct dmar_unit*) ; 
 int /*<<< orphan*/  dmar_disable_fault_intr (struct dmar_unit*) ; 
 int /*<<< orphan*/  dmar_enable_fault_intr (struct dmar_unit*) ; 
 int /*<<< orphan*/  dmar_fault_task ; 
 int /*<<< orphan*/  malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  taskqueue_create_fast (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_start_threads (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_thread_enqueue ; 

int
dmar_init_fault_log(struct dmar_unit *unit)
{

	mtx_init(&unit->fault_lock, "dmarflt", NULL, MTX_SPIN);
	unit->fault_log_size = 256; /* 128 fault log entries */
	TUNABLE_INT_FETCH("hw.dmar.fault_log_size", &unit->fault_log_size);
	if (unit->fault_log_size % 2 != 0)
		panic("hw.dmar_fault_log_size must be even");
	unit->fault_log = malloc(sizeof(uint64_t) * unit->fault_log_size,
	    M_DEVBUF, M_WAITOK | M_ZERO);

	TASK_INIT(&unit->fault_task, 0, dmar_fault_task, unit);
	unit->fault_taskqueue = taskqueue_create_fast("dmarff", M_WAITOK,
	    taskqueue_thread_enqueue, &unit->fault_taskqueue);
	taskqueue_start_threads(&unit->fault_taskqueue, 1, PI_AV,
	    "dmar%d fault taskq", unit->unit);

	DMAR_LOCK(unit);
	dmar_disable_fault_intr(unit);
	dmar_clear_faults(unit);
	dmar_enable_fault_intr(unit);
	DMAR_UNLOCK(unit);

	return (0);
}