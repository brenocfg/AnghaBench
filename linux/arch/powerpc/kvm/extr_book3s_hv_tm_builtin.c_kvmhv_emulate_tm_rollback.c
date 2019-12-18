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
struct TYPE_6__ {int ccr; int /*<<< orphan*/  nip; } ;
struct TYPE_4__ {int /*<<< orphan*/  msr; } ;
struct TYPE_5__ {TYPE_3__ regs; int /*<<< orphan*/  tfhar; TYPE_1__ shregs; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_TS_MASK ; 
 int /*<<< orphan*/  copy_from_checkpoint (struct kvm_vcpu*) ; 

void kvmhv_emulate_tm_rollback(struct kvm_vcpu *vcpu)
{
	vcpu->arch.shregs.msr &= ~MSR_TS_MASK;	/* go to N state */
	vcpu->arch.regs.nip = vcpu->arch.tfhar;
	copy_from_checkpoint(vcpu);
	vcpu->arch.regs.ccr = (vcpu->arch.regs.ccr & 0x0fffffff) | 0xa0000000;
}