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
struct lwp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPL_NONE ; 
 int KTHREAD_MPSAFE ; 
 int KTHREAD_MUSTJOIN ; 
 int /*<<< orphan*/  MUTEX_DEFAULT ; 
 int NTHREADS ; 
 int /*<<< orphan*/  PRI_NONE ; 
 int kthread_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,struct lwp**,char*) ; 
 int /*<<< orphan*/  kthread_join (struct lwp*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mymtx ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 int /*<<< orphan*/  tinythread ; 

void
rumptest_tsleep()
{
	struct lwp *notbigl[NTHREADS];
	int rv, i;

	mutex_init(&mymtx, MUTEX_DEFAULT, IPL_NONE);

	for (i = 0; i < NTHREADS; i++) {
		rv = kthread_create(PRI_NONE, KTHREAD_MUSTJOIN| KTHREAD_MPSAFE,
		    NULL, tinythread, (void *)(uintptr_t)i, &notbigl[i], "nb");
		if (rv)
			panic("thread create failed: %d", rv);
	}

	for (i = 0; i < NTHREADS; i++) {
		kthread_join(notbigl[i]);
	}
}