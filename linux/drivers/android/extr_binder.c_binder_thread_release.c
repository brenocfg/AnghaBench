#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct binder_transaction {int /*<<< orphan*/  lock; struct binder_transaction* from_parent; struct binder_thread* from; struct binder_transaction* to_parent; TYPE_1__* buffer; struct binder_thread* to_thread; int /*<<< orphan*/ * to_proc; int /*<<< orphan*/  debug_id; } ;
struct binder_thread {int is_dead; int looper; int /*<<< orphan*/  todo; int /*<<< orphan*/  proc; int /*<<< orphan*/  wait; int /*<<< orphan*/  pid; struct binder_transaction* transaction_stack; int /*<<< orphan*/  rb_node; int /*<<< orphan*/  tmp_ref; } ;
struct binder_proc {int /*<<< orphan*/  pid; int /*<<< orphan*/  threads; int /*<<< orphan*/  tmp_ref; } ;
struct TYPE_2__ {int /*<<< orphan*/ * transaction; } ;

/* Variables and functions */
 int /*<<< orphan*/  BINDER_DEBUG_DEAD_TRANSACTION ; 
 int BINDER_LOOPER_STATE_POLL ; 
 int /*<<< orphan*/  BR_DEAD_REPLY ; 
 int /*<<< orphan*/  BUG () ; 
 int EPOLLHUP ; 
 int POLLFREE ; 
 int /*<<< orphan*/  __acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  binder_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  binder_inner_proc_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  binder_inner_proc_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  binder_release_work (struct binder_proc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  binder_send_failed_reply (struct binder_transaction*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  binder_thread_dec_tmpref (struct binder_thread*) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 
 scalar_t__ waitqueue_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_poll (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int binder_thread_release(struct binder_proc *proc,
				 struct binder_thread *thread)
{
	struct binder_transaction *t;
	struct binder_transaction *send_reply = NULL;
	int active_transactions = 0;
	struct binder_transaction *last_t = NULL;

	binder_inner_proc_lock(thread->proc);
	/*
	 * take a ref on the proc so it survives
	 * after we remove this thread from proc->threads.
	 * The corresponding dec is when we actually
	 * free the thread in binder_free_thread()
	 */
	proc->tmp_ref++;
	/*
	 * take a ref on this thread to ensure it
	 * survives while we are releasing it
	 */
	atomic_inc(&thread->tmp_ref);
	rb_erase(&thread->rb_node, &proc->threads);
	t = thread->transaction_stack;
	if (t) {
		spin_lock(&t->lock);
		if (t->to_thread == thread)
			send_reply = t;
	} else {
		__acquire(&t->lock);
	}
	thread->is_dead = true;

	while (t) {
		last_t = t;
		active_transactions++;
		binder_debug(BINDER_DEBUG_DEAD_TRANSACTION,
			     "release %d:%d transaction %d %s, still active\n",
			      proc->pid, thread->pid,
			     t->debug_id,
			     (t->to_thread == thread) ? "in" : "out");

		if (t->to_thread == thread) {
			t->to_proc = NULL;
			t->to_thread = NULL;
			if (t->buffer) {
				t->buffer->transaction = NULL;
				t->buffer = NULL;
			}
			t = t->to_parent;
		} else if (t->from == thread) {
			t->from = NULL;
			t = t->from_parent;
		} else
			BUG();
		spin_unlock(&last_t->lock);
		if (t)
			spin_lock(&t->lock);
		else
			__acquire(&t->lock);
	}
	/* annotation for sparse, lock not acquired in last iteration above */
	__release(&t->lock);

	/*
	 * If this thread used poll, make sure we remove the waitqueue
	 * from any epoll data structures holding it with POLLFREE.
	 * waitqueue_active() is safe to use here because we're holding
	 * the inner lock.
	 */
	if ((thread->looper & BINDER_LOOPER_STATE_POLL) &&
	    waitqueue_active(&thread->wait)) {
		wake_up_poll(&thread->wait, EPOLLHUP | POLLFREE);
	}

	binder_inner_proc_unlock(thread->proc);

	/*
	 * This is needed to avoid races between wake_up_poll() above and
	 * and ep_remove_waitqueue() called for other reasons (eg the epoll file
	 * descriptor being closed); ep_remove_waitqueue() holds an RCU read
	 * lock, so we can be sure it's done after calling synchronize_rcu().
	 */
	if (thread->looper & BINDER_LOOPER_STATE_POLL)
		synchronize_rcu();

	if (send_reply)
		binder_send_failed_reply(send_reply, BR_DEAD_REPLY);
	binder_release_work(proc, &thread->todo);
	binder_thread_dec_tmpref(thread);
	return active_transactions;
}