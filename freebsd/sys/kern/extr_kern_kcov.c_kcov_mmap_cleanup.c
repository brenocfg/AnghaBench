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
struct thread {int dummy; } ;
struct kcov_info {struct thread* thread; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  KCOV_STATE_DYING ; 
 int /*<<< orphan*/  atomic_store_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_thread_fence_seq_cst () ; 
 int /*<<< orphan*/  kcov_free (struct kcov_info*) ; 
 int /*<<< orphan*/  kcov_lock ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
kcov_mmap_cleanup(void *arg)
{
	struct kcov_info *info = arg;
	struct thread *thread;

	mtx_lock_spin(&kcov_lock);
	/*
	 * Move to KCOV_STATE_DYING to stop adding new entries.
	 *
	 * If the thread is running we need to wait until thread exit to
	 * clean up as it may currently be adding a new entry. If this is
	 * the case being in KCOV_STATE_DYING will signal that the buffer
	 * needs to be cleaned up.
	 */
	atomic_store_int(&info->state, KCOV_STATE_DYING);
	atomic_thread_fence_seq_cst();
	thread = info->thread;
	mtx_unlock_spin(&kcov_lock);

	if (thread != NULL)
		return;

	/*
	 * We can safely clean up the info struct as it is in the
	 * KCOV_STATE_DYING state with no thread associated.
	 *
	 * The KCOV_STATE_DYING stops new threads from using it.
	 * The lack of a thread means nothing is currently using the buffers.
	 */
	kcov_free(info);
}