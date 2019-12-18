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
struct thread {int dummy; } ;

/* Variables and functions */
 int EWOULDBLOCK ; 
 int QUIT ; 
 int /*<<< orphan*/  global_condvar ; 
 int hz ; 
 int /*<<< orphan*/  kthread_exit () ; 
 int kthread_suspend (struct thread*,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*,...) ; 
 int /*<<< orphan*/  test_global_lock ; 
 int /*<<< orphan*/  test_thrcnt ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void 
thr_suspender(void *arg)
{
	struct thread *td = (struct thread *) arg;
	int error;

	for (;;) {
		if (QUIT == 1)
			break;
		error = kthread_suspend(td, 10*hz);
		if (error != 0 && QUIT == 0) {
			if (error == EWOULDBLOCK)
				panic("Ooops: kthread deadlock\n");
			else 
				panic("kthread_suspend error: %d\n", error);
			break;
		}
	}

	mtx_lock(&test_global_lock);
	test_thrcnt--;
	wakeup(&global_condvar);
	mtx_unlock(&test_global_lock);

	kthread_exit();
}