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
struct kvm {int dummy; } ;

/* Variables and functions */
 scalar_t__ KVM_ADDRESS_SPACE_NUM ; 
 int KVM_MEMSLOT_GEN_UPDATE_IN_PROGRESS ; 
 int MMIO_SPTE_GEN_MASK ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  kvm_debug_ratelimited (char*) ; 
 int /*<<< orphan*/  kvm_mmu_zap_all_fast (struct kvm*) ; 
 scalar_t__ unlikely (int) ; 

void kvm_mmu_invalidate_mmio_sptes(struct kvm *kvm, u64 gen)
{
	WARN_ON(gen & KVM_MEMSLOT_GEN_UPDATE_IN_PROGRESS);

	gen &= MMIO_SPTE_GEN_MASK;

	/*
	 * Generation numbers are incremented in multiples of the number of
	 * address spaces in order to provide unique generations across all
	 * address spaces.  Strip what is effectively the address space
	 * modifier prior to checking for a wrap of the MMIO generation so
	 * that a wrap in any address space is detected.
	 */
	gen &= ~((u64)KVM_ADDRESS_SPACE_NUM - 1);

	/*
	 * The very rare case: if the MMIO generation number has wrapped,
	 * zap all shadow pages.
	 */
	if (unlikely(gen == 0)) {
		kvm_debug_ratelimited("kvm: zapping shadow pages for mmio generation wraparound\n");
		kvm_mmu_zap_all_fast(kvm);
	}
}