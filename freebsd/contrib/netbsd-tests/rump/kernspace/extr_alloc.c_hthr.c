#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int VM_MAP_WANTVA ; 
 int __arraycount (int /*<<< orphan*/ *) ; 
 int curstat ; 
 int /*<<< orphan*/  cv_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kcv ; 
 TYPE_1__* kernel_map ; 
 int /*<<< orphan*/  kpause (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kthread_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pool_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp1 ; 
 int /*<<< orphan*/ * store ; 

__attribute__((used)) static void
hthr(void *arg)
{
	int i;

	mutex_enter(&mtx);
	curstat++;
	cv_signal(&kcv);

	while (curstat < 2)
		cv_wait(&kcv, &mtx);
	mutex_exit(&mtx);

	/* try to guarantee that the sleep is triggered in PR_WAITOK */
	while ((kernel_map->flags & VM_MAP_WANTVA) == 0)
		kpause("take5", false, 1, NULL);

	for (i = 0; i < __arraycount(store); i++) {
		pool_put(&pp1, store[i]);
	}

	kthread_exit(0);
}