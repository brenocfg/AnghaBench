#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct vcpu_vmx {TYPE_2__* loaded_vmcs; } ;
struct TYPE_6__ {int vmexit_ctrl; } ;
struct TYPE_4__ {unsigned long cr3; unsigned long cr4; } ;
struct TYPE_5__ {TYPE_1__ host_state; } ;

/* Variables and functions */
 int GDT_ENTRY_TSS ; 
 int /*<<< orphan*/  HOST_CR0 ; 
 int /*<<< orphan*/  HOST_CR3 ; 
 int /*<<< orphan*/  HOST_CR4 ; 
 int /*<<< orphan*/  HOST_CS_SELECTOR ; 
 int /*<<< orphan*/  HOST_DS_SELECTOR ; 
 int /*<<< orphan*/  HOST_ES_SELECTOR ; 
 int /*<<< orphan*/  HOST_IA32_EFER ; 
 int /*<<< orphan*/  HOST_IA32_PAT ; 
 int /*<<< orphan*/  HOST_IA32_SYSENTER_CS ; 
 int /*<<< orphan*/  HOST_IA32_SYSENTER_EIP ; 
 int /*<<< orphan*/  HOST_IDTR_BASE ; 
 int /*<<< orphan*/  HOST_RIP ; 
 int /*<<< orphan*/  HOST_SS_SELECTOR ; 
 int /*<<< orphan*/  HOST_TR_SELECTOR ; 
 int /*<<< orphan*/  MSR_IA32_CR_PAT ; 
 int /*<<< orphan*/  MSR_IA32_SYSENTER_CS ; 
 int /*<<< orphan*/  MSR_IA32_SYSENTER_EIP ; 
 int VM_EXIT_LOAD_IA32_PAT ; 
 int /*<<< orphan*/  WARN_ON (unsigned long) ; 
 unsigned long X86_CR0_TS ; 
 int __KERNEL_CS ; 
 int __KERNEL_DS ; 
 unsigned long __read_cr3 () ; 
 scalar_t__ cpu_has_load_ia32_efer () ; 
 unsigned long cr4_read_shadow () ; 
 int host_efer ; 
 unsigned long host_idt_base ; 
 int /*<<< orphan*/  rdmsr (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rdmsrl (int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long read_cr0 () ; 
 TYPE_3__ vmcs_config ; 
 int /*<<< orphan*/  vmcs_write16 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vmcs_write32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vmcs_write64 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vmcs_writel (int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ vmx_vmexit ; 

void vmx_set_constant_host_state(struct vcpu_vmx *vmx)
{
	u32 low32, high32;
	unsigned long tmpl;
	unsigned long cr0, cr3, cr4;

	cr0 = read_cr0();
	WARN_ON(cr0 & X86_CR0_TS);
	vmcs_writel(HOST_CR0, cr0);  /* 22.2.3 */

	/*
	 * Save the most likely value for this task's CR3 in the VMCS.
	 * We can't use __get_current_cr3_fast() because we're not atomic.
	 */
	cr3 = __read_cr3();
	vmcs_writel(HOST_CR3, cr3);		/* 22.2.3  FIXME: shadow tables */
	vmx->loaded_vmcs->host_state.cr3 = cr3;

	/* Save the most likely value for this task's CR4 in the VMCS. */
	cr4 = cr4_read_shadow();
	vmcs_writel(HOST_CR4, cr4);			/* 22.2.3, 22.2.5 */
	vmx->loaded_vmcs->host_state.cr4 = cr4;

	vmcs_write16(HOST_CS_SELECTOR, __KERNEL_CS);  /* 22.2.4 */
#ifdef CONFIG_X86_64
	/*
	 * Load null selectors, so we can avoid reloading them in
	 * vmx_prepare_switch_to_host(), in case userspace uses
	 * the null selectors too (the expected case).
	 */
	vmcs_write16(HOST_DS_SELECTOR, 0);
	vmcs_write16(HOST_ES_SELECTOR, 0);
#else
	vmcs_write16(HOST_DS_SELECTOR, __KERNEL_DS);  /* 22.2.4 */
	vmcs_write16(HOST_ES_SELECTOR, __KERNEL_DS);  /* 22.2.4 */
#endif
	vmcs_write16(HOST_SS_SELECTOR, __KERNEL_DS);  /* 22.2.4 */
	vmcs_write16(HOST_TR_SELECTOR, GDT_ENTRY_TSS*8);  /* 22.2.4 */

	vmcs_writel(HOST_IDTR_BASE, host_idt_base);   /* 22.2.4 */

	vmcs_writel(HOST_RIP, (unsigned long)vmx_vmexit); /* 22.2.5 */

	rdmsr(MSR_IA32_SYSENTER_CS, low32, high32);
	vmcs_write32(HOST_IA32_SYSENTER_CS, low32);
	rdmsrl(MSR_IA32_SYSENTER_EIP, tmpl);
	vmcs_writel(HOST_IA32_SYSENTER_EIP, tmpl);   /* 22.2.3 */

	if (vmcs_config.vmexit_ctrl & VM_EXIT_LOAD_IA32_PAT) {
		rdmsr(MSR_IA32_CR_PAT, low32, high32);
		vmcs_write64(HOST_IA32_PAT, low32 | ((u64) high32 << 32));
	}

	if (cpu_has_load_ia32_efer())
		vmcs_write64(HOST_IA32_EFER, host_efer);
}