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
struct kvmppc_pte {int eaddr; int raddr; int may_execute; int may_read; int may_write; int /*<<< orphan*/  vpage; int /*<<< orphan*/  page_size; } ;
struct TYPE_2__ {int magic_page_ea; int magic_page_pa; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
typedef  int gva_t ;

/* Variables and functions */
 int ENOENT ; 
 int KVM_PAM ; 
 int /*<<< orphan*/  MMU_PAGE_4K ; 
 int MSR_PR ; 
 int kvmppc_get_msr (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_mmu_book3s_32_ea_to_vp (struct kvm_vcpu*,int,int) ; 
 int kvmppc_mmu_book3s_32_xlate_bat (struct kvm_vcpu*,int,struct kvmppc_pte*,int,int) ; 
 int kvmppc_mmu_book3s_32_xlate_pte (struct kvm_vcpu*,int,struct kvmppc_pte*,int,int,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int kvmppc_mmu_book3s_32_xlate(struct kvm_vcpu *vcpu, gva_t eaddr,
				      struct kvmppc_pte *pte, bool data,
				      bool iswrite)
{
	int r;
	ulong mp_ea = vcpu->arch.magic_page_ea;

	pte->eaddr = eaddr;
	pte->page_size = MMU_PAGE_4K;

	/* Magic page override */
	if (unlikely(mp_ea) &&
	    unlikely((eaddr & ~0xfffULL) == (mp_ea & ~0xfffULL)) &&
	    !(kvmppc_get_msr(vcpu) & MSR_PR)) {
		pte->vpage = kvmppc_mmu_book3s_32_ea_to_vp(vcpu, eaddr, data);
		pte->raddr = vcpu->arch.magic_page_pa | (pte->raddr & 0xfff);
		pte->raddr &= KVM_PAM;
		pte->may_execute = true;
		pte->may_read = true;
		pte->may_write = true;

		return 0;
	}

	r = kvmppc_mmu_book3s_32_xlate_bat(vcpu, eaddr, pte, data, iswrite);
	if (r < 0)
		r = kvmppc_mmu_book3s_32_xlate_pte(vcpu, eaddr, pte,
						   data, iswrite, true);
	if (r == -ENOENT)
		r = kvmppc_mmu_book3s_32_xlate_pte(vcpu, eaddr, pte,
						   data, iswrite, false);

	return r;
}