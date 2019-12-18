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
typedef  int u64 ;
struct kvmppc_pte {int eaddr; int /*<<< orphan*/  vpage; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* esid_to_vsid ) (struct kvm_vcpu*,int,int*) ;} ;
struct TYPE_4__ {TYPE_1__ mmu; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;

/* Variables and functions */
 int SID_SHIFT ; 
 int VSID_64K ; 
 int /*<<< orphan*/  kvmppc_mmu_pte_vflush (struct kvm_vcpu*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct kvm_vcpu*,int,int*) ; 

void kvmppc_mmu_unmap_page(struct kvm_vcpu *vcpu, struct kvmppc_pte *pte)
{
	u64 mask = 0xfffffffffULL;
	u64 vsid;

	vcpu->arch.mmu.esid_to_vsid(vcpu, pte->eaddr >> SID_SHIFT, &vsid);
	if (vsid & VSID_64K)
		mask = 0xffffffff0ULL;
	kvmppc_mmu_pte_vflush(vcpu, pte->vpage, mask);
}