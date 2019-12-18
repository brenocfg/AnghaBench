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
union kvm_mmu_page_role {scalar_t__ word; } ;
typedef  size_t uint ;
struct TYPE_4__ {struct kvm_mmu* mmu; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct kvm_mmu_root_info {scalar_t__ cr3; int /*<<< orphan*/  hpa; } ;
struct kvm_mmu {scalar_t__ root_cr3; int /*<<< orphan*/  root_hpa; int /*<<< orphan*/ * prev_roots; } ;
typedef  scalar_t__ gpa_t ;
struct TYPE_5__ {scalar_t__ word; } ;
struct TYPE_6__ {TYPE_2__ role; } ;

/* Variables and functions */
 size_t KVM_MMU_NUM_PREV_ROOTS ; 
 scalar_t__ VALID_PAGE (int /*<<< orphan*/ ) ; 
 TYPE_3__* page_header (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swap (struct kvm_mmu_root_info,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool cached_root_available(struct kvm_vcpu *vcpu, gpa_t new_cr3,
				  union kvm_mmu_page_role new_role)
{
	uint i;
	struct kvm_mmu_root_info root;
	struct kvm_mmu *mmu = vcpu->arch.mmu;

	root.cr3 = mmu->root_cr3;
	root.hpa = mmu->root_hpa;

	for (i = 0; i < KVM_MMU_NUM_PREV_ROOTS; i++) {
		swap(root, mmu->prev_roots[i]);

		if (new_cr3 == root.cr3 && VALID_PAGE(root.hpa) &&
		    page_header(root.hpa) != NULL &&
		    new_role.word == page_header(root.hpa)->role.word)
			break;
	}

	mmu->root_hpa = root.hpa;
	mmu->root_cr3 = root.cr3;

	return i < KVM_MMU_NUM_PREV_ROOTS;
}