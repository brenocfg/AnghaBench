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
struct loop_device {int /*<<< orphan*/  worker_task; int /*<<< orphan*/  lo_number; int /*<<< orphan*/  worker; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIN_NICE ; 
 int /*<<< orphan*/  kthread_init_worker (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kthread_run (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  loop_kthread_worker_fn ; 
 int /*<<< orphan*/  set_user_nice (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int loop_prepare_queue(struct loop_device *lo)
{
	kthread_init_worker(&lo->worker);
	lo->worker_task = kthread_run(loop_kthread_worker_fn,
			&lo->worker, "loop%d", lo->lo_number);
	if (IS_ERR(lo->worker_task))
		return -ENOMEM;
	set_user_nice(lo->worker_task, MIN_NICE);
	return 0;
}