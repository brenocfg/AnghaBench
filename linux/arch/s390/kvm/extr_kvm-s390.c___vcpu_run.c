#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  sie_block; } ;
struct kvm_vcpu {void* srcu_idx; TYPE_5__* kvm; TYPE_4__* run; TYPE_1__ arch; } ;
struct TYPE_10__ {int /*<<< orphan*/  srcu; } ;
struct TYPE_7__ {int /*<<< orphan*/  gprs; } ;
struct TYPE_8__ {TYPE_2__ regs; } ;
struct TYPE_9__ {TYPE_3__ s; } ;

/* Variables and functions */
 int /*<<< orphan*/  __disable_cpu_timer_accounting (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  __enable_cpu_timer_accounting (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  guest_enter_irqoff () ; 
 int /*<<< orphan*/  guest_exit_irqoff () ; 
 int /*<<< orphan*/  guestdbg_exit_pending (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int sie64a (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal_pending (int /*<<< orphan*/ ) ; 
 void* srcu_read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srcu_read_unlock (int /*<<< orphan*/ *,void*) ; 
 int vcpu_post_run (struct kvm_vcpu*,int) ; 
 int vcpu_pre_run (struct kvm_vcpu*) ; 

__attribute__((used)) static int __vcpu_run(struct kvm_vcpu *vcpu)
{
	int rc, exit_reason;

	/*
	 * We try to hold kvm->srcu during most of vcpu_run (except when run-
	 * ning the guest), so that memslots (and other stuff) are protected
	 */
	vcpu->srcu_idx = srcu_read_lock(&vcpu->kvm->srcu);

	do {
		rc = vcpu_pre_run(vcpu);
		if (rc)
			break;

		srcu_read_unlock(&vcpu->kvm->srcu, vcpu->srcu_idx);
		/*
		 * As PF_VCPU will be used in fault handler, between
		 * guest_enter and guest_exit should be no uaccess.
		 */
		local_irq_disable();
		guest_enter_irqoff();
		__disable_cpu_timer_accounting(vcpu);
		local_irq_enable();
		exit_reason = sie64a(vcpu->arch.sie_block,
				     vcpu->run->s.regs.gprs);
		local_irq_disable();
		__enable_cpu_timer_accounting(vcpu);
		guest_exit_irqoff();
		local_irq_enable();
		vcpu->srcu_idx = srcu_read_lock(&vcpu->kvm->srcu);

		rc = vcpu_post_run(vcpu, exit_reason);
	} while (!signal_pending(current) && !guestdbg_exit_pending(vcpu) && !rc);

	srcu_read_unlock(&vcpu->kvm->srcu, vcpu->srcu_idx);
	return rc;
}