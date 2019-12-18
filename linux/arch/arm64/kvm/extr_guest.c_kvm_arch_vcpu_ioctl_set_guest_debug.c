#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  external_debug_state; } ;
struct kvm_vcpu {int guest_debug; TYPE_1__ arch; } ;
struct kvm_guest_debug {int control; int /*<<< orphan*/  arch; } ;

/* Variables and functions */
 int EINVAL ; 
 int KVM_GUESTDBG_ENABLE ; 
 int KVM_GUESTDBG_USE_HW ; 
 int KVM_GUESTDBG_VALID_MASK ; 
 int /*<<< orphan*/  trace_kvm_set_guest_debug (struct kvm_vcpu*,int) ; 

int kvm_arch_vcpu_ioctl_set_guest_debug(struct kvm_vcpu *vcpu,
					struct kvm_guest_debug *dbg)
{
	int ret = 0;

	trace_kvm_set_guest_debug(vcpu, dbg->control);

	if (dbg->control & ~KVM_GUESTDBG_VALID_MASK) {
		ret = -EINVAL;
		goto out;
	}

	if (dbg->control & KVM_GUESTDBG_ENABLE) {
		vcpu->guest_debug = dbg->control;

		/* Hardware assisted Break and Watch points */
		if (vcpu->guest_debug & KVM_GUESTDBG_USE_HW) {
			vcpu->arch.external_debug_state = dbg->arch;
		}

	} else {
		/* If not enabled clear all flags */
		vcpu->guest_debug = 0;
	}

out:
	return ret;
}