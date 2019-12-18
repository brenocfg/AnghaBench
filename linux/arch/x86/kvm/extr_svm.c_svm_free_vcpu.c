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
struct TYPE_5__ {struct vcpu_svm* guest_fpu; struct vcpu_svm* user_fpu; } ;
struct TYPE_6__ {TYPE_2__ arch; } ;
struct TYPE_4__ {int /*<<< orphan*/  msrpm; int /*<<< orphan*/  hsave; } ;
struct vcpu_svm {TYPE_3__ vcpu; TYPE_1__ nested; int /*<<< orphan*/  msrpm; int /*<<< orphan*/  vmcb_pa; int /*<<< orphan*/  vmcb; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSRPM_ALLOC_ORDER ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  __free_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __free_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int __sme_clr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct vcpu_svm*) ; 
 int /*<<< orphan*/  kvm_vcpu_cache ; 
 int /*<<< orphan*/  kvm_vcpu_uninit (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  pfn_to_page (int) ; 
 int /*<<< orphan*/  svm_clear_current_vmcb (int /*<<< orphan*/ ) ; 
 struct vcpu_svm* to_svm (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  virt_to_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  x86_fpu_cache ; 

__attribute__((used)) static void svm_free_vcpu(struct kvm_vcpu *vcpu)
{
	struct vcpu_svm *svm = to_svm(vcpu);

	/*
	 * The vmcb page can be recycled, causing a false negative in
	 * svm_vcpu_load(). So, ensure that no logical CPU has this
	 * vmcb page recorded as its current vmcb.
	 */
	svm_clear_current_vmcb(svm->vmcb);

	__free_page(pfn_to_page(__sme_clr(svm->vmcb_pa) >> PAGE_SHIFT));
	__free_pages(virt_to_page(svm->msrpm), MSRPM_ALLOC_ORDER);
	__free_page(virt_to_page(svm->nested.hsave));
	__free_pages(virt_to_page(svm->nested.msrpm), MSRPM_ALLOC_ORDER);
	kvm_vcpu_uninit(vcpu);
	kmem_cache_free(x86_fpu_cache, svm->vcpu.arch.user_fpu);
	kmem_cache_free(x86_fpu_cache, svm->vcpu.arch.guest_fpu);
	kmem_cache_free(kvm_vcpu_cache, svm);
}