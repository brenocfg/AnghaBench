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
struct TYPE_6__ {int /*<<< orphan*/ * ivor; } ;
struct kvm_vcpu {TYPE_3__ arch; } ;
struct TYPE_4__ {int /*<<< orphan*/ * ivor_low; int /*<<< orphan*/  features; } ;
struct TYPE_5__ {TYPE_1__ e; } ;
struct kvm_sregs {TYPE_2__ u; } ;

/* Variables and functions */
 size_t BOOKE_IRQPRIO_ALIGNMENT ; 
 size_t BOOKE_IRQPRIO_AP_UNAVAIL ; 
 size_t BOOKE_IRQPRIO_CRITICAL ; 
 size_t BOOKE_IRQPRIO_DATA_STORAGE ; 
 size_t BOOKE_IRQPRIO_DEBUG ; 
 size_t BOOKE_IRQPRIO_DECREMENTER ; 
 size_t BOOKE_IRQPRIO_DTLB_MISS ; 
 size_t BOOKE_IRQPRIO_EXTERNAL ; 
 size_t BOOKE_IRQPRIO_FIT ; 
 size_t BOOKE_IRQPRIO_FP_UNAVAIL ; 
 size_t BOOKE_IRQPRIO_INST_STORAGE ; 
 size_t BOOKE_IRQPRIO_ITLB_MISS ; 
 size_t BOOKE_IRQPRIO_MACHINE_CHECK ; 
 size_t BOOKE_IRQPRIO_PROGRAM ; 
 size_t BOOKE_IRQPRIO_SYSCALL ; 
 size_t BOOKE_IRQPRIO_WATCHDOG ; 
 int /*<<< orphan*/  KVM_SREGS_E_IVOR ; 

int kvmppc_get_sregs_ivor(struct kvm_vcpu *vcpu, struct kvm_sregs *sregs)
{
	sregs->u.e.features |= KVM_SREGS_E_IVOR;

	sregs->u.e.ivor_low[0] = vcpu->arch.ivor[BOOKE_IRQPRIO_CRITICAL];
	sregs->u.e.ivor_low[1] = vcpu->arch.ivor[BOOKE_IRQPRIO_MACHINE_CHECK];
	sregs->u.e.ivor_low[2] = vcpu->arch.ivor[BOOKE_IRQPRIO_DATA_STORAGE];
	sregs->u.e.ivor_low[3] = vcpu->arch.ivor[BOOKE_IRQPRIO_INST_STORAGE];
	sregs->u.e.ivor_low[4] = vcpu->arch.ivor[BOOKE_IRQPRIO_EXTERNAL];
	sregs->u.e.ivor_low[5] = vcpu->arch.ivor[BOOKE_IRQPRIO_ALIGNMENT];
	sregs->u.e.ivor_low[6] = vcpu->arch.ivor[BOOKE_IRQPRIO_PROGRAM];
	sregs->u.e.ivor_low[7] = vcpu->arch.ivor[BOOKE_IRQPRIO_FP_UNAVAIL];
	sregs->u.e.ivor_low[8] = vcpu->arch.ivor[BOOKE_IRQPRIO_SYSCALL];
	sregs->u.e.ivor_low[9] = vcpu->arch.ivor[BOOKE_IRQPRIO_AP_UNAVAIL];
	sregs->u.e.ivor_low[10] = vcpu->arch.ivor[BOOKE_IRQPRIO_DECREMENTER];
	sregs->u.e.ivor_low[11] = vcpu->arch.ivor[BOOKE_IRQPRIO_FIT];
	sregs->u.e.ivor_low[12] = vcpu->arch.ivor[BOOKE_IRQPRIO_WATCHDOG];
	sregs->u.e.ivor_low[13] = vcpu->arch.ivor[BOOKE_IRQPRIO_DTLB_MISS];
	sregs->u.e.ivor_low[14] = vcpu->arch.ivor[BOOKE_IRQPRIO_ITLB_MISS];
	sregs->u.e.ivor_low[15] = vcpu->arch.ivor[BOOKE_IRQPRIO_DEBUG];
	return 0;
}