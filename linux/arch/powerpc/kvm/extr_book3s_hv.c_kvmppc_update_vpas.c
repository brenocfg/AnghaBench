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
struct TYPE_4__ {scalar_t__ update_pending; scalar_t__ pinned_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  vpa_update_lock; TYPE_2__ slb_shadow; scalar_t__ dtl_index; TYPE_2__ dtl; scalar_t__ dtl_ptr; TYPE_2__ vpa; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_vpa (struct kvm_vcpu*,scalar_t__) ; 
 int /*<<< orphan*/  kvmppc_update_vpa (struct kvm_vcpu*,TYPE_2__*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void kvmppc_update_vpas(struct kvm_vcpu *vcpu)
{
	if (!(vcpu->arch.vpa.update_pending ||
	      vcpu->arch.slb_shadow.update_pending ||
	      vcpu->arch.dtl.update_pending))
		return;

	spin_lock(&vcpu->arch.vpa_update_lock);
	if (vcpu->arch.vpa.update_pending) {
		kvmppc_update_vpa(vcpu, &vcpu->arch.vpa);
		if (vcpu->arch.vpa.pinned_addr)
			init_vpa(vcpu, vcpu->arch.vpa.pinned_addr);
	}
	if (vcpu->arch.dtl.update_pending) {
		kvmppc_update_vpa(vcpu, &vcpu->arch.dtl);
		vcpu->arch.dtl_ptr = vcpu->arch.dtl.pinned_addr;
		vcpu->arch.dtl_index = 0;
	}
	if (vcpu->arch.slb_shadow.update_pending)
		kvmppc_update_vpa(vcpu, &vcpu->arch.slb_shadow);
	spin_unlock(&vcpu->arch.vpa_update_lock);
}