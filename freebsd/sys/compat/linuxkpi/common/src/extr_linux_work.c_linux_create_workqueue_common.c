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
struct workqueue_struct {int /*<<< orphan*/  exec_mtx; int /*<<< orphan*/  exec_head; int /*<<< orphan*/  taskqueue; int /*<<< orphan*/  draining; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTX_DEF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  PWAIT ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct workqueue_struct* kmalloc (int,int) ; 
 int linux_default_wq_cpus ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_create (char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_start_threads (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  taskqueue_thread_enqueue ; 

struct workqueue_struct *
linux_create_workqueue_common(const char *name, int cpus)
{
	struct workqueue_struct *wq;

	/*
	 * If zero CPUs are specified use the default number of CPUs:
	 */
	if (cpus == 0)
		cpus = linux_default_wq_cpus;

	wq = kmalloc(sizeof(*wq), M_WAITOK | M_ZERO);
	wq->taskqueue = taskqueue_create(name, M_WAITOK,
	    taskqueue_thread_enqueue, &wq->taskqueue);
	atomic_set(&wq->draining, 0);
	taskqueue_start_threads(&wq->taskqueue, cpus, PWAIT, "%s", name);
	TAILQ_INIT(&wq->exec_head);
	mtx_init(&wq->exec_mtx, "linux_wq_exec", NULL, MTX_DEF);

	return (wq);
}