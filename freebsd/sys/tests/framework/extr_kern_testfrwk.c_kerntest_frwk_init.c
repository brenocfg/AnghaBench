#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
struct TYPE_3__ {scalar_t__ kfrwk_waiting; int /*<<< orphan*/ * kfrwk_tq; int /*<<< orphan*/  kfrwk_que; int /*<<< orphan*/  kfrwk_testlist; int /*<<< orphan*/  kfrwk_testq; } ;

/* Variables and functions */
 int /*<<< orphan*/  KTFRWK_MUTEX_INIT () ; 
 scalar_t__ MAXCPU ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  PI_NET ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__ kfrwk ; 
 int /*<<< orphan*/  kfrwk_task ; 
 int ktest_frwk_inited ; 
 scalar_t__ mp_ncpus ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/ * taskqueue_create_fast (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  taskqueue_start_threads (int /*<<< orphan*/ **,scalar_t__,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  taskqueue_thread_enqueue ; 

__attribute__((used)) static int
kerntest_frwk_init(void)
{
	u_int ncpus = mp_ncpus ? mp_ncpus : MAXCPU;

	KTFRWK_MUTEX_INIT();
	TAILQ_INIT(&kfrwk.kfrwk_testq);
	TAILQ_INIT(&kfrwk.kfrwk_testlist);
	/* Now lets start up a number of tasks to do the work */
	TASK_INIT(&kfrwk.kfrwk_que, 0, kfrwk_task, &kfrwk);
	kfrwk.kfrwk_tq = taskqueue_create_fast("sbtls_task", M_NOWAIT,
	    taskqueue_thread_enqueue, &kfrwk.kfrwk_tq);
	if (kfrwk.kfrwk_tq == NULL) {
		printf("Can't start taskqueue for Kernel Test Framework\n");
		panic("Taskqueue init fails for kfrwk");
	}
	taskqueue_start_threads(&kfrwk.kfrwk_tq, ncpus, PI_NET, "[kt_frwk task]");
	kfrwk.kfrwk_waiting = ncpus;
	ktest_frwk_inited = 1;
	return (0);
}