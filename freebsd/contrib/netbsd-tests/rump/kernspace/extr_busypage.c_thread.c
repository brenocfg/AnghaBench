#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  vmobjlock; } ;

/* Variables and functions */
 int /*<<< orphan*/  PG_WANTED ; 
 int /*<<< orphan*/  UVM_UNLOCK_AND_WAIT (TYPE_2__*,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cv_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kthread_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcv ; 
 TYPE_2__* testpg ; 
 int threadrun ; 
 TYPE_1__* uobj ; 

__attribute__((used)) static void
thread(void *arg)
{

	mutex_enter(uobj->vmobjlock);
	threadrun = true;
	cv_signal(&tcv);
	testpg->flags |= PG_WANTED;
	UVM_UNLOCK_AND_WAIT(testpg, uobj->vmobjlock, false, "tw", 0);
	kthread_exit(0);
}