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
struct TYPE_8__ {int /*<<< orphan*/  rl_lock; int /*<<< orphan*/  rl_tree; } ;
typedef  TYPE_1__ rangelock_t ;
struct TYPE_9__ {scalar_t__ lr_type; int lr_count; int /*<<< orphan*/  lr_read_cv; scalar_t__ lr_read_wanted; int /*<<< orphan*/  lr_write_cv; scalar_t__ lr_write_wanted; int /*<<< orphan*/  lr_proxy; TYPE_1__* lr_rangelock; } ;
typedef  TYPE_2__ locked_range_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ RL_READER ; 
 scalar_t__ RL_WRITER ; 
 int /*<<< orphan*/  avl_remove (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  cv_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_free (TYPE_2__*,int) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rangelock_exit_reader (TYPE_1__*,TYPE_2__*) ; 

void
rangelock_exit(locked_range_t *lr)
{
	rangelock_t *rl = lr->lr_rangelock;

	ASSERT(lr->lr_type == RL_WRITER || lr->lr_type == RL_READER);
	ASSERT(lr->lr_count == 1 || lr->lr_count == 0);
	ASSERT(!lr->lr_proxy);

	mutex_enter(&rl->rl_lock);
	if (lr->lr_type == RL_WRITER) {
		/* writer locks can't be shared or split */
		avl_remove(&rl->rl_tree, lr);
		mutex_exit(&rl->rl_lock);
		if (lr->lr_write_wanted) {
			cv_broadcast(&lr->lr_write_cv);
			cv_destroy(&lr->lr_write_cv);
		}
		if (lr->lr_read_wanted) {
			cv_broadcast(&lr->lr_read_cv);
			cv_destroy(&lr->lr_read_cv);
		}
		kmem_free(lr, sizeof (locked_range_t));
	} else {
		/*
		 * lock may be shared, let rangelock_exit_reader()
		 * release the lock and free the rl_t
		 */
		rangelock_exit_reader(rl, lr);
		mutex_exit(&rl->rl_lock);
	}
}