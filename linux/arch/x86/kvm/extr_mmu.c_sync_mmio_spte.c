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
typedef  int /*<<< orphan*/  u64 ;
struct kvm_vcpu {int dummy; } ;
typedef  scalar_t__ gfn_t ;

/* Variables and functions */
 scalar_t__ get_mmio_spte_gfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_mmio_spte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_mmio_spte (struct kvm_vcpu*,int /*<<< orphan*/ *,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  mmu_spte_clear_no_track (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool sync_mmio_spte(struct kvm_vcpu *vcpu, u64 *sptep, gfn_t gfn,
			   unsigned access, int *nr_present)
{
	if (unlikely(is_mmio_spte(*sptep))) {
		if (gfn != get_mmio_spte_gfn(*sptep)) {
			mmu_spte_clear_no_track(sptep);
			return true;
		}

		(*nr_present)++;
		mark_mmio_spte(vcpu, sptep, gfn, access);
		return true;
	}

	return false;
}