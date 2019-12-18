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
struct vcpu_vmx {TYPE_1__* loaded_vmcs; } ;
struct kvm_vcpu {int dummy; } ;
struct TYPE_2__ {int soft_vnmi_blocked; int nmi_known_unmasked; } ;

/* Variables and functions */
 int /*<<< orphan*/  GUEST_INTERRUPTIBILITY_INFO ; 
 int GUEST_INTR_STATE_NMI ; 
 int /*<<< orphan*/  enable_vnmi ; 
 struct vcpu_vmx* to_vmx (struct kvm_vcpu*) ; 
 int vmcs_read32 (int /*<<< orphan*/ ) ; 

bool vmx_get_nmi_mask(struct kvm_vcpu *vcpu)
{
	struct vcpu_vmx *vmx = to_vmx(vcpu);
	bool masked;

	if (!enable_vnmi)
		return vmx->loaded_vmcs->soft_vnmi_blocked;
	if (vmx->loaded_vmcs->nmi_known_unmasked)
		return false;
	masked = vmcs_read32(GUEST_INTERRUPTIBILITY_INFO) & GUEST_INTR_STATE_NMI;
	vmx->loaded_vmcs->nmi_known_unmasked = !masked;
	return masked;
}