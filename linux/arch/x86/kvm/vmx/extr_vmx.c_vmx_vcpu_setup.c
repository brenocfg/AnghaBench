#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_18__ {int output_mask; } ;
struct TYPE_20__ {TYPE_7__ guest; } ;
struct TYPE_17__ {unsigned long long pat; int /*<<< orphan*/  cr0_guest_owned_bits; } ;
struct TYPE_11__ {TYPE_6__ arch; int /*<<< orphan*/  kvm; } ;
struct TYPE_14__ {int /*<<< orphan*/ * val; } ;
struct TYPE_13__ {int /*<<< orphan*/ * val; } ;
struct TYPE_15__ {TYPE_3__ guest; TYPE_2__ host; } ;
struct TYPE_12__ {int /*<<< orphan*/ * msr_bitmap; } ;
struct vcpu_vmx {int hv_deadline_tsc; int ple_window_dirty; int nmsrs; TYPE_9__ pt_desc; int /*<<< orphan*/  pml_pg; TYPE_10__ vcpu; TYPE_5__* guest_msrs; TYPE_4__ msr_autoload; int /*<<< orphan*/  ple_window; int /*<<< orphan*/  pi_desc; int /*<<< orphan*/  secondary_exec_control; TYPE_1__ vmcs01; } ;
struct TYPE_19__ {int vmentry_ctrl; } ;
struct TYPE_16__ {int index; unsigned long long mask; scalar_t__ data; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CR0_GUEST_HOST_MASK ; 
 int /*<<< orphan*/  CR3_TARGET_COUNT ; 
 int /*<<< orphan*/  ENCLS_EXITING_BITMAP ; 
 int /*<<< orphan*/  EOI_EXIT_BITMAP0 ; 
 int /*<<< orphan*/  EOI_EXIT_BITMAP1 ; 
 int /*<<< orphan*/  EOI_EXIT_BITMAP2 ; 
 int /*<<< orphan*/  EOI_EXIT_BITMAP3 ; 
 int /*<<< orphan*/  GUEST_IA32_PAT ; 
 int /*<<< orphan*/  GUEST_IA32_RTIT_CTL ; 
 int /*<<< orphan*/  GUEST_INTR_STATUS ; 
 int /*<<< orphan*/  GUEST_PML_INDEX ; 
 int /*<<< orphan*/  HOST_FS_BASE ; 
 int /*<<< orphan*/  HOST_FS_SELECTOR ; 
 int /*<<< orphan*/  HOST_GS_BASE ; 
 int /*<<< orphan*/  HOST_GS_SELECTOR ; 
 int /*<<< orphan*/  MSR_BITMAP ; 
 int /*<<< orphan*/  PAGE_FAULT_ERROR_CODE_MASK ; 
 int /*<<< orphan*/  PAGE_FAULT_ERROR_CODE_MATCH ; 
 int /*<<< orphan*/  PLE_GAP ; 
 int /*<<< orphan*/  PML_ADDRESS ; 
 scalar_t__ PML_ENTITY_NUM ; 
 int /*<<< orphan*/  POSTED_INTR_DESC_ADDR ; 
 int /*<<< orphan*/  POSTED_INTR_NV ; 
 scalar_t__ POSTED_INTR_VECTOR ; 
 scalar_t__ PT_MODE_HOST_GUEST ; 
 int /*<<< orphan*/  VMCS_LINK_POINTER ; 
 unsigned long long VMX_XSS_EXIT_BITMAP ; 
 int VM_ENTRY_LOAD_IA32_PAT ; 
 int /*<<< orphan*/  VM_ENTRY_MSR_LOAD_ADDR ; 
 int /*<<< orphan*/  VM_ENTRY_MSR_LOAD_COUNT ; 
 int /*<<< orphan*/  VM_EXIT_MSR_LOAD_ADDR ; 
 int /*<<< orphan*/  VM_EXIT_MSR_LOAD_COUNT ; 
 int /*<<< orphan*/  VM_EXIT_MSR_STORE_COUNT ; 
 int /*<<< orphan*/  VM_FUNCTION_CONTROL ; 
 int /*<<< orphan*/  X86_CR0_TS ; 
 int /*<<< orphan*/  XSS_EXIT_BITMAP ; 
 unsigned long long __pa (int /*<<< orphan*/ *) ; 
 scalar_t__ cpu_has_secondary_exec_ctrls () ; 
 scalar_t__ cpu_has_vmx_encls_vmexit () ; 
 scalar_t__ cpu_has_vmx_msr_bitmap () ; 
 scalar_t__ cpu_has_vmx_vmfunc () ; 
 scalar_t__ enable_pml ; 
 int /*<<< orphan*/  exec_controls_set (struct vcpu_vmx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_pause_in_guest (int /*<<< orphan*/ ) ; 
 scalar_t__ kvm_vcpu_apicv_active (TYPE_10__*) ; 
 int /*<<< orphan*/  memset (TYPE_9__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ nested ; 
 int /*<<< orphan*/  nested_vmx_vcpu_setup () ; 
 unsigned long long page_to_phys (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pin_controls_set (struct vcpu_vmx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ple_gap ; 
 int /*<<< orphan*/  ple_window ; 
 scalar_t__ pt_mode ; 
 scalar_t__ rdmsr_safe (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secondary_exec_controls_set (struct vcpu_vmx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_cr4_guest_host_mask (struct vcpu_vmx*) ; 
 int /*<<< orphan*/  vm_entry_controls_set (struct vcpu_vmx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_exit_controls_set (struct vcpu_vmx*,int /*<<< orphan*/ ) ; 
 TYPE_8__ vmcs_config ; 
 int /*<<< orphan*/  vmcs_write16 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  vmcs_write32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmcs_write64 (int /*<<< orphan*/ ,unsigned long long) ; 
 int /*<<< orphan*/  vmcs_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmx_compute_secondary_exec_control (struct vcpu_vmx*) ; 
 int /*<<< orphan*/  vmx_exec_control (struct vcpu_vmx*) ; 
 int /*<<< orphan*/ * vmx_msr_index ; 
 int /*<<< orphan*/  vmx_pin_based_exec_ctrl (struct vcpu_vmx*) ; 
 int /*<<< orphan*/  vmx_set_constant_host_state (struct vcpu_vmx*) ; 
 int /*<<< orphan*/  vmx_vmentry_ctrl () ; 
 int /*<<< orphan*/  vmx_vmexit_ctrl () ; 
 scalar_t__ vmx_xsaves_supported () ; 
 scalar_t__ wrmsr_safe (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vmx_vcpu_setup(struct vcpu_vmx *vmx)
{
	int i;

	if (nested)
		nested_vmx_vcpu_setup();

	if (cpu_has_vmx_msr_bitmap())
		vmcs_write64(MSR_BITMAP, __pa(vmx->vmcs01.msr_bitmap));

	vmcs_write64(VMCS_LINK_POINTER, -1ull); /* 22.3.1.5 */

	/* Control */
	pin_controls_set(vmx, vmx_pin_based_exec_ctrl(vmx));
	vmx->hv_deadline_tsc = -1;

	exec_controls_set(vmx, vmx_exec_control(vmx));

	if (cpu_has_secondary_exec_ctrls()) {
		vmx_compute_secondary_exec_control(vmx);
		secondary_exec_controls_set(vmx, vmx->secondary_exec_control);
	}

	if (kvm_vcpu_apicv_active(&vmx->vcpu)) {
		vmcs_write64(EOI_EXIT_BITMAP0, 0);
		vmcs_write64(EOI_EXIT_BITMAP1, 0);
		vmcs_write64(EOI_EXIT_BITMAP2, 0);
		vmcs_write64(EOI_EXIT_BITMAP3, 0);

		vmcs_write16(GUEST_INTR_STATUS, 0);

		vmcs_write16(POSTED_INTR_NV, POSTED_INTR_VECTOR);
		vmcs_write64(POSTED_INTR_DESC_ADDR, __pa((&vmx->pi_desc)));
	}

	if (!kvm_pause_in_guest(vmx->vcpu.kvm)) {
		vmcs_write32(PLE_GAP, ple_gap);
		vmx->ple_window = ple_window;
		vmx->ple_window_dirty = true;
	}

	vmcs_write32(PAGE_FAULT_ERROR_CODE_MASK, 0);
	vmcs_write32(PAGE_FAULT_ERROR_CODE_MATCH, 0);
	vmcs_write32(CR3_TARGET_COUNT, 0);           /* 22.2.1 */

	vmcs_write16(HOST_FS_SELECTOR, 0);            /* 22.2.4 */
	vmcs_write16(HOST_GS_SELECTOR, 0);            /* 22.2.4 */
	vmx_set_constant_host_state(vmx);
	vmcs_writel(HOST_FS_BASE, 0); /* 22.2.4 */
	vmcs_writel(HOST_GS_BASE, 0); /* 22.2.4 */

	if (cpu_has_vmx_vmfunc())
		vmcs_write64(VM_FUNCTION_CONTROL, 0);

	vmcs_write32(VM_EXIT_MSR_STORE_COUNT, 0);
	vmcs_write32(VM_EXIT_MSR_LOAD_COUNT, 0);
	vmcs_write64(VM_EXIT_MSR_LOAD_ADDR, __pa(vmx->msr_autoload.host.val));
	vmcs_write32(VM_ENTRY_MSR_LOAD_COUNT, 0);
	vmcs_write64(VM_ENTRY_MSR_LOAD_ADDR, __pa(vmx->msr_autoload.guest.val));

	if (vmcs_config.vmentry_ctrl & VM_ENTRY_LOAD_IA32_PAT)
		vmcs_write64(GUEST_IA32_PAT, vmx->vcpu.arch.pat);

	for (i = 0; i < ARRAY_SIZE(vmx_msr_index); ++i) {
		u32 index = vmx_msr_index[i];
		u32 data_low, data_high;
		int j = vmx->nmsrs;

		if (rdmsr_safe(index, &data_low, &data_high) < 0)
			continue;
		if (wrmsr_safe(index, data_low, data_high) < 0)
			continue;
		vmx->guest_msrs[j].index = i;
		vmx->guest_msrs[j].data = 0;
		vmx->guest_msrs[j].mask = -1ull;
		++vmx->nmsrs;
	}

	vm_exit_controls_set(vmx, vmx_vmexit_ctrl());

	/* 22.2.1, 20.8.1 */
	vm_entry_controls_set(vmx, vmx_vmentry_ctrl());

	vmx->vcpu.arch.cr0_guest_owned_bits = X86_CR0_TS;
	vmcs_writel(CR0_GUEST_HOST_MASK, ~X86_CR0_TS);

	set_cr4_guest_host_mask(vmx);

	if (vmx_xsaves_supported())
		vmcs_write64(XSS_EXIT_BITMAP, VMX_XSS_EXIT_BITMAP);

	if (enable_pml) {
		vmcs_write64(PML_ADDRESS, page_to_phys(vmx->pml_pg));
		vmcs_write16(GUEST_PML_INDEX, PML_ENTITY_NUM - 1);
	}

	if (cpu_has_vmx_encls_vmexit())
		vmcs_write64(ENCLS_EXITING_BITMAP, -1ull);

	if (pt_mode == PT_MODE_HOST_GUEST) {
		memset(&vmx->pt_desc, 0, sizeof(vmx->pt_desc));
		/* Bit[6~0] are forced to 1, writes are ignored. */
		vmx->pt_desc.guest.output_mask = 0x7F;
		vmcs_write64(GUEST_IA32_RTIT_CTL, 0);
	}
}