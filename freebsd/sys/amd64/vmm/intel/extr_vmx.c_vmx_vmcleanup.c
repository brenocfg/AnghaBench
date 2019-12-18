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
typedef  int uint16_t ;
struct vmx {TYPE_1__* state; int /*<<< orphan*/  vm; } ;
struct TYPE_2__ {int /*<<< orphan*/  vpid; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_APIC_BASE ; 
 int /*<<< orphan*/  M_VMX ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ apic_access_virtualization (struct vmx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct vmx*,int /*<<< orphan*/ ) ; 
 int vm_get_maxcpus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_unmap_mmio (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vpid_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vmx_vmcleanup(void *arg)
{
	int i;
	struct vmx *vmx = arg;
	uint16_t maxcpus;

	if (apic_access_virtualization(vmx, 0))
		vm_unmap_mmio(vmx->vm, DEFAULT_APIC_BASE, PAGE_SIZE);

	maxcpus = vm_get_maxcpus(vmx->vm);
	for (i = 0; i < maxcpus; i++)
		vpid_free(vmx->state[i].vpid);

	free(vmx, M_VMX);

	return;
}