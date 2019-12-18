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
struct kvmppc_pte {int /*<<< orphan*/  vpage; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvmppc_mmu_pte_vflush (struct kvm_vcpu*,int /*<<< orphan*/ ,int) ; 

void kvmppc_mmu_unmap_page(struct kvm_vcpu *vcpu, struct kvmppc_pte *pte)
{
	kvmppc_mmu_pte_vflush(vcpu, pte->vpage, 0xfffffffffULL);
}