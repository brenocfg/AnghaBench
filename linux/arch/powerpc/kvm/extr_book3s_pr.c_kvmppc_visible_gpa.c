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
typedef  int ulong ;
typedef  int uint32_t ;
struct TYPE_2__ {int magic_page_pa; } ;
struct kvm_vcpu {int /*<<< orphan*/  kvm; TYPE_1__ arch; } ;
typedef  int gpa_t ;

/* Variables and functions */
 int KVM_PAM ; 
 int MSR_SF ; 
 int PAGE_SHIFT ; 
 int kvm_is_visible_gfn (int /*<<< orphan*/ ,int) ; 
 int kvmppc_get_msr (struct kvm_vcpu*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool kvmppc_visible_gpa(struct kvm_vcpu *vcpu, gpa_t gpa)
{
	ulong mp_pa = vcpu->arch.magic_page_pa;

	if (!(kvmppc_get_msr(vcpu) & MSR_SF))
		mp_pa = (uint32_t)mp_pa;

	gpa &= ~0xFFFULL;
	if (unlikely(mp_pa) && unlikely((mp_pa & KVM_PAM) == (gpa & KVM_PAM))) {
		return true;
	}

	return kvm_is_visible_gfn(vcpu->kvm, gpa >> PAGE_SHIFT);
}