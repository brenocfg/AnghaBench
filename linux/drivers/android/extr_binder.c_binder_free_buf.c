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
struct binder_work {int dummy; } ;
struct binder_proc {int /*<<< orphan*/  alloc; int /*<<< orphan*/  todo; } ;
struct binder_node {int has_async_transaction; int /*<<< orphan*/  async_todo; struct binder_proc* proc; } ;
struct binder_buffer {struct binder_node* target_node; scalar_t__ async_transaction; TYPE_1__* transaction; } ;
struct TYPE_2__ {int /*<<< orphan*/ * buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  binder_alloc_free_buf (int /*<<< orphan*/ *,struct binder_buffer*) ; 
 struct binder_work* binder_dequeue_work_head_ilocked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  binder_enqueue_work_ilocked (struct binder_work*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  binder_inner_proc_lock (struct binder_proc*) ; 
 int /*<<< orphan*/  binder_inner_proc_unlock (struct binder_proc*) ; 
 int /*<<< orphan*/  binder_node_inner_lock (struct binder_node*) ; 
 int /*<<< orphan*/  binder_node_inner_unlock (struct binder_node*) ; 
 int /*<<< orphan*/  binder_transaction_buffer_release (struct binder_proc*,struct binder_buffer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  binder_wakeup_proc_ilocked (struct binder_proc*) ; 
 int /*<<< orphan*/  trace_binder_transaction_buffer_release (struct binder_buffer*) ; 

__attribute__((used)) static void
binder_free_buf(struct binder_proc *proc, struct binder_buffer *buffer)
{
	binder_inner_proc_lock(proc);
	if (buffer->transaction) {
		buffer->transaction->buffer = NULL;
		buffer->transaction = NULL;
	}
	binder_inner_proc_unlock(proc);
	if (buffer->async_transaction && buffer->target_node) {
		struct binder_node *buf_node;
		struct binder_work *w;

		buf_node = buffer->target_node;
		binder_node_inner_lock(buf_node);
		BUG_ON(!buf_node->has_async_transaction);
		BUG_ON(buf_node->proc != proc);
		w = binder_dequeue_work_head_ilocked(
				&buf_node->async_todo);
		if (!w) {
			buf_node->has_async_transaction = false;
		} else {
			binder_enqueue_work_ilocked(
					w, &proc->todo);
			binder_wakeup_proc_ilocked(proc);
		}
		binder_node_inner_unlock(buf_node);
	}
	trace_binder_transaction_buffer_release(buffer);
	binder_transaction_buffer_release(proc, buffer, 0, false);
	binder_alloc_free_buf(&proc->alloc, buffer);
}