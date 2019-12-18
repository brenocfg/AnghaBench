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
struct intr_event {int (* ie_assign_cpu ) (int /*<<< orphan*/ ,int) ;int ie_cpu; int /*<<< orphan*/  ie_lock; TYPE_2__* ie_thread; int /*<<< orphan*/  ie_source; } ;
typedef  int /*<<< orphan*/  lwpid_t ;
struct TYPE_4__ {TYPE_1__* it_thread; } ;
struct TYPE_3__ {int /*<<< orphan*/  td_tid; } ;

/* Variables and functions */
 scalar_t__ CPU_ABSENT (int) ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int NOCPU ; 
 int /*<<< orphan*/  PRIV_SCHED_CPUSET_INTR ; 
 int cpuset_setithread (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int priv_check (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
_intr_event_bind(struct intr_event *ie, int cpu, bool bindirq, bool bindithread)
{
	lwpid_t id;
	int error;

	/* Need a CPU to bind to. */
	if (cpu != NOCPU && CPU_ABSENT(cpu))
		return (EINVAL);

	if (ie->ie_assign_cpu == NULL)
		return (EOPNOTSUPP);

	error = priv_check(curthread, PRIV_SCHED_CPUSET_INTR);
	if (error)
		return (error);

	/*
	 * If we have any ithreads try to set their mask first to verify
	 * permissions, etc.
	 */
	if (bindithread) {
		mtx_lock(&ie->ie_lock);
		if (ie->ie_thread != NULL) {
			id = ie->ie_thread->it_thread->td_tid;
			mtx_unlock(&ie->ie_lock);
			error = cpuset_setithread(id, cpu);
			if (error)
				return (error);
		} else
			mtx_unlock(&ie->ie_lock);
	}
	if (bindirq)
		error = ie->ie_assign_cpu(ie->ie_source, cpu);
	if (error) {
		if (bindithread) {
			mtx_lock(&ie->ie_lock);
			if (ie->ie_thread != NULL) {
				cpu = ie->ie_cpu;
				id = ie->ie_thread->it_thread->td_tid;
				mtx_unlock(&ie->ie_lock);
				(void)cpuset_setithread(id, cpu);
			} else
				mtx_unlock(&ie->ie_lock);
		}
		return (error);
	}

	if (bindirq) {
		mtx_lock(&ie->ie_lock);
		ie->ie_cpu = cpu;
		mtx_unlock(&ie->ie_lock);
	}

	return (error);
}