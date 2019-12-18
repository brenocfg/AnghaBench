#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u64 ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  kvmppc_mmu_pte_vflush_64k (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  kvmppc_mmu_pte_vflush_long (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  kvmppc_mmu_pte_vflush_short (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  trace_kvm_book3s_mmu_flush (char*,struct kvm_vcpu*,int,int) ; 

void kvmppc_mmu_pte_vflush(struct kvm_vcpu *vcpu, u64 guest_vp, u64 vp_mask)
{
	trace_kvm_book3s_mmu_flush("v", vcpu, guest_vp, vp_mask);
	guest_vp &= vp_mask;

	switch(vp_mask) {
	case 0xfffffffffULL:
		kvmppc_mmu_pte_vflush_short(vcpu, guest_vp);
		break;
#ifdef CONFIG_PPC_BOOK3S_64
	case 0xffffffff0ULL:
		kvmppc_mmu_pte_vflush_64k(vcpu, guest_vp);
		break;
#endif
	case 0xffffff000ULL:
		kvmppc_mmu_pte_vflush_long(vcpu, guest_vp);
		break;
	default:
		WARN_ON(1);
		return;
	}
}