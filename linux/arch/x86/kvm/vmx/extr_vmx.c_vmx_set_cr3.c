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
typedef  int /*<<< orphan*/  u64 ;
struct kvm_vcpu {struct kvm* kvm; } ;
struct kvm {int dummy; } ;
struct TYPE_6__ {scalar_t__ tlb_remote_flush; } ;
struct TYPE_5__ {unsigned long ept_identity_map_addr; int /*<<< orphan*/  ept_pointer_lock; int /*<<< orphan*/  ept_pointers_match; } ;
struct TYPE_4__ {int /*<<< orphan*/  ept_pointer; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPT_POINTER ; 
 int /*<<< orphan*/  EPT_POINTERS_CHECK ; 
 int /*<<< orphan*/  GUEST_CR3 ; 
 int /*<<< orphan*/  construct_eptp (struct kvm_vcpu*,unsigned long) ; 
 scalar_t__ enable_ept ; 
 scalar_t__ enable_unrestricted_guest ; 
 int /*<<< orphan*/  ept_load_pdptrs (struct kvm_vcpu*) ; 
 scalar_t__ is_guest_mode (struct kvm_vcpu*) ; 
 scalar_t__ is_paging (struct kvm_vcpu*) ; 
 unsigned long kvm_read_cr3 (struct kvm_vcpu*) ; 
 TYPE_3__* kvm_x86_ops ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 TYPE_2__* to_kvm_vmx (struct kvm*) ; 
 TYPE_1__* to_vmx (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vmcs_write64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmcs_writel (int /*<<< orphan*/ ,unsigned long) ; 

void vmx_set_cr3(struct kvm_vcpu *vcpu, unsigned long cr3)
{
	struct kvm *kvm = vcpu->kvm;
	unsigned long guest_cr3;
	u64 eptp;

	guest_cr3 = cr3;
	if (enable_ept) {
		eptp = construct_eptp(vcpu, cr3);
		vmcs_write64(EPT_POINTER, eptp);

		if (kvm_x86_ops->tlb_remote_flush) {
			spin_lock(&to_kvm_vmx(kvm)->ept_pointer_lock);
			to_vmx(vcpu)->ept_pointer = eptp;
			to_kvm_vmx(kvm)->ept_pointers_match
				= EPT_POINTERS_CHECK;
			spin_unlock(&to_kvm_vmx(kvm)->ept_pointer_lock);
		}

		if (enable_unrestricted_guest || is_paging(vcpu) ||
		    is_guest_mode(vcpu))
			guest_cr3 = kvm_read_cr3(vcpu);
		else
			guest_cr3 = to_kvm_vmx(kvm)->ept_identity_map_addr;
		ept_load_pdptrs(vcpu);
	}

	vmcs_writel(GUEST_CR3, guest_cr3);
}