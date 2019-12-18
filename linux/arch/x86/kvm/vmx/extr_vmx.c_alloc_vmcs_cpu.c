#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int shadow_vmcs; int /*<<< orphan*/  revision_id; } ;
struct vmcs {TYPE_1__ hdr; } ;
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_4__ {int /*<<< orphan*/  revision_id; int /*<<< orphan*/  size; int /*<<< orphan*/  order; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_EVMCS_VERSION ; 
 struct page* __alloc_pages_node (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cpu_to_node (int) ; 
 int /*<<< orphan*/  enable_evmcs ; 
 int /*<<< orphan*/  memset (struct vmcs*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vmcs* page_address (struct page*) ; 
 scalar_t__ static_branch_unlikely (int /*<<< orphan*/ *) ; 
 TYPE_2__ vmcs_config ; 

struct vmcs *alloc_vmcs_cpu(bool shadow, int cpu, gfp_t flags)
{
	int node = cpu_to_node(cpu);
	struct page *pages;
	struct vmcs *vmcs;

	pages = __alloc_pages_node(node, flags, vmcs_config.order);
	if (!pages)
		return NULL;
	vmcs = page_address(pages);
	memset(vmcs, 0, vmcs_config.size);

	/* KVM supports Enlightened VMCS v1 only */
	if (static_branch_unlikely(&enable_evmcs))
		vmcs->hdr.revision_id = KVM_EVMCS_VERSION;
	else
		vmcs->hdr.revision_id = vmcs_config.revision_id;

	if (shadow)
		vmcs->hdr.shadow_vmcs = 1;
	return vmcs;
}