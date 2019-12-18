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
struct thread {int /*<<< orphan*/  td_oncpu; } ;
struct stack {scalar_t__ depth; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  IPI_TRACE ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  MPASS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TD_IS_RUNNING (struct thread*) ; 
 int /*<<< orphan*/  THREAD_LOCK_ASSERT (struct thread*,int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_load_acq_ptr (long*) ; 
 int /*<<< orphan*/  cpu_spinwait () ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  ipi_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nmi_lock ; 
 struct thread* nmi_pending ; 
 struct stack* nmi_stack ; 
 int /*<<< orphan*/  stack_save (struct stack*) ; 

int
stack_save_td_running(struct stack *st, struct thread *td)
{

#ifdef STACK
	THREAD_LOCK_ASSERT(td, MA_OWNED);
	MPASS(TD_IS_RUNNING(td));

	if (td == curthread) {
		stack_save(st);
		return (0);
	}

#ifdef SMP
	mtx_lock_spin(&nmi_lock);

	nmi_stack = st;
	nmi_pending = td;
	ipi_cpu(td->td_oncpu, IPI_TRACE);
	while ((void *)atomic_load_acq_ptr((long *)&nmi_pending) != NULL)
		cpu_spinwait();
	nmi_stack = NULL;

	mtx_unlock_spin(&nmi_lock);

	if (st->depth == 0)
		return (EAGAIN);
#else /* !SMP */
	KASSERT(0, ("curthread isn't running"));
#endif /* SMP */
	return (0);
#else /* !STACK */
	return (EOPNOTSUPP);
#endif /* STACK */
}