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
struct TYPE_4__ {TYPE_1__* sie_block; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
struct TYPE_3__ {int /*<<< orphan*/  lctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUSTAT_IO_INT ; 
 int IRQ_PEND_IO_MASK ; 
 int /*<<< orphan*/  LCTL_CR6 ; 
 int /*<<< orphan*/  kvm_s390_set_cpuflags (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int pending_irqs_no_gisa (struct kvm_vcpu*) ; 
 scalar_t__ psw_ioint_disabled (struct kvm_vcpu*) ; 

__attribute__((used)) static void set_intercept_indicators_io(struct kvm_vcpu *vcpu)
{
	if (!(pending_irqs_no_gisa(vcpu) & IRQ_PEND_IO_MASK))
		return;
	if (psw_ioint_disabled(vcpu))
		kvm_s390_set_cpuflags(vcpu, CPUSTAT_IO_INT);
	else
		vcpu->arch.sie_block->lctl |= LCTL_CR6;
}