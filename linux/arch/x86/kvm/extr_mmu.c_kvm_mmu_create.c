#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint ;
struct TYPE_7__ {void** prev_roots; void* translate_gpa; scalar_t__ root_cr3; void* root_hpa; } ;
struct TYPE_5__ {int /*<<< orphan*/  translate_gpa; } ;
struct TYPE_6__ {TYPE_3__ guest_mmu; TYPE_3__ root_mmu; TYPE_1__ nested_mmu; TYPE_3__* walk_mmu; TYPE_3__* mmu; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;

/* Variables and functions */
 void* INVALID_PAGE ; 
 size_t KVM_MMU_NUM_PREV_ROOTS ; 
 void* KVM_MMU_ROOT_INFO_INVALID ; 
 int alloc_mmu_pages (struct kvm_vcpu*,TYPE_3__*) ; 
 int /*<<< orphan*/  free_mmu_pages (TYPE_3__*) ; 
 void* translate_gpa ; 
 int /*<<< orphan*/  translate_nested_gpa ; 

int kvm_mmu_create(struct kvm_vcpu *vcpu)
{
	uint i;
	int ret;

	vcpu->arch.mmu = &vcpu->arch.root_mmu;
	vcpu->arch.walk_mmu = &vcpu->arch.root_mmu;

	vcpu->arch.root_mmu.root_hpa = INVALID_PAGE;
	vcpu->arch.root_mmu.root_cr3 = 0;
	vcpu->arch.root_mmu.translate_gpa = translate_gpa;
	for (i = 0; i < KVM_MMU_NUM_PREV_ROOTS; i++)
		vcpu->arch.root_mmu.prev_roots[i] = KVM_MMU_ROOT_INFO_INVALID;

	vcpu->arch.guest_mmu.root_hpa = INVALID_PAGE;
	vcpu->arch.guest_mmu.root_cr3 = 0;
	vcpu->arch.guest_mmu.translate_gpa = translate_gpa;
	for (i = 0; i < KVM_MMU_NUM_PREV_ROOTS; i++)
		vcpu->arch.guest_mmu.prev_roots[i] = KVM_MMU_ROOT_INFO_INVALID;

	vcpu->arch.nested_mmu.translate_gpa = translate_nested_gpa;

	ret = alloc_mmu_pages(vcpu, &vcpu->arch.guest_mmu);
	if (ret)
		return ret;

	ret = alloc_mmu_pages(vcpu, &vcpu->arch.root_mmu);
	if (ret)
		goto fail_allocate_root;

	return ret;
 fail_allocate_root:
	free_mmu_pages(&vcpu->arch.guest_mmu);
	return ret;
}