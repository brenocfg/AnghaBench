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
 int /*<<< orphan*/  KTHREAD_MPSAFE ; 
 int /*<<< orphan*/  MUTEX_DEFAULT ; 
 int /*<<< orphan*/  PRI_NONE ; 
 int /*<<< orphan*/  cv ; 
 int /*<<< orphan*/  cv_init (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  cv_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kpause (char*,int,int,int /*<<< orphan*/ *) ; 
 int kthread_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct lwp**,char*) ; 
 int /*<<< orphan*/  mtx ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 int /*<<< orphan*/  thethread ; 
 scalar_t__ value ; 

void
rumptest_thread()
{
	struct lwp *newl;
	int rv;

	mutex_init(&mtx, MUTEX_DEFAULT, IPL_NONE);
	cv_init(&cv, "jooei");
	rv = kthread_create(PRI_NONE, KTHREAD_MPSAFE, NULL,
	    thethread, NULL, &newl, "ktest");
	if (rv)
		panic("thread creation failed: %d", rv);

	mutex_enter(&mtx);
	while (value == 0)
		cv_wait(&cv, &mtx);
	mutex_exit(&mtx);

	/* try to verify thread really exists and we don't crash */
	kpause("take1", false, 1, NULL);
}