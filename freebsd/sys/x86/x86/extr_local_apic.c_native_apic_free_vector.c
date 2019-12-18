#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
struct thread {int dummy; } ;
struct TYPE_2__ {scalar_t__* la_ioint_irqs; } ;

/* Variables and functions */
 scalar_t__ APIC_IO_INTS ; 
 scalar_t__ APIC_NUM_IOINTS ; 
 scalar_t__ IDT_DTRACE_RET ; 
 scalar_t__ IDT_SYSCALL ; 
 scalar_t__ IRQ_FREE ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  apic_cpuid (scalar_t__) ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  icu_lock ; 
 TYPE_1__* lapics ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 scalar_t__ num_io_irqs ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  rebooting ; 
 int /*<<< orphan*/  sched_bind (struct thread*,int /*<<< orphan*/ ) ; 
 scalar_t__ sched_is_bound (struct thread*) ; 
 int /*<<< orphan*/  sched_unbind (struct thread*) ; 
 int /*<<< orphan*/  thread_lock (struct thread*) ; 
 int /*<<< orphan*/  thread_unlock (struct thread*) ; 

__attribute__((used)) static void
native_apic_free_vector(u_int apic_id, u_int vector, u_int irq)
{
	struct thread *td;

	KASSERT(vector >= APIC_IO_INTS && vector != IDT_SYSCALL &&
	    vector <= APIC_IO_INTS + APIC_NUM_IOINTS,
	    ("Vector %u does not map to an IRQ line", vector));
	KASSERT(irq < num_io_irqs, ("Invalid IRQ %u", irq));
	KASSERT(lapics[apic_id].la_ioint_irqs[vector - APIC_IO_INTS] ==
	    irq, ("IRQ mismatch"));
#ifdef KDTRACE_HOOKS
	KASSERT(vector != IDT_DTRACE_RET,
	    ("Attempt to overwrite DTrace entry"));
#endif

	/*
	 * Bind us to the cpu that owned the vector before freeing it so
	 * we don't lose an interrupt delivery race.
	 */
	td = curthread;
	if (!rebooting) {
		thread_lock(td);
		if (sched_is_bound(td))
			panic("apic_free_vector: Thread already bound.\n");
		sched_bind(td, apic_cpuid(apic_id));
		thread_unlock(td);
	}
	mtx_lock_spin(&icu_lock);
	lapics[apic_id].la_ioint_irqs[vector - APIC_IO_INTS] = IRQ_FREE;
	mtx_unlock_spin(&icu_lock);
	if (!rebooting) {
		thread_lock(td);
		sched_unbind(td);
		thread_unlock(td);
	}
}