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
struct TYPE_2__ {int load_eoi_exitmap_pending; int /*<<< orphan*/  hflags; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  HF_GUEST_MASK ; 
 int /*<<< orphan*/  KVM_REQ_LOAD_EOI_EXITMAP ; 
 int /*<<< orphan*/  kvm_make_request (int /*<<< orphan*/ ,struct kvm_vcpu*) ; 

__attribute__((used)) static inline void leave_guest_mode(struct kvm_vcpu *vcpu)
{
	vcpu->arch.hflags &= ~HF_GUEST_MASK;

	if (vcpu->arch.load_eoi_exitmap_pending) {
		vcpu->arch.load_eoi_exitmap_pending = false;
		kvm_make_request(KVM_REQ_LOAD_EOI_EXITMAP, vcpu);
	}
}