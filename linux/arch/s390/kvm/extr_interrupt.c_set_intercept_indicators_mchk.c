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
struct TYPE_3__ {int /*<<< orphan*/  lctl; int /*<<< orphan*/  ictl; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICTL_LPSW ; 
 int IRQ_PEND_MCHK_MASK ; 
 int /*<<< orphan*/  LCTL_CR14 ; 
 int pending_irqs_no_gisa (struct kvm_vcpu*) ; 
 scalar_t__ psw_mchk_disabled (struct kvm_vcpu*) ; 

__attribute__((used)) static void set_intercept_indicators_mchk(struct kvm_vcpu *vcpu)
{
	if (!(pending_irqs_no_gisa(vcpu) & IRQ_PEND_MCHK_MASK))
		return;
	if (psw_mchk_disabled(vcpu))
		vcpu->arch.sie_block->ictl |= ICTL_LPSW;
	else
		vcpu->arch.sie_block->lctl |= LCTL_CR14;
}