#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct thread {TYPE_3__* td_cpuset; } ;
struct proc {int dummy; } ;
struct intr_event {int /*<<< orphan*/  ie_lock; TYPE_2__* ie_thread; int /*<<< orphan*/  ie_cpu; } ;
typedef  int /*<<< orphan*/  lwpid_t ;
typedef  int /*<<< orphan*/  cpuset_t ;
struct TYPE_6__ {int /*<<< orphan*/  cs_mask; } ;
struct TYPE_5__ {TYPE_1__* it_thread; } ;
struct TYPE_4__ {int /*<<< orphan*/  td_tid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_COPY (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
#define  CPU_WHICH_INTRHANDLER 130 
#define  CPU_WHICH_IRQ 129 
#define  CPU_WHICH_ITHREAD 128 
 int /*<<< orphan*/  CPU_WHICH_TID ; 
 int /*<<< orphan*/  CPU_ZERO (int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 int ESRCH ; 
 int /*<<< orphan*/  NOCPU ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int /*<<< orphan*/ * cpuset_root ; 
 int cpuset_which (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct proc**,struct thread**,int /*<<< orphan*/ *) ; 
 struct intr_event* intr_lookup (int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

int
intr_getaffinity(int irq, int mode, void *m)
{
	struct intr_event *ie;
	struct thread *td;
	struct proc *p;
	cpuset_t *mask;
	lwpid_t id;
	int error;

	mask = m;
	ie = intr_lookup(irq);
	if (ie == NULL)
		return (ESRCH);

	error = 0;
	CPU_ZERO(mask);
	switch (mode) {
	case CPU_WHICH_IRQ:
	case CPU_WHICH_INTRHANDLER:
		mtx_lock(&ie->ie_lock);
		if (ie->ie_cpu == NOCPU)
			CPU_COPY(cpuset_root, mask);
		else
			CPU_SET(ie->ie_cpu, mask);
		mtx_unlock(&ie->ie_lock);
		break;
	case CPU_WHICH_ITHREAD:
		mtx_lock(&ie->ie_lock);
		if (ie->ie_thread == NULL) {
			mtx_unlock(&ie->ie_lock);
			CPU_COPY(cpuset_root, mask);
		} else {
			id = ie->ie_thread->it_thread->td_tid;
			mtx_unlock(&ie->ie_lock);
			error = cpuset_which(CPU_WHICH_TID, id, &p, &td, NULL);
			if (error != 0)
				return (error);
			CPU_COPY(&td->td_cpuset->cs_mask, mask);
			PROC_UNLOCK(p);
		}
	default:
		return (EINVAL);
	}
	return (0);
}