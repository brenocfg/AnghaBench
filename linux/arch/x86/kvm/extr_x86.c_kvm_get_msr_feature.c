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
struct kvm_msr_entry {int index; int /*<<< orphan*/  data; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_msr_feature ) (struct kvm_msr_entry*) ;} ;

/* Variables and functions */
#define  MSR_IA32_ARCH_CAPABILITIES 129 
#define  MSR_IA32_UCODE_REV 128 
 int /*<<< orphan*/  kvm_get_arch_capabilities () ; 
 TYPE_1__* kvm_x86_ops ; 
 int /*<<< orphan*/  rdmsrl_safe (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct kvm_msr_entry*) ; 

__attribute__((used)) static int kvm_get_msr_feature(struct kvm_msr_entry *msr)
{
	switch (msr->index) {
	case MSR_IA32_ARCH_CAPABILITIES:
		msr->data = kvm_get_arch_capabilities();
		break;
	case MSR_IA32_UCODE_REV:
		rdmsrl_safe(msr->index, &msr->data);
		break;
	default:
		if (kvm_x86_ops->get_msr_feature(msr))
			return 1;
	}
	return 0;
}