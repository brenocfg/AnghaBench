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
struct TYPE_3__ {int /*<<< orphan*/ * gpr; } ;
struct TYPE_4__ {TYPE_1__ regs; } ;
struct kvm_vcpu {TYPE_2__ arch; int /*<<< orphan*/  kvm; } ;

/* Variables and functions */
 long H_HARDWARE ; 
 long H_SUCCESS ; 
 int MSR_IR ; 
 scalar_t__ kvm_is_radix (int /*<<< orphan*/ ) ; 
 int mfmsr () ; 
 int powernv_get_random_long (int /*<<< orphan*/ *) ; 
 int powernv_get_random_real_mode (int /*<<< orphan*/ *) ; 

long kvmppc_h_random(struct kvm_vcpu *vcpu)
{
	int r;

	/* Only need to do the expensive mfmsr() on radix */
	if (kvm_is_radix(vcpu->kvm) && (mfmsr() & MSR_IR))
		r = powernv_get_random_long(&vcpu->arch.regs.gpr[4]);
	else
		r = powernv_get_random_real_mode(&vcpu->arch.regs.gpr[4]);
	if (r)
		return H_SUCCESS;

	return H_HARDWARE;
}