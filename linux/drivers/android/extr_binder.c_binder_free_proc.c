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
struct binder_proc {int /*<<< orphan*/  tsk; int /*<<< orphan*/  alloc; int /*<<< orphan*/  delivered_death; int /*<<< orphan*/  todo; } ;

/* Variables and functions */
 int /*<<< orphan*/  BINDER_STAT_PROC ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  binder_alloc_deferred_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  binder_stats_deleted (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct binder_proc*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_task_struct (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void binder_free_proc(struct binder_proc *proc)
{
	BUG_ON(!list_empty(&proc->todo));
	BUG_ON(!list_empty(&proc->delivered_death));
	binder_alloc_deferred_release(&proc->alloc);
	put_task_struct(proc->tsk);
	binder_stats_deleted(BINDER_STAT_PROC);
	kfree(proc);
}