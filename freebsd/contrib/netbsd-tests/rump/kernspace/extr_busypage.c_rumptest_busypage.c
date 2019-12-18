#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct lwp {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  vmobjlock; } ;

/* Variables and functions */
 int KTHREAD_MPSAFE ; 
 int KTHREAD_MUSTJOIN ; 
 int /*<<< orphan*/  PRI_NONE ; 
 int /*<<< orphan*/  cv_init (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  cv_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int kthread_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct lwp**,char*) ; 
 int kthread_join (struct lwp*) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,...) ; 
 int /*<<< orphan*/  tcv ; 
 int /*<<< orphan*/ * testpg ; 
 int /*<<< orphan*/  thread ; 
 int /*<<< orphan*/  threadrun ; 
 TYPE_1__* uao_create (int,int /*<<< orphan*/ ) ; 
 TYPE_1__* uobj ; 
 int /*<<< orphan*/  uvm_page_unbusy (int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/ * uvm_pagealloc (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
rumptest_busypage()
{
	struct lwp *newl;
	int rv;

	cv_init(&tcv, "napina");

	uobj = uao_create(1, 0);
	mutex_enter(uobj->vmobjlock);
	testpg = uvm_pagealloc(uobj, 0, NULL, 0);
	mutex_exit(uobj->vmobjlock);
	if (testpg == NULL)
		panic("couldn't create vm page");

	rv = kthread_create(PRI_NONE, KTHREAD_MUSTJOIN | KTHREAD_MPSAFE, NULL,
	    thread, NULL, &newl, "jointest");
	if (rv)
		panic("thread creation failed: %d", rv);

	mutex_enter(uobj->vmobjlock);
	while (!threadrun)
		cv_wait(&tcv, uobj->vmobjlock);

	uvm_page_unbusy(&testpg, 1);
	mutex_exit(uobj->vmobjlock);

	rv = kthread_join(newl);
	if (rv)
		panic("thread join failed: %d", rv);

}