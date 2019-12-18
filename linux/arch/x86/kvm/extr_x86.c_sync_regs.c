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
struct kvm_vcpu {TYPE_3__* run; } ;
struct TYPE_4__ {int /*<<< orphan*/  events; int /*<<< orphan*/  sregs; int /*<<< orphan*/  regs; } ;
struct TYPE_5__ {TYPE_1__ regs; } ;
struct TYPE_6__ {int kvm_dirty_regs; TYPE_2__ s; } ;

/* Variables and functions */
 int EINVAL ; 
 int KVM_SYNC_X86_EVENTS ; 
 int KVM_SYNC_X86_REGS ; 
 int KVM_SYNC_X86_SREGS ; 
 int KVM_SYNC_X86_VALID_FIELDS ; 
 int /*<<< orphan*/  __set_regs (struct kvm_vcpu*,int /*<<< orphan*/ *) ; 
 scalar_t__ __set_sregs (struct kvm_vcpu*,int /*<<< orphan*/ *) ; 
 scalar_t__ kvm_vcpu_ioctl_x86_set_vcpu_events (struct kvm_vcpu*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sync_regs(struct kvm_vcpu *vcpu)
{
	if (vcpu->run->kvm_dirty_regs & ~KVM_SYNC_X86_VALID_FIELDS)
		return -EINVAL;

	if (vcpu->run->kvm_dirty_regs & KVM_SYNC_X86_REGS) {
		__set_regs(vcpu, &vcpu->run->s.regs.regs);
		vcpu->run->kvm_dirty_regs &= ~KVM_SYNC_X86_REGS;
	}
	if (vcpu->run->kvm_dirty_regs & KVM_SYNC_X86_SREGS) {
		if (__set_sregs(vcpu, &vcpu->run->s.regs.sregs))
			return -EINVAL;
		vcpu->run->kvm_dirty_regs &= ~KVM_SYNC_X86_SREGS;
	}
	if (vcpu->run->kvm_dirty_regs & KVM_SYNC_X86_EVENTS) {
		if (kvm_vcpu_ioctl_x86_set_vcpu_events(
				vcpu, &vcpu->run->s.regs.events))
			return -EINVAL;
		vcpu->run->kvm_dirty_regs &= ~KVM_SYNC_X86_EVENTS;
	}

	return 0;
}