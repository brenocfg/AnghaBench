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
struct kvmppc_xive {int /*<<< orphan*/  mapping_lock; scalar_t__ mapping; } ;
struct TYPE_2__ {struct kvmppc_xive* xive; } ;
struct kvm {TYPE_1__ arch; } ;
typedef  unsigned long long pgoff_t ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long KVMPPC_XIVE_NR_IRQS ; 
 unsigned long long KVM_XIVE_ESB_PAGE_OFFSET ; 
 unsigned long long PAGE_SHIFT ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned long) ; 
 int /*<<< orphan*/  unmap_mapping_range (scalar_t__,unsigned long long,unsigned long long,int) ; 

__attribute__((used)) static int kvmppc_xive_native_reset_mapped(struct kvm *kvm, unsigned long irq)
{
	struct kvmppc_xive *xive = kvm->arch.xive;
	pgoff_t esb_pgoff = KVM_XIVE_ESB_PAGE_OFFSET + irq * 2;

	if (irq >= KVMPPC_XIVE_NR_IRQS)
		return -EINVAL;

	/*
	 * Clear the ESB pages of the IRQ number being mapped (or
	 * unmapped) into the guest and let the the VM fault handler
	 * repopulate with the appropriate ESB pages (device or IC)
	 */
	pr_debug("clearing esb pages for girq 0x%lx\n", irq);
	mutex_lock(&xive->mapping_lock);
	if (xive->mapping)
		unmap_mapping_range(xive->mapping,
				    esb_pgoff << PAGE_SHIFT,
				    2ull << PAGE_SHIFT, 1);
	mutex_unlock(&xive->mapping_lock);
	return 0;
}