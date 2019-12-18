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
typedef  unsigned long uint64_t ;
struct vmx {struct vmcs* vmcs; } ;
struct vmcs {int dummy; } ;
struct vlapic_vtx {struct vmx* vmx; } ;
struct vlapic {size_t vcpuid; int /*<<< orphan*/  vm; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  VMCLEAR (struct vmcs*) ; 
 int /*<<< orphan*/  VMCS_EOI_EXIT (int) ; 
 int /*<<< orphan*/  VMPTRLD (struct vmcs*) ; 
 int /*<<< orphan*/  vcpu_is_running (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *) ; 
 unsigned long vmcs_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmcs_write (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void
vmx_set_tmr(struct vlapic *vlapic, int vector, bool level)
{
	struct vlapic_vtx *vlapic_vtx;
	struct vmx *vmx;
	struct vmcs *vmcs;
	uint64_t mask, val;

	KASSERT(vector >= 0 && vector <= 255, ("invalid vector %d", vector));
	KASSERT(!vcpu_is_running(vlapic->vm, vlapic->vcpuid, NULL),
	    ("vmx_set_tmr: vcpu cannot be running"));

	vlapic_vtx = (struct vlapic_vtx *)vlapic;
	vmx = vlapic_vtx->vmx;
	vmcs = &vmx->vmcs[vlapic->vcpuid];
	mask = 1UL << (vector % 64);

	VMPTRLD(vmcs);
	val = vmcs_read(VMCS_EOI_EXIT(vector));
	if (level)
		val |= mask;
	else
		val &= ~mask;
	vmcs_write(VMCS_EOI_EXIT(vector), val);
	VMCLEAR(vmcs);
}