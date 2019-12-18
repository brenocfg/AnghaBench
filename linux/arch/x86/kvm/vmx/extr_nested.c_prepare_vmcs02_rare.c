#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vmcs12 {int vm_entry_controls; int /*<<< orphan*/  eoi_exit_bitmap3; int /*<<< orphan*/  eoi_exit_bitmap2; int /*<<< orphan*/  eoi_exit_bitmap1; int /*<<< orphan*/  eoi_exit_bitmap0; int /*<<< orphan*/  page_fault_error_code_match; int /*<<< orphan*/  page_fault_error_code_mask; int /*<<< orphan*/  xss_exit_bitmap; int /*<<< orphan*/  guest_bndcfgs; int /*<<< orphan*/  guest_pdptr3; int /*<<< orphan*/  guest_pdptr2; int /*<<< orphan*/  guest_pdptr1; int /*<<< orphan*/  guest_pdptr0; int /*<<< orphan*/  guest_sysenter_eip; int /*<<< orphan*/  guest_sysenter_esp; int /*<<< orphan*/  guest_pending_dbg_exceptions; int /*<<< orphan*/  guest_sysenter_cs; int /*<<< orphan*/  guest_idtr_base; int /*<<< orphan*/  guest_gdtr_base; int /*<<< orphan*/  guest_tr_base; int /*<<< orphan*/  guest_ldtr_base; int /*<<< orphan*/  guest_gs_base; int /*<<< orphan*/  guest_fs_base; int /*<<< orphan*/  guest_ds_base; int /*<<< orphan*/  guest_ss_base; int /*<<< orphan*/  guest_cs_base; int /*<<< orphan*/  guest_es_base; int /*<<< orphan*/  guest_tr_ar_bytes; int /*<<< orphan*/  guest_ldtr_ar_bytes; int /*<<< orphan*/  guest_gs_ar_bytes; int /*<<< orphan*/  guest_fs_ar_bytes; int /*<<< orphan*/  guest_ds_ar_bytes; int /*<<< orphan*/  guest_es_ar_bytes; int /*<<< orphan*/  guest_ss_ar_bytes; int /*<<< orphan*/  guest_cs_ar_bytes; int /*<<< orphan*/  guest_idtr_limit; int /*<<< orphan*/  guest_gdtr_limit; int /*<<< orphan*/  guest_tr_limit; int /*<<< orphan*/  guest_ldtr_limit; int /*<<< orphan*/  guest_gs_limit; int /*<<< orphan*/  guest_fs_limit; int /*<<< orphan*/  guest_ds_limit; int /*<<< orphan*/  guest_ss_limit; int /*<<< orphan*/  guest_cs_limit; int /*<<< orphan*/  guest_es_limit; int /*<<< orphan*/  guest_tr_selector; int /*<<< orphan*/  guest_ldtr_selector; int /*<<< orphan*/  guest_gs_selector; int /*<<< orphan*/  guest_fs_selector; int /*<<< orphan*/  guest_ds_selector; int /*<<< orphan*/  guest_ss_selector; int /*<<< orphan*/  guest_cs_selector; int /*<<< orphan*/  guest_es_selector; } ;
struct TYPE_7__ {int /*<<< orphan*/  nr; } ;
struct TYPE_6__ {int /*<<< orphan*/  nr; } ;
struct TYPE_8__ {TYPE_3__ guest; TYPE_2__ host; } ;
struct TYPE_5__ {scalar_t__ nested_run_pending; struct hv_enlightened_vmcs* hv_evmcs; } ;
struct vcpu_vmx {TYPE_4__ msr_autoload; TYPE_1__ nested; } ;
struct hv_enlightened_vmcs {int hv_clean_fields; } ;

