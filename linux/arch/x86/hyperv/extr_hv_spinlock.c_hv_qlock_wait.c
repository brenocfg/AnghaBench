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
typedef  scalar_t__ u8 ;

/* Variables and functions */
 int /*<<< orphan*/  HV_X64_MSR_GUEST_IDLE ; 
 scalar_t__ READ_ONCE (scalar_t__) ; 
 scalar_t__ in_nmi () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  rdmsrl (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void hv_qlock_wait(u8 *byte, u8 val)
{
	unsigned long msr_val;
	unsigned long flags;

	if (in_nmi())
		return;

	/*
	 * Reading HV_X64_MSR_GUEST_IDLE MSR tells the hypervisor that the
	 * vCPU can be put into 'idle' state. This 'idle' state is
	 * terminated by an IPI, usually from hv_qlock_kick(), even if
	 * interrupts are disabled on the vCPU.
	 *
	 * To prevent a race against the unlock path it is required to
	 * disable interrupts before accessing the HV_X64_MSR_GUEST_IDLE
	 * MSR. Otherwise, if the IPI from hv_qlock_kick() arrives between
	 * the lock value check and the rdmsrl() then the vCPU might be put
	 * into 'idle' state by the hypervisor and kept in that state for
	 * an unspecified amount of time.
	 */
	local_irq_save(flags);
	/*
	 * Only issue the rdmsrl() when the lock state has not changed.
	 */
	if (READ_ONCE(*byte) == val)
		rdmsrl(HV_X64_MSR_GUEST_IDLE, msr_val);
	local_irq_restore(flags);
}