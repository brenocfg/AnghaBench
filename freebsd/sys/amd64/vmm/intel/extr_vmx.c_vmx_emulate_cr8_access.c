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
typedef  int uint64_t ;
struct vmx {int /*<<< orphan*/  vm; } ;
struct vlapic {int dummy; } ;

/* Variables and functions */
 int HANDLED ; 
 int UNHANDLED ; 
 int vlapic_get_cr8 (struct vlapic*) ; 
 int /*<<< orphan*/  vlapic_set_cr8 (struct vlapic*,int) ; 
 struct vlapic* vm_lapic (int /*<<< orphan*/ ,int) ; 
 int vmx_get_guest_reg (struct vmx*,int,int) ; 
 int /*<<< orphan*/  vmx_set_guest_reg (struct vmx*,int,int,int) ; 

__attribute__((used)) static int
vmx_emulate_cr8_access(struct vmx *vmx, int vcpu, uint64_t exitqual)
{
	struct vlapic *vlapic;
	uint64_t cr8;
	int regnum;

	/* We only handle mov %cr8 to/from a register at this time. */
	if ((exitqual & 0xe0) != 0x00) {
		return (UNHANDLED);
	}

	vlapic = vm_lapic(vmx->vm, vcpu);
	regnum = (exitqual >> 8) & 0xf;
	if (exitqual & 0x10) {
		cr8 = vlapic_get_cr8(vlapic);
		vmx_set_guest_reg(vmx, vcpu, regnum, cr8);
	} else {
		cr8 = vmx_get_guest_reg(vmx, vcpu, regnum);
		vlapic_set_cr8(vlapic, cr8);
	}

	return (HANDLED);
}