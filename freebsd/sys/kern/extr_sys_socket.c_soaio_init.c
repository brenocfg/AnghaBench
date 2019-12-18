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

/* Variables and functions */
 int /*<<< orphan*/  AIOD_LIFETIME_DEFAULT ; 
 int /*<<< orphan*/  INT_MAX ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  new_unrhdr (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  soaio_jobs ; 
 int /*<<< orphan*/  soaio_jobs_lock ; 
 int /*<<< orphan*/  soaio_kproc_create ; 
 int /*<<< orphan*/  soaio_kproc_task ; 
 int /*<<< orphan*/  soaio_kproc_unr ; 
 int /*<<< orphan*/  soaio_lifetime ; 
 scalar_t__ soaio_target_procs ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_thread ; 

__attribute__((used)) static void
soaio_init(void)
{

	soaio_lifetime = AIOD_LIFETIME_DEFAULT;
	STAILQ_INIT(&soaio_jobs);
	mtx_init(&soaio_jobs_lock, "soaio jobs", NULL, MTX_DEF);
	soaio_kproc_unr = new_unrhdr(1, INT_MAX, NULL);
	TASK_INIT(&soaio_kproc_task, 0, soaio_kproc_create, NULL);
	if (soaio_target_procs > 0)
		taskqueue_enqueue(taskqueue_thread, &soaio_kproc_task);
}