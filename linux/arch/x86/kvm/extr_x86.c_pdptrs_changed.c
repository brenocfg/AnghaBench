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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_4__ {TYPE_1__* walk_mmu; int /*<<< orphan*/  regs_avail; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
typedef  int /*<<< orphan*/  pdpte ;
typedef  int gfn_t ;
struct TYPE_3__ {int /*<<< orphan*/  pdptrs; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int PFERR_USER_MASK ; 
 int PFERR_WRITE_MASK ; 
 int /*<<< orphan*/  VCPU_EXREG_PDPTR ; 
 int /*<<< orphan*/  is_pae_paging (struct kvm_vcpu*) ; 
 int kvm_read_cr3 (struct kvm_vcpu*) ; 
 int kvm_read_nested_guest_page (struct kvm_vcpu*,int,int /*<<< orphan*/ *,int,int,int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,unsigned long*) ; 

bool pdptrs_changed(struct kvm_vcpu *vcpu)
{
	u64 pdpte[ARRAY_SIZE(vcpu->arch.walk_mmu->pdptrs)];
	bool changed = true;
	int offset;
	gfn_t gfn;
	int r;

	if (!is_pae_paging(vcpu))
		return false;

	if (!test_bit(VCPU_EXREG_PDPTR,
		      (unsigned long *)&vcpu->arch.regs_avail))
		return true;

	gfn = (kvm_read_cr3(vcpu) & 0xffffffe0ul) >> PAGE_SHIFT;
	offset = (kvm_read_cr3(vcpu) & 0xffffffe0ul) & (PAGE_SIZE - 1);
	r = kvm_read_nested_guest_page(vcpu, gfn, pdpte, offset, sizeof(pdpte),
				       PFERR_USER_MASK | PFERR_WRITE_MASK);
	if (r < 0)
		goto out;
	changed = memcmp(pdpte, vcpu->arch.walk_mmu->pdptrs, sizeof(pdpte)) != 0;
out:

	return changed;
}