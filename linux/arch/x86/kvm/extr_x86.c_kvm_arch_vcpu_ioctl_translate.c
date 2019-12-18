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
struct kvm_vcpu {TYPE_1__* kvm; } ;
struct kvm_translation {unsigned long linear_address; int valid; int writeable; scalar_t__ usermode; scalar_t__ physical_address; } ;
typedef  scalar_t__ gpa_t ;
struct TYPE_2__ {int /*<<< orphan*/  srcu; } ;

/* Variables and functions */
 scalar_t__ UNMAPPED_GVA ; 
 scalar_t__ kvm_mmu_gva_to_gpa_system (struct kvm_vcpu*,unsigned long,int /*<<< orphan*/ *) ; 
 int srcu_read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srcu_read_unlock (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vcpu_load (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vcpu_put (struct kvm_vcpu*) ; 

int kvm_arch_vcpu_ioctl_translate(struct kvm_vcpu *vcpu,
				    struct kvm_translation *tr)
{
	unsigned long vaddr = tr->linear_address;
	gpa_t gpa;
	int idx;

	vcpu_load(vcpu);

	idx = srcu_read_lock(&vcpu->kvm->srcu);
	gpa = kvm_mmu_gva_to_gpa_system(vcpu, vaddr, NULL);
	srcu_read_unlock(&vcpu->kvm->srcu, idx);
	tr->physical_address = gpa;
	tr->valid = gpa != UNMAPPED_GVA;
	tr->writeable = 1;
	tr->usermode = 0;

	vcpu_put(vcpu);
	return 0;
}