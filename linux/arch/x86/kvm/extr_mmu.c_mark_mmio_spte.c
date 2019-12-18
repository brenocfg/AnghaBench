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
typedef  unsigned int u64 ;
struct kvm_vcpu {int dummy; } ;
struct TYPE_2__ {unsigned int generation; } ;

/* Variables and functions */
 unsigned int MMIO_SPTE_GEN_MASK ; 
 unsigned int PAGE_SHIFT ; 
 unsigned int generation_mmio_spte_mask (unsigned int) ; 
 TYPE_1__* kvm_vcpu_memslots (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  mmu_spte_set (unsigned int*,unsigned int) ; 
 unsigned int shadow_mmio_access_mask ; 
 unsigned int shadow_mmio_value ; 
 unsigned int shadow_nonpresent_or_rsvd_mask ; 
 unsigned int shadow_nonpresent_or_rsvd_mask_len ; 
 int /*<<< orphan*/  trace_mark_mmio_spte (unsigned int*,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static void mark_mmio_spte(struct kvm_vcpu *vcpu, u64 *sptep, u64 gfn,
			   unsigned access)
{
	u64 gen = kvm_vcpu_memslots(vcpu)->generation & MMIO_SPTE_GEN_MASK;
	u64 mask = generation_mmio_spte_mask(gen);
	u64 gpa = gfn << PAGE_SHIFT;

	access &= shadow_mmio_access_mask;
	mask |= shadow_mmio_value | access;
	mask |= gpa | shadow_nonpresent_or_rsvd_mask;
	mask |= (gpa & shadow_nonpresent_or_rsvd_mask)
		<< shadow_nonpresent_or_rsvd_mask_len;

	trace_mark_mmio_spte(sptep, gfn, access, gen);
	mmu_spte_set(sptep, mask);
}