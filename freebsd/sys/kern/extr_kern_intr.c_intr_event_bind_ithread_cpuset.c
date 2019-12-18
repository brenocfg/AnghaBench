#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct intr_event {int /*<<< orphan*/  ie_lock; TYPE_2__* ie_thread; } ;
typedef  int /*<<< orphan*/  lwpid_t ;
typedef  int /*<<< orphan*/  cpuset_t ;
struct TYPE_4__ {TYPE_1__* it_thread; } ;
struct TYPE_3__ {int /*<<< orphan*/  td_tid; } ;

/* Variables and functions */
 int ENODEV ; 
 int cpuset_setthread (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

int
intr_event_bind_ithread_cpuset(struct intr_event *ie, cpuset_t *cs)
{
	lwpid_t id;

	mtx_lock(&ie->ie_lock);
	if (ie->ie_thread != NULL) {
		id = ie->ie_thread->it_thread->td_tid;
		mtx_unlock(&ie->ie_lock);
		return (cpuset_setthread(id, cs));
	} else {
		mtx_unlock(&ie->ie_lock);
	}
	return (ENODEV);
}