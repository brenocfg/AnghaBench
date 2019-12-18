#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct file {int dummy; } ;
struct binder_txn_fd_fixup {int /*<<< orphan*/  fixup_entry; int /*<<< orphan*/  offset; struct file* file; } ;
struct binder_transaction {int flags; int /*<<< orphan*/  fd_fixups; TYPE_2__* buffer; struct binder_proc* to_proc; } ;
struct binder_thread {int /*<<< orphan*/  pid; struct binder_proc* proc; } ;
struct binder_proc {int /*<<< orphan*/  tsk; int /*<<< orphan*/  pid; } ;
typedef  int /*<<< orphan*/  binder_size_t ;
struct TYPE_4__ {TYPE_1__* target_node; } ;
struct TYPE_3__ {int accept_fds; } ;

/* Variables and functions */
 int EBADF ; 
 int ENOMEM ; 
 int EPERM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int TF_ACCEPT_FDS ; 
 int /*<<< orphan*/  binder_user_error (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 struct file* fget (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fput (struct file*) ; 
 struct binder_txn_fd_fixup* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int security_binder_transfer_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct file*) ; 
 int /*<<< orphan*/  trace_binder_transaction_fd_send (struct binder_transaction*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int binder_translate_fd(u32 fd, binder_size_t fd_offset,
			       struct binder_transaction *t,
			       struct binder_thread *thread,
			       struct binder_transaction *in_reply_to)
{
	struct binder_proc *proc = thread->proc;
	struct binder_proc *target_proc = t->to_proc;
	struct binder_txn_fd_fixup *fixup;
	struct file *file;
	int ret = 0;
	bool target_allows_fd;

	if (in_reply_to)
		target_allows_fd = !!(in_reply_to->flags & TF_ACCEPT_FDS);
	else
		target_allows_fd = t->buffer->target_node->accept_fds;
	if (!target_allows_fd) {
		binder_user_error("%d:%d got %s with fd, %d, but target does not allow fds\n",
				  proc->pid, thread->pid,
				  in_reply_to ? "reply" : "transaction",
				  fd);
		ret = -EPERM;
		goto err_fd_not_accepted;
	}

	file = fget(fd);
	if (!file) {
		binder_user_error("%d:%d got transaction with invalid fd, %d\n",
				  proc->pid, thread->pid, fd);
		ret = -EBADF;
		goto err_fget;
	}
	ret = security_binder_transfer_file(proc->tsk, target_proc->tsk, file);
	if (ret < 0) {
		ret = -EPERM;
		goto err_security;
	}

	/*
	 * Add fixup record for this transaction. The allocation
	 * of the fd in the target needs to be done from a
	 * target thread.
	 */
	fixup = kzalloc(sizeof(*fixup), GFP_KERNEL);
	if (!fixup) {
		ret = -ENOMEM;
		goto err_alloc;
	}
	fixup->file = file;
	fixup->offset = fd_offset;
	trace_binder_transaction_fd_send(t, fd, fixup->offset);
	list_add_tail(&fixup->fixup_entry, &t->fd_fixups);

	return ret;

err_alloc:
err_security:
	fput(file);
err_fget:
err_fd_not_accepted:
	return ret;
}