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
struct proc {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  type; TYPE_2__* user_td; } ;
struct nm_kctx {int run; int /*<<< orphan*/ * worker; TYPE_1__ worker_ctx; scalar_t__ attach_user; } ;
struct TYPE_4__ {struct proc* td_proc; } ;

/* Variables and functions */
 int EBUSY ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  RFNOWAIT ; 
 TYPE_2__* curthread ; 
 int kthread_add (int /*<<< orphan*/ ,struct nm_kctx*,struct proc*,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nm_kctx_worker ; 
 int /*<<< orphan*/  nm_prerr (char*,int) ; 
 int /*<<< orphan*/  nm_prinf (char*,int /*<<< orphan*/ *) ; 

int
nm_os_kctx_worker_start(struct nm_kctx *nmk)
{
	struct proc *p = NULL;
	int error = 0;

	/* Temporarily disable this function as it is currently broken
	 * and causes kernel crashes. The failure can be triggered by
	 * the "vale_polling_enable_disable" test in ctrl-api-test.c. */
	return EOPNOTSUPP;

	if (nmk->worker)
		return EBUSY;

	/* check if we want to attach kthread to user process */
	if (nmk->attach_user) {
		nmk->worker_ctx.user_td = curthread;
		p = curthread->td_proc;
	}

	/* enable kthread main loop */
	nmk->run = 1;
	/* create kthread */
	if((error = kthread_add(nm_kctx_worker, nmk, p,
			&nmk->worker, RFNOWAIT /* to be checked */, 0, "nm-kthread-%ld",
			nmk->worker_ctx.type))) {
		goto err;
	}

	nm_prinf("nm_kthread started td %p", nmk->worker);

	return 0;
err:
	nm_prerr("nm_kthread start failed err %d", error);
	nmk->worker = NULL;
	return error;
}