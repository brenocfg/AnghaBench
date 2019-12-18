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
struct proc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTX_DEF ; 
 scalar_t__ QUIT ; 
 int kproc_kthread_add (int /*<<< orphan*/ ,struct thread*,struct proc**,struct thread**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 int /*<<< orphan*/  test_global_lock ; 
 int test_thrcnt ; 
 int /*<<< orphan*/  thr_getsuspended ; 
 int /*<<< orphan*/  thr_resumer ; 
 int /*<<< orphan*/  thr_suspender ; 

__attribute__((used)) static void
kthrdlk_init(void)
{
	struct proc *testproc;
	struct thread *newthr;
	int error;

	QUIT = 0;
	test_thrcnt = 3;
	mtx_init(&test_global_lock, "kthrdlk_lock", NULL, MTX_DEF);
	testproc = NULL;
	error = kproc_kthread_add(thr_getsuspended, NULL, &testproc, &newthr,
	    0, 0, "kthrdlk", "thr_getsuspended");
	if (error != 0)
		panic("cannot start thr_getsuspended error: %d\n", error);

	error = kproc_kthread_add(thr_resumer, newthr, &testproc, NULL, 0, 0, 
	    "kthrdlk", "thr_resumer");
	if (error != 0)
		panic("cannot start thr_resumer error: %d\n", error);

	error = kproc_kthread_add(thr_suspender, newthr, &testproc, NULL, 0, 0, 
	    "kthrdlk", "thr_suspender");
	if (error != 0)
		panic("cannot start thr_suspender error: %d\n", error);
}