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
typedef  int u32 ;
struct kvm_vcpu {int dummy; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int /*<<< orphan*/  MIPS_EXC_INT_TIMER ; 
 int /*<<< orphan*/  back_to_back_c0_hazard () ; 
 int /*<<< orphan*/  kvm_mips_freeze_hrtimer (struct kvm_vcpu*,int*) ; 
 int /*<<< orphan*/  kvm_vz_queue_irq (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int read_c0_count () ; 
 int read_gc0_count () ; 
 int /*<<< orphan*/  write_c0_gtoffset (int) ; 
 int /*<<< orphan*/  write_gc0_cause (int) ; 

__attribute__((used)) static void _kvm_vz_restore_htimer(struct kvm_vcpu *vcpu,
				   u32 compare, u32 cause)
{
	u32 start_count, after_count;
	ktime_t freeze_time;
	unsigned long flags;

	/*
	 * Freeze the soft-timer and sync the guest CP0_Count with it. We do
	 * this with interrupts disabled to avoid latency.
	 */
	local_irq_save(flags);
	freeze_time = kvm_mips_freeze_hrtimer(vcpu, &start_count);
	write_c0_gtoffset(start_count - read_c0_count());
	local_irq_restore(flags);

	/* restore guest CP0_Cause, as TI may already be set */
	back_to_back_c0_hazard();
	write_gc0_cause(cause);

	/*
	 * The above sequence isn't atomic and would result in lost timer
	 * interrupts if we're not careful. Detect if a timer interrupt is due
	 * and assert it.
	 */
	back_to_back_c0_hazard();
	after_count = read_gc0_count();
	if (after_count - start_count > compare - start_count - 1)
		kvm_vz_queue_irq(vcpu, MIPS_EXC_INT_TIMER);
}