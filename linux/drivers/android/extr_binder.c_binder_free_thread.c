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
struct binder_thread {int /*<<< orphan*/  proc; int /*<<< orphan*/  todo; } ;

/* Variables and functions */
 int /*<<< orphan*/  BINDER_STAT_THREAD ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  binder_proc_dec_tmpref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  binder_stats_deleted (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct binder_thread*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void binder_free_thread(struct binder_thread *thread)
{
	BUG_ON(!list_empty(&thread->todo));
	binder_stats_deleted(BINDER_STAT_THREAD);
	binder_proc_dec_tmpref(thread->proc);
	kfree(thread);
}