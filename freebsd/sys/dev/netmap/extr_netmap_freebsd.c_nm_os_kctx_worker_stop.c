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
struct nm_kctx {int /*<<< orphan*/ * worker; scalar_t__ run; } ;

/* Variables and functions */
 int /*<<< orphan*/  kthread_resume (int /*<<< orphan*/ *) ; 

void
nm_os_kctx_worker_stop(struct nm_kctx *nmk)
{
	if (!nmk->worker)
		return;

	/* tell to kthread to exit from main loop */
	nmk->run = 0;

	/* wake up kthread if it sleeps */
	kthread_resume(nmk->worker);

	nmk->worker = NULL;
}