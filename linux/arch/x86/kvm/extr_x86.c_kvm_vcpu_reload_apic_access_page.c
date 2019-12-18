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
struct page {int dummy; } ;
struct kvm_vcpu {int /*<<< orphan*/  kvm; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_apic_access_page_addr ) (struct kvm_vcpu*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int APIC_DEFAULT_PHYS_BASE ; 
 int PAGE_SHIFT ; 
 struct page* gfn_to_page (int /*<<< orphan*/ ,int) ; 
 scalar_t__ is_error_page (struct page*) ; 
 TYPE_1__* kvm_x86_ops ; 
 int /*<<< orphan*/  lapic_in_kernel (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  page_to_phys (struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  stub1 (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

void kvm_vcpu_reload_apic_access_page(struct kvm_vcpu *vcpu)
{
	struct page *page = NULL;

	if (!lapic_in_kernel(vcpu))
		return;

	if (!kvm_x86_ops->set_apic_access_page_addr)
		return;

	page = gfn_to_page(vcpu->kvm, APIC_DEFAULT_PHYS_BASE >> PAGE_SHIFT);
	if (is_error_page(page))
		return;
	kvm_x86_ops->set_apic_access_page_addr(vcpu, page_to_phys(page));

	/*
	 * Do not pin apic access page in memory, the MMU notifier
	 * will call us again if it is migrated or swapped out.
	 */
	put_page(page);
}