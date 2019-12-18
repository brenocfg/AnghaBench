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
struct kvm_vcpu {int dummy; } ;
struct kvm_mmu {unsigned int root_level; unsigned int last_nonleaf_level; } ;

/* Variables and functions */
 unsigned int PT32_ROOT_LEVEL ; 
 scalar_t__ is_pse (struct kvm_vcpu*) ; 

__attribute__((used)) static void update_last_nonleaf_level(struct kvm_vcpu *vcpu, struct kvm_mmu *mmu)
{
	unsigned root_level = mmu->root_level;

	mmu->last_nonleaf_level = root_level;
	if (root_level == PT32_ROOT_LEVEL && is_pse(vcpu))
		mmu->last_nonleaf_level++;
}