/* Variables and functions */
 int /*<<< orphan*/  EOI_EXIT_BITMAP0 ; 
 int /*<<< orphan*/  EOI_EXIT_BITMAP1 ; 
 int /*<<< orphan*/  EOI_EXIT_BITMAP2 ; 
 int /*<<< orphan*/  EOI_EXIT_BITMAP3 ; 
 int /*<<< orphan*/  GUEST_BNDCFGS ; 
 int /*<<< orphan*/  GUEST_CS_AR_BYTES ; 
 int /*<<< orphan*/  GUEST_CS_BASE ; 
 int /*<<< orphan*/  GUEST_CS_LIMIT ; 
 int /*<<< orphan*/  GUEST_CS_SELECTOR ; 
 int /*<<< orphan*/  GUEST_DS_AR_BYTES ; 
 int /*<<< orphan*/  GUEST_DS_BASE ; 
 int /*<<< orphan*/  GUEST_DS_LIMIT ; 
 int /*<<< orphan*/  GUEST_DS_SELECTOR ; 
 int /*<<< orphan*/  GUEST_ES_AR_BYTES ; 
 int /*<<< orphan*/  GUEST_ES_BASE ; 
 int /*<<< orphan*/  GUEST_ES_LIMIT ; 
 int /*<<< orphan*/  GUEST_ES_SELECTOR ; 
 int /*<<< orphan*/  GUEST_FS_AR_BYTES ; 
 int /*<<< orphan*/  GUEST_FS_BASE ; 
 int /*<<< orphan*/  GUEST_FS_LIMIT ; 
 int /*<<< orphan*/  GUEST_FS_SELECTOR ; 
 int /*<<< orphan*/  GUEST_GDTR_BASE ; 
 int /*<<< orphan*/  GUEST_GDTR_LIMIT ; 
 int /*<<< orphan*/  GUEST_GS_AR_BYTES ; 
 int /*<<< orphan*/  GUEST_GS_BASE ; 
 int /*<<< orphan*/  GUEST_GS_LIMIT ; 
 int /*<<< orphan*/  GUEST_GS_SELECTOR ; 
 int /*<<< orphan*/  GUEST_IDTR_BASE ; 
 int /*<<< orphan*/  GUEST_IDTR_LIMIT ; 
 int /*<<< orphan*/  GUEST_LDTR_AR_BYTES ; 
 int /*<<< orphan*/  GUEST_LDTR_BASE ; 
 int /*<<< orphan*/  GUEST_LDTR_LIMIT ; 
 int /*<<< orphan*/  GUEST_LDTR_SELECTOR ; 
 int /*<<< orphan*/  GUEST_PDPTR0 ; 
 int /*<<< orphan*/  GUEST_PDPTR1 ; 
 int /*<<< orphan*/  GUEST_PDPTR2 ; 
 int /*<<< orphan*/  GUEST_PDPTR3 ; 
 int /*<<< orphan*/  GUEST_PENDING_DBG_EXCEPTIONS ; 
 int /*<<< orphan*/  GUEST_SS_AR_BYTES ; 
 int /*<<< orphan*/  GUEST_SS_BASE ; 
 int /*<<< orphan*/  GUEST_SS_LIMIT ; 
 int /*<<< orphan*/  GUEST_SS_SELECTOR ; 
 int /*<<< orphan*/  GUEST_SYSENTER_CS ; 
 int /*<<< orphan*/  GUEST_SYSENTER_EIP ; 
 int /*<<< orphan*/  GUEST_SYSENTER_ESP ; 
 int /*<<< orphan*/  GUEST_TR_AR_BYTES ; 
 int /*<<< orphan*/  GUEST_TR_BASE ; 
 int /*<<< orphan*/  GUEST_TR_LIMIT ; 
 int /*<<< orphan*/  GUEST_TR_SELECTOR ; 
 int HV_VMX_ENLIGHTENED_CLEAN_FIELD_GUEST_GRP1 ; 
 int HV_VMX_ENLIGHTENED_CLEAN_FIELD_GUEST_GRP2 ; 
 int /*<<< orphan*/  PAGE_FAULT_ERROR_CODE_MASK ; 
 int /*<<< orphan*/  PAGE_FAULT_ERROR_CODE_MATCH ; 
 int VM_ENTRY_LOAD_BNDCFGS ; 
 int /*<<< orphan*/  VM_ENTRY_MSR_LOAD_COUNT ; 
 int /*<<< orphan*/  VM_EXIT_MSR_LOAD_COUNT ; 
 int /*<<< orphan*/  XSS_EXIT_BITMAP ; 
 scalar_t__ cpu_has_vmx_apicv () ; 
 scalar_t__ enable_ept ; 
 scalar_t__ kvm_mpx_supported () ; 
 scalar_t__ nested_cpu_has_xsaves (struct vmcs12*) ; 
 int /*<<< orphan*/  set_cr4_guest_host_mask (struct vcpu_vmx*) ; 
 int /*<<< orphan*/  vmcs_write16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmcs_write32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmcs_write64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmcs_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void prepare_vmcs02_rare(struct vcpu_vmx *vmx, struct vmcs12 *vmcs12)
{
	struct hv_enlightened_vmcs *hv_evmcs = vmx->nested.hv_evmcs;

	if (!hv_evmcs || !(hv_evmcs->hv_clean_fields &
			   HV_VMX_ENLIGHTENED_CLEAN_FIELD_GUEST_GRP2)) {
		vmcs_write16(GUEST_ES_SELECTOR, vmcs12->guest_es_selector);
		vmcs_write16(GUEST_CS_SELECTOR, vmcs12->guest_cs_selector);
		vmcs_write16(GUEST_SS_SELECTOR, vmcs12->guest_ss_selector);
		vmcs_write16(GUEST_DS_SELECTOR, vmcs12->guest_ds_selector);
		vmcs_write16(GUEST_FS_SELECTOR, vmcs12->guest_fs_selector);
		vmcs_write16(GUEST_GS_SELECTOR, vmcs12->guest_gs_selector);
		vmcs_write16(GUEST_LDTR_SELECTOR, vmcs12->guest_ldtr_selector);
		vmcs_write16(GUEST_TR_SELECTOR, vmcs12->guest_tr_selector);
		vmcs_write32(GUEST_ES_LIMIT, vmcs12->guest_es_limit);
		vmcs_write32(GUEST_CS_LIMIT, vmcs12->guest_cs_limit);
		vmcs_write32(GUEST_SS_LIMIT, vmcs12->guest_ss_limit);
		vmcs_write32(GUEST_DS_LIMIT, vmcs12->guest_ds_limit);
		vmcs_write32(GUEST_FS_LIMIT, vmcs12->guest_fs_limit);
		vmcs_write32(GUEST_GS_LIMIT, vmcs12->guest_gs_limit);
		vmcs_write32(GUEST_LDTR_LIMIT, vmcs12->guest_ldtr_limit);
		vmcs_write32(GUEST_TR_LIMIT, vmcs12->guest_tr_limit);
		vmcs_write32(GUEST_GDTR_LIMIT, vmcs12->guest_gdtr_limit);
		vmcs_write32(GUEST_IDTR_LIMIT, vmcs12->guest_idtr_limit);
		vmcs_write32(GUEST_CS_AR_BYTES, vmcs12->guest_cs_ar_bytes);
		vmcs_write32(GUEST_SS_AR_BYTES, vmcs12->guest_ss_ar_bytes);
		vmcs_write32(GUEST_ES_AR_BYTES, vmcs12->guest_es_ar_bytes);
		vmcs_write32(GUEST_DS_AR_BYTES, vmcs12->guest_ds_ar_bytes);
		vmcs_write32(GUEST_FS_AR_BYTES, vmcs12->guest_fs_ar_bytes);
		vmcs_write32(GUEST_GS_AR_BYTES, vmcs12->guest_gs_ar_bytes);
		vmcs_write32(GUEST_LDTR_AR_BYTES, vmcs12->guest_ldtr_ar_bytes);
		vmcs_write32(GUEST_TR_AR_BYTES, vmcs12->guest_tr_ar_bytes);
		vmcs_writel(GUEST_ES_BASE, vmcs12->guest_es_base);
		vmcs_writel(GUEST_CS_BASE, vmcs12->guest_cs_base);
		vmcs_writel(GUEST_SS_BASE, vmcs12->guest_ss_base);
		vmcs_writel(GUEST_DS_BASE, vmcs12->guest_ds_base);
		vmcs_writel(GUEST_FS_BASE, vmcs12->guest_fs_base);
		vmcs_writel(GUEST_GS_BASE, vmcs12->guest_gs_base);
		vmcs_writel(GUEST_LDTR_BASE, vmcs12->guest_ldtr_base);
		vmcs_writel(GUEST_TR_BASE, vmcs12->guest_tr_base);
		vmcs_writel(GUEST_GDTR_BASE, vmcs12->guest_gdtr_base);
		vmcs_writel(GUEST_IDTR_BASE, vmcs12->guest_idtr_base);
	}

	if (!hv_evmcs || !(hv_evmcs->hv_clean_fields &
			   HV_VMX_ENLIGHTENED_CLEAN_FIELD_GUEST_GRP1)) {
		vmcs_write32(GUEST_SYSENTER_CS, vmcs12->guest_sysenter_cs);
		vmcs_writel(GUEST_PENDING_DBG_EXCEPTIONS,
			    vmcs12->guest_pending_dbg_exceptions);
		vmcs_writel(GUEST_SYSENTER_ESP, vmcs12->guest_sysenter_esp);
		vmcs_writel(GUEST_SYSENTER_EIP, vmcs12->guest_sysenter_eip);

		/*
		 * L1 may access the L2's PDPTR, so save them to construct
		 * vmcs12
		 */
		if (enable_ept) {
			vmcs_write64(GUEST_PDPTR0, vmcs12->guest_pdptr0);
			vmcs_write64(GUEST_PDPTR1, vmcs12->guest_pdptr1);
			vmcs_write64(GUEST_PDPTR2, vmcs12->guest_pdptr2);
			vmcs_write64(GUEST_PDPTR3, vmcs12->guest_pdptr3);
		}

		if (kvm_mpx_supported() && vmx->nested.nested_run_pending &&
		    (vmcs12->vm_entry_controls & VM_ENTRY_LOAD_BNDCFGS))
			vmcs_write64(GUEST_BNDCFGS, vmcs12->guest_bndcfgs);
	}

	if (nested_cpu_has_xsaves(vmcs12))
		vmcs_write64(XSS_EXIT_BITMAP, vmcs12->xss_exit_bitmap);

	/*
	 * Whether page-faults are trapped is determined by a combination of
	 * 3 settings: PFEC_MASK, PFEC_MATCH and EXCEPTION_BITMAP.PF.
	 * If enable_ept, L0 doesn't care about page faults and we should
	 * set all of these to L1's desires. However, if !enable_ept, L0 does
	 * care about (at least some) page faults, and because it is not easy
	 * (if at all possible?) to merge L0 and L1's desires, we simply ask
	 * to exit on each and every L2 page fault. This is done by setting
	 * MASK=MATCH=0 and (see below) EB.PF=1.
	 * Note that below we don't need special code to set EB.PF beyond the
	 * "or"ing of the EB of vmcs01 and vmcs12, because when enable_ept,
	 * vmcs01's EB.PF is 0 so the "or" will take vmcs12's value, and when
	 * !enable_ept, EB.PF is 1, so the "or" will always be 1.
	 */
	vmcs_write32(PAGE_FAULT_ERROR_CODE_MASK,
		enable_ept ? vmcs12->page_fault_error_code_mask : 0);
	vmcs_write32(PAGE_FAULT_ERROR_CODE_MATCH,
		enable_ept ? vmcs12->page_fault_error_code_match : 0);

	if (cpu_has_vmx_apicv()) {
		vmcs_write64(EOI_EXIT_BITMAP0, vmcs12->eoi_exit_bitmap0);
		vmcs_write64(EOI_EXIT_BITMAP1, vmcs12->eoi_exit_bitmap1);
		vmcs_write64(EOI_EXIT_BITMAP2, vmcs12->eoi_exit_bitmap2);
		vmcs_write64(EOI_EXIT_BITMAP3, vmcs12->eoi_exit_bitmap3);
	}

	vmcs_write32(VM_EXIT_MSR_LOAD_COUNT, vmx->msr_autoload.host.nr);
	vmcs_write32(VM_ENTRY_MSR_LOAD_COUNT, vmx->msr_autoload.guest.nr);

	set_cr4_guest_host_mask(vmx);
}