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
struct vmx {int dummy; } ;

/* Variables and functions */
 int CR0_PG ; 
 int EFER_LMA ; 
 int EFER_LME ; 
 int HANDLED ; 
 int UNHANDLED ; 
 int /*<<< orphan*/  VMCS_CR0_SHADOW ; 
 int /*<<< orphan*/  VMCS_ENTRY_CTLS ; 
 int /*<<< orphan*/  VMCS_GUEST_CR0 ; 
 int /*<<< orphan*/  VMCS_GUEST_IA32_EFER ; 
 int VM_ENTRY_GUEST_LMA ; 
 int cr0_ones_mask ; 
 int cr0_zeros_mask ; 
 int vmcs_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmcs_write (int /*<<< orphan*/ ,int) ; 
 int vmx_get_guest_reg (struct vmx*,int,int) ; 

__attribute__((used)) static int
vmx_emulate_cr0_access(struct vmx *vmx, int vcpu, uint64_t exitqual)
{
	uint64_t crval, regval;

	/* We only handle mov to %cr0 at this time */
	if ((exitqual & 0xf0) != 0x00)
		return (UNHANDLED);

	regval = vmx_get_guest_reg(vmx, vcpu, (exitqual >> 8) & 0xf);

	vmcs_write(VMCS_CR0_SHADOW, regval);

	crval = regval | cr0_ones_mask;
	crval &= ~cr0_zeros_mask;
	vmcs_write(VMCS_GUEST_CR0, crval);

	if (regval & CR0_PG) {
		uint64_t efer, entry_ctls;

		/*
		 * If CR0.PG is 1 and EFER.LME is 1 then EFER.LMA and
		 * the "IA-32e mode guest" bit in VM-entry control must be
		 * equal.
		 */
		efer = vmcs_read(VMCS_GUEST_IA32_EFER);
		if (efer & EFER_LME) {
			efer |= EFER_LMA;
			vmcs_write(VMCS_GUEST_IA32_EFER, efer);
			entry_ctls = vmcs_read(VMCS_ENTRY_CTLS);
			entry_ctls |= VM_ENTRY_GUEST_LMA;
			vmcs_write(VMCS_ENTRY_CTLS, entry_ctls);
		}
	}

	return (HANDLED);
}