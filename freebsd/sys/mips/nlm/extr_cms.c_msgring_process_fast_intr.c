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
struct thread {int dummy; } ;
struct msgring_thread {int needed; struct thread* thread; } ;

/* Variables and functions */
 int FILTER_HANDLED ; 
 unsigned long long IRQ_MSGRING ; 
 int /*<<< orphan*/  SRQ_INTR ; 
 scalar_t__ TD_AWAITING_INTR (struct thread*) ; 
 int /*<<< orphan*/  TD_CLR_IWAIT (struct thread*) ; 
 int /*<<< orphan*/ * msgring_nintr ; 
 struct msgring_thread* msgring_threads ; 
 int /*<<< orphan*/ * msgring_wakeup_nosleep ; 
 int /*<<< orphan*/ * msgring_wakeup_sleep ; 
 int nlm_cpuid () ; 
 int /*<<< orphan*/  nlm_write_c0_eirr (unsigned long long) ; 
 int /*<<< orphan*/  sched_add (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_lock (struct thread*) ; 
 int /*<<< orphan*/  thread_unlock (struct thread*) ; 

__attribute__((used)) static int
msgring_process_fast_intr(void *arg)
{
	struct msgring_thread *mthd;
	struct thread *td;
	int	cpu;

	cpu = nlm_cpuid();
	mthd = &msgring_threads[cpu];
	msgring_nintr[cpu]++;
	td = mthd->thread;

	/* clear pending interrupts */
	nlm_write_c0_eirr(1ULL << IRQ_MSGRING);

	/* wake up the target thread */
	mthd->needed = 1;
	thread_lock(td);
	if (TD_AWAITING_INTR(td)) {
		msgring_wakeup_sleep[cpu]++;
		TD_CLR_IWAIT(td);
		sched_add(td, SRQ_INTR);
	} else
		msgring_wakeup_nosleep[cpu]++;

	thread_unlock(td);

	return (FILTER_HANDLED);
}