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
 int KTHREAD_MPSAFE ; 
 int KTHREAD_MUSTJOIN ; 
 int /*<<< orphan*/  PRI_NONE ; 
 int /*<<< orphan*/  jointhread ; 
 int kthread_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct lwp**,char*) ; 
 int kthread_join (struct lwp*) ; 
 int /*<<< orphan*/  panic (char*,...) ; 
 int testit ; 

void
rumptest_threadjoin()
{
	struct lwp *newl;
	int rv;

	rv = kthread_create(PRI_NONE, KTHREAD_MUSTJOIN | KTHREAD_MPSAFE, NULL,
	    jointhread, NULL, &newl, "jointest");
	if (rv)
		panic("thread creation failed: %d", rv);
	rv = kthread_join(newl);
	if (rv)
		panic("thread join failed: %d", rv);

	if (testit != 1)
		panic("new thread did not run");
}