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
typedef  scalar_t__ u64 ;
struct TYPE_4__ {TYPE_1__* sie_block; } ;
struct kvm_vcpu {TYPE_2__ arch; int /*<<< orphan*/  kvm; } ;
typedef  scalar_t__ s64 ;
struct TYPE_3__ {scalar_t__ ckc; int* gcr; } ;

/* Variables and functions */
 int CR0_CLOCK_COMPARATOR_SIGN ; 
 int ckc_interrupts_enabled (struct kvm_vcpu*) ; 
 scalar_t__ kvm_s390_get_tod_clock_fast (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ckc_irq_pending(struct kvm_vcpu *vcpu)
{
	const u64 now = kvm_s390_get_tod_clock_fast(vcpu->kvm);
	const u64 ckc = vcpu->arch.sie_block->ckc;

	if (vcpu->arch.sie_block->gcr[0] & CR0_CLOCK_COMPARATOR_SIGN) {
		if ((s64)ckc >= (s64)now)
			return 0;
	} else if (ckc >= now) {
		return 0;
	}
	return ckc_interrupts_enabled(vcpu);
}