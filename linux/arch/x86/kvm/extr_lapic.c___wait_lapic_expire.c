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
typedef  unsigned long long u64 ;
struct TYPE_6__ {scalar_t__ tsc_scaling_ratio; int /*<<< orphan*/  virtual_tsc_khz; TYPE_2__* apic; } ;
struct kvm_vcpu {TYPE_3__ arch; } ;
struct TYPE_4__ {unsigned long long timer_advance_ns; } ;
struct TYPE_5__ {TYPE_1__ lapic_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  __delay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_div (unsigned long long,int /*<<< orphan*/ ) ; 
 scalar_t__ kvm_default_tsc_scaling_ratio ; 
 int /*<<< orphan*/  min (unsigned long long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min_t (int /*<<< orphan*/ ,unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  ndelay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsec_to_cycles (struct kvm_vcpu*,unsigned long long) ; 
 int /*<<< orphan*/  u32 ; 

__attribute__((used)) static inline void __wait_lapic_expire(struct kvm_vcpu *vcpu, u64 guest_cycles)
{
	u64 timer_advance_ns = vcpu->arch.apic->lapic_timer.timer_advance_ns;

	/*
	 * If the guest TSC is running at a different ratio than the host, then
	 * convert the delay to nanoseconds to achieve an accurate delay.  Note
	 * that __delay() uses delay_tsc whenever the hardware has TSC, thus
	 * always for VMX enabled hardware.
	 */
	if (vcpu->arch.tsc_scaling_ratio == kvm_default_tsc_scaling_ratio) {
		__delay(min(guest_cycles,
			nsec_to_cycles(vcpu, timer_advance_ns)));
	} else {
		u64 delay_ns = guest_cycles * 1000000ULL;
		do_div(delay_ns, vcpu->arch.virtual_tsc_khz);
		ndelay(min_t(u32, delay_ns, timer_advance_ns));
	}
}