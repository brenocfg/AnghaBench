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
 int EWOULDBLOCK ; 
 int NTHREADS ; 
 int /*<<< orphan*/  PNORELOCK ; 
 int /*<<< orphan*/  kthread_exit (int /*<<< orphan*/ ) ; 
 int mtsleep (void (*) (void*),int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mymtx ; 
 int /*<<< orphan*/  panic (char*,...) ; 
 void rumptest_tsleep (void*) ; 
 int /*<<< orphan*/  wakeup (void (*) (void*)) ; 

__attribute__((used)) static void
tinythread(void *arg)
{
	static int wakeups;
	int i, rv;
	bool relock = ((uintptr_t)arg % 2) == 0;

	for (i = 0; i < 1000; i++) {
		mutex_enter(&mymtx);
		wakeup(tinythread);
		if (wakeups >= NTHREADS-1) {
			mutex_exit(&mymtx);
			break;
		}
		rv = mtsleep(tinythread, relock ? 0 : PNORELOCK,
		    "haa", 0, &mymtx);
		if (relock)
			mutex_exit(&mymtx);
		if (rv != 0)
			panic("mtsleep failed");
	}

	mutex_enter(&mymtx);
	wakeups++;
	wakeup(tinythread);

	rv = mtsleep(rumptest_tsleep, PNORELOCK, "kepuli", 1, &mymtx);
	if (rv != EWOULDBLOCK)
		panic("mtsleep unexpected return value %d", rv);

	kthread_exit(0);
}