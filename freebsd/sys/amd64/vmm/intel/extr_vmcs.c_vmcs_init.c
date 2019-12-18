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
typedef  int u_long ;
struct vmcs {int dummy; } ;

/* Variables and functions */
 int CR4_VMXE ; 
 int /*<<< orphan*/  VMCLEAR (struct vmcs*) ; 
 int /*<<< orphan*/  VMCS_HOST_CR0 ; 
 int /*<<< orphan*/  VMCS_HOST_CR4 ; 
 int /*<<< orphan*/  VMCS_HOST_CS_SELECTOR ; 
 int /*<<< orphan*/  VMCS_HOST_DS_SELECTOR ; 
 int /*<<< orphan*/  VMCS_HOST_ES_SELECTOR ; 
 int /*<<< orphan*/  VMCS_HOST_FS_BASE ; 
 int /*<<< orphan*/  VMCS_HOST_FS_SELECTOR ; 
 int /*<<< orphan*/  VMCS_HOST_GS_SELECTOR ; 
 int /*<<< orphan*/  VMCS_HOST_IA32_EFER ; 
 int /*<<< orphan*/  VMCS_HOST_IA32_PAT ; 
 int /*<<< orphan*/  VMCS_HOST_IDTR_BASE ; 
 int /*<<< orphan*/  VMCS_HOST_RIP ; 
 int /*<<< orphan*/  VMCS_HOST_SS_SELECTOR ; 
 int /*<<< orphan*/  VMCS_HOST_TR_SELECTOR ; 
 int /*<<< orphan*/  VMCS_LINK_POINTER ; 
 int /*<<< orphan*/  VMPTRLD (struct vmcs*) ; 
 scalar_t__ no_flush_rsb ; 
 int vmm_get_host_codesel () ; 
 int vmm_get_host_cr0 () ; 
 int vmm_get_host_cr4 () ; 
 int vmm_get_host_datasel () ; 
 int vmm_get_host_efer () ; 
 int vmm_get_host_fsbase () ; 
 int vmm_get_host_idtrbase () ; 
 int vmm_get_host_pat () ; 
 int vmm_get_host_tsssel () ; 
 int vmwrite (int /*<<< orphan*/ ,int) ; 
 scalar_t__ vmx_exit_guest ; 
 scalar_t__ vmx_exit_guest_flush_rsb ; 

int
vmcs_init(struct vmcs *vmcs)
{
	int error, codesel, datasel, tsssel;
	u_long cr0, cr4, efer;
	uint64_t pat, fsbase, idtrbase;

	codesel = vmm_get_host_codesel();
	datasel = vmm_get_host_datasel();
	tsssel = vmm_get_host_tsssel();

	/*
	 * Make sure we have a "current" VMCS to work with.
	 */
	VMPTRLD(vmcs);

	/* Host state */

	/* Initialize host IA32_PAT MSR */
	pat = vmm_get_host_pat();
	if ((error = vmwrite(VMCS_HOST_IA32_PAT, pat)) != 0)
		goto done;

	/* Load the IA32_EFER MSR */
	efer = vmm_get_host_efer();
	if ((error = vmwrite(VMCS_HOST_IA32_EFER, efer)) != 0)
		goto done;

	/* Load the control registers */

	cr0 = vmm_get_host_cr0();
	if ((error = vmwrite(VMCS_HOST_CR0, cr0)) != 0)
		goto done;
	
	cr4 = vmm_get_host_cr4() | CR4_VMXE;
	if ((error = vmwrite(VMCS_HOST_CR4, cr4)) != 0)
		goto done;

	/* Load the segment selectors */
	if ((error = vmwrite(VMCS_HOST_ES_SELECTOR, datasel)) != 0)
		goto done;

	if ((error = vmwrite(VMCS_HOST_CS_SELECTOR, codesel)) != 0)
		goto done;

	if ((error = vmwrite(VMCS_HOST_SS_SELECTOR, datasel)) != 0)
		goto done;

	if ((error = vmwrite(VMCS_HOST_DS_SELECTOR, datasel)) != 0)
		goto done;

	if ((error = vmwrite(VMCS_HOST_FS_SELECTOR, datasel)) != 0)
		goto done;

	if ((error = vmwrite(VMCS_HOST_GS_SELECTOR, datasel)) != 0)
		goto done;

	if ((error = vmwrite(VMCS_HOST_TR_SELECTOR, tsssel)) != 0)
		goto done;

	/*
	 * Load the Base-Address for %fs and idtr.
	 *
	 * Note that we exclude %gs, tss and gdtr here because their base
	 * address is pcpu specific.
	 */
	fsbase = vmm_get_host_fsbase();
	if ((error = vmwrite(VMCS_HOST_FS_BASE, fsbase)) != 0)
		goto done;

	idtrbase = vmm_get_host_idtrbase();
	if ((error = vmwrite(VMCS_HOST_IDTR_BASE, idtrbase)) != 0)
		goto done;

	/* instruction pointer */
	if (no_flush_rsb) {
		if ((error = vmwrite(VMCS_HOST_RIP,
		    (u_long)vmx_exit_guest)) != 0)
			goto done;
	} else {
		if ((error = vmwrite(VMCS_HOST_RIP,
		    (u_long)vmx_exit_guest_flush_rsb)) != 0)
			goto done;
	}

	/* link pointer */
	if ((error = vmwrite(VMCS_LINK_POINTER, ~0)) != 0)
		goto done;
done:
	VMCLEAR(vmcs);
	return (error);
}