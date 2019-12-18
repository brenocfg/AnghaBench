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
struct kvm {int dummy; } ;
struct kvm_svm {struct kvm kvm; } ;

/* Variables and functions */
 int GFP_KERNEL_ACCOUNT ; 
 int /*<<< orphan*/  PAGE_KERNEL ; 
 int __GFP_ZERO ; 
 struct kvm_svm* __vmalloc (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct kvm *svm_vm_alloc(void)
{
	struct kvm_svm *kvm_svm = __vmalloc(sizeof(struct kvm_svm),
					    GFP_KERNEL_ACCOUNT | __GFP_ZERO,
					    PAGE_KERNEL);
	return &kvm_svm->kvm;
}