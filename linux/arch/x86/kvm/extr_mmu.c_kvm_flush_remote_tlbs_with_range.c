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
struct kvm_tlb_range {int dummy; } ;
struct kvm {int dummy; } ;
struct TYPE_2__ {int (* tlb_remote_flush_with_range ) (struct kvm*,struct kvm_tlb_range*) ;} ;

/* Variables and functions */
 int ENOTSUPP ; 
 int /*<<< orphan*/  kvm_flush_remote_tlbs (struct kvm*) ; 
 TYPE_1__* kvm_x86_ops ; 
 int stub1 (struct kvm*,struct kvm_tlb_range*) ; 

__attribute__((used)) static void kvm_flush_remote_tlbs_with_range(struct kvm *kvm,
		struct kvm_tlb_range *range)
{
	int ret = -ENOTSUPP;

	if (range && kvm_x86_ops->tlb_remote_flush_with_range)
		ret = kvm_x86_ops->tlb_remote_flush_with_range(kvm, range);

	if (ret)
		kvm_flush_remote_tlbs(kvm);
}