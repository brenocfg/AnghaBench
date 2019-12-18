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
typedef  int /*<<< orphan*/  work_func_t ;
struct TYPE_4__ {int /*<<< orphan*/  mtx; int /*<<< orphan*/  callout; } ;
struct TYPE_3__ {int /*<<< orphan*/  work_task; int /*<<< orphan*/  func; } ;
struct delayed_work {TYPE_2__ timer; TYPE_1__ work; } ;

/* Variables and functions */
 int MTX_DEF ; 
 int MTX_NOWITNESS ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct delayed_work*) ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linux_delayed_work_fn ; 
 int /*<<< orphan*/  memset (struct delayed_work*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_name (char*) ; 

void
linux_init_delayed_work(struct delayed_work *dwork, work_func_t func)
{
	memset(dwork, 0, sizeof(*dwork));
	dwork->work.func = func;
	TASK_INIT(&dwork->work.work_task, 0, linux_delayed_work_fn, dwork);
	mtx_init(&dwork->timer.mtx, spin_lock_name("lkpi-dwork"), NULL,
	    MTX_DEF | MTX_NOWITNESS);
	callout_init_mtx(&dwork->timer.callout, &dwork->timer.mtx, 0);
}