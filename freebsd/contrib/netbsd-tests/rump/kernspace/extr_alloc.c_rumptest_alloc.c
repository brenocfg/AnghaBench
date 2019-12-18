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
 int /*<<< orphan*/  IPL_NONE ; 
 int /*<<< orphan*/  KTHREAD_MPSAFE ; 
 int /*<<< orphan*/  MUTEX_DEFAULT ; 
 int /*<<< orphan*/  PRI_NONE ; 
 int /*<<< orphan*/  PR_NOWAIT ; 
 int /*<<< orphan*/  PR_WAITOK ; 
 int __arraycount (char**) ; 
 scalar_t__ curstat ; 
 int /*<<< orphan*/  cv_init (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  cv_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hthr ; 
 int /*<<< orphan*/  kcv ; 
 int /*<<< orphan*/  kthread_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mtx ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  pool_allocator_nointr ; 
 char* pool_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pool_init (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp1 ; 
 int /*<<< orphan*/  pp2 ; 
 char** store ; 

void
rumptest_alloc(size_t thelimit)
{
	char *c;
	int succ, i;

	mutex_init(&mtx, MUTEX_DEFAULT, IPL_NONE);
	cv_init(&kcv, "venailu");

	kthread_create(PRI_NONE, KTHREAD_MPSAFE, NULL, hthr, NULL, NULL, "h");

	pool_init(&pp1, 1024, 0, 0, 0, "vara-allas",
	    &pool_allocator_nointr, IPL_NONE);
	pool_init(&pp2, 1024, 0, 0, 0, "allas",
	    &pool_allocator_nointr, IPL_NONE);
	
	for (i = 0; i < __arraycount(store); i++) {
		store[i] = pool_get(&pp1, PR_NOWAIT);
		if (store[i] == NULL) {
			panic("pool_get store failed");
		}
	}

	/* wait until other thread runs */
	mutex_enter(&mtx);
	while (curstat == 0)
		cv_wait(&kcv, &mtx);
	mutex_exit(&mtx);

	for (succ = 0;; succ++) {
		if (succ * 1024 > thelimit)
			panic("managed to allocate over limit");
		if ((c = pool_get(&pp2, PR_NOWAIT)) == NULL) {
			mutex_enter(&mtx);
			curstat++;
			cv_signal(&kcv);
			mutex_exit(&mtx);
			if (pool_get(&pp2, PR_WAITOK) == NULL)
				panic("pool get PR_WAITOK failed");
			break;
		}
		*c = 'a';
	}
}