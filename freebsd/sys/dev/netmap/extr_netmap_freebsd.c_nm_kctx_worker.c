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
struct nm_kctx_ctx {int /*<<< orphan*/  worker_private; int /*<<< orphan*/  (* worker_fn ) (int /*<<< orphan*/ ) ;scalar_t__ user_td; } ;
struct nm_kctx {scalar_t__ affinity; scalar_t__ run; struct nm_kctx_ctx worker_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  PROC_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROC_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curproc ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  kthread_exit () ; 
 int /*<<< orphan*/  kthread_suspend_check () ; 
 int /*<<< orphan*/  sched_bind (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_suspend_check (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nm_kctx_worker(void *data)
{
	struct nm_kctx *nmk = data;
	struct nm_kctx_ctx *ctx = &nmk->worker_ctx;

	if (nmk->affinity >= 0) {
		thread_lock(curthread);
		sched_bind(curthread, nmk->affinity);
		thread_unlock(curthread);
	}

	while (nmk->run) {
		/*
		 * check if the parent process dies
		 * (when kthread is attached to user process)
		 */
		if (ctx->user_td) {
			PROC_LOCK(curproc);
			thread_suspend_check(0);
			PROC_UNLOCK(curproc);
		} else {
			kthread_suspend_check();
		}

		/* Continuously execute worker process. */
		ctx->worker_fn(ctx->worker_private); /* worker body */
	}

	kthread_exit();
}