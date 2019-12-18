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
typedef  int uint32_t ;
struct vmctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VMCS_CR0_MASK ; 
 int /*<<< orphan*/  VMCS_CR0_SHADOW ; 
 int /*<<< orphan*/  VMCS_CR3_TARGET0 ; 
 int /*<<< orphan*/  VMCS_CR3_TARGET1 ; 
 int /*<<< orphan*/  VMCS_CR3_TARGET2 ; 
 int /*<<< orphan*/  VMCS_CR3_TARGET3 ; 
 int /*<<< orphan*/  VMCS_CR3_TARGET_COUNT ; 
 int /*<<< orphan*/  VMCS_CR4_MASK ; 
 int /*<<< orphan*/  VMCS_CR4_SHADOW ; 
 int /*<<< orphan*/  VMCS_ENTRY_CTLS ; 
 int /*<<< orphan*/  VMCS_ENTRY_INTR_INFO ; 
 int /*<<< orphan*/  VMCS_EXIT_CTLS ; 
 int /*<<< orphan*/  VMCS_EXIT_INSTRUCTION_LENGTH ; 
 int /*<<< orphan*/  VMCS_EXIT_INTR_ERRCODE ; 
 int /*<<< orphan*/  VMCS_EXIT_INTR_INFO ; 
 int /*<<< orphan*/  VMCS_EXIT_QUALIFICATION ; 
 int /*<<< orphan*/  VMCS_GUEST_INTERRUPTIBILITY ; 
 int /*<<< orphan*/  VMCS_GUEST_LINEAR_ADDRESS ; 
 int /*<<< orphan*/  VMCS_GUEST_PHYSICAL_ADDRESS ; 
 int /*<<< orphan*/  VMCS_HOST_CR0 ; 
 int /*<<< orphan*/  VMCS_HOST_CR3 ; 
 int /*<<< orphan*/  VMCS_HOST_CR4 ; 
 int /*<<< orphan*/  VMCS_HOST_IA32_PAT ; 
 int /*<<< orphan*/  VMCS_HOST_RIP ; 
 int /*<<< orphan*/  VMCS_HOST_RSP ; 
 int /*<<< orphan*/  VMCS_INSTRUCTION_ERROR ; 
 int /*<<< orphan*/  VMCS_LINK_POINTER ; 
 int /*<<< orphan*/  VMCS_PIN_BASED_CTLS ; 
 int /*<<< orphan*/  VMCS_PRI_PROC_BASED_CTLS ; 
 int /*<<< orphan*/  VMCS_SEC_PROC_BASED_CTLS ; 
 int /*<<< orphan*/  VMCS_TPR_THRESHOLD ; 
 scalar_t__ get_all ; 
 scalar_t__ get_cr0_mask ; 
 scalar_t__ get_cr0_shadow ; 
 scalar_t__ get_cr3_targets ; 
 scalar_t__ get_cr4_mask ; 
 scalar_t__ get_cr4_shadow ; 
 scalar_t__ get_entry_ctls ; 
 scalar_t__ get_exit_ctls ; 
 scalar_t__ get_host_cr0 ; 
 scalar_t__ get_host_cr3 ; 
 scalar_t__ get_host_cr4 ; 
 scalar_t__ get_host_pat ; 
 scalar_t__ get_host_rip ; 
 scalar_t__ get_host_rsp ; 
 scalar_t__ get_inst_err ; 
 scalar_t__ get_pinbased_ctls ; 
 scalar_t__ get_procbased_ctls ; 
 scalar_t__ get_procbased_ctls2 ; 
 scalar_t__ get_tpr_threshold ; 
 scalar_t__ get_vmcs_entry_interruption_info ; 
 scalar_t__ get_vmcs_exit_inst_length ; 
 scalar_t__ get_vmcs_exit_interruption_error ; 
 scalar_t__ get_vmcs_exit_interruption_info ; 
 scalar_t__ get_vmcs_exit_qualification ; 
 scalar_t__ get_vmcs_gla ; 
 scalar_t__ get_vmcs_gpa ; 
 scalar_t__ get_vmcs_interruptibility ; 
 scalar_t__ get_vmcs_link ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 int vm_get_vmcs_field (struct vmctx*,int,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int
get_misc_vmcs(struct vmctx *ctx, int vcpu)
{
	uint64_t ctl, cr0, cr3, cr4, rsp, rip, pat, addr, u64;
	int error = 0;

	if (!error && (get_cr0_mask || get_all)) {
		uint64_t cr0mask;
		error = vm_get_vmcs_field(ctx, vcpu, VMCS_CR0_MASK, &cr0mask);
		if (error == 0)
			printf("cr0_mask[%d]\t\t0x%016lx\n", vcpu, cr0mask);
	}

	if (!error && (get_cr0_shadow || get_all)) {
		uint64_t cr0shadow;
		error = vm_get_vmcs_field(ctx, vcpu, VMCS_CR0_SHADOW,
					  &cr0shadow);
		if (error == 0)
			printf("cr0_shadow[%d]\t\t0x%016lx\n", vcpu, cr0shadow);
	}

	if (!error && (get_cr4_mask || get_all)) {
		uint64_t cr4mask;
		error = vm_get_vmcs_field(ctx, vcpu, VMCS_CR4_MASK, &cr4mask);
		if (error == 0)
			printf("cr4_mask[%d]\t\t0x%016lx\n", vcpu, cr4mask);
	}

	if (!error && (get_cr4_shadow || get_all)) {
		uint64_t cr4shadow;
		error = vm_get_vmcs_field(ctx, vcpu, VMCS_CR4_SHADOW,
					  &cr4shadow);
		if (error == 0)
			printf("cr4_shadow[%d]\t\t0x%016lx\n", vcpu, cr4shadow);
	}
	
	if (!error && (get_cr3_targets || get_all)) {
		uint64_t target_count, target_addr;
		error = vm_get_vmcs_field(ctx, vcpu, VMCS_CR3_TARGET_COUNT,
					  &target_count);
		if (error == 0) {
			printf("cr3_target_count[%d]\t0x%016lx\n",
				vcpu, target_count);
		}

		error = vm_get_vmcs_field(ctx, vcpu, VMCS_CR3_TARGET0,
					  &target_addr);
		if (error == 0) {
			printf("cr3_target0[%d]\t\t0x%016lx\n",
				vcpu, target_addr);
		}

		error = vm_get_vmcs_field(ctx, vcpu, VMCS_CR3_TARGET1,
					  &target_addr);
		if (error == 0) {
			printf("cr3_target1[%d]\t\t0x%016lx\n",
				vcpu, target_addr);
		}

		error = vm_get_vmcs_field(ctx, vcpu, VMCS_CR3_TARGET2,
					  &target_addr);
		if (error == 0) {
			printf("cr3_target2[%d]\t\t0x%016lx\n",
				vcpu, target_addr);
		}

		error = vm_get_vmcs_field(ctx, vcpu, VMCS_CR3_TARGET3,
					  &target_addr);
		if (error == 0) {
			printf("cr3_target3[%d]\t\t0x%016lx\n",
				vcpu, target_addr);
		}
	}

	if (!error && (get_pinbased_ctls || get_all)) {
		error = vm_get_vmcs_field(ctx, vcpu, VMCS_PIN_BASED_CTLS, &ctl);
		if (error == 0)
			printf("pinbased_ctls[%d]\t0x%016lx\n", vcpu, ctl);
	}

	if (!error && (get_procbased_ctls || get_all)) {
		error = vm_get_vmcs_field(ctx, vcpu,
					  VMCS_PRI_PROC_BASED_CTLS, &ctl);
		if (error == 0)
			printf("procbased_ctls[%d]\t0x%016lx\n", vcpu, ctl);
	}

	if (!error && (get_procbased_ctls2 || get_all)) {
		error = vm_get_vmcs_field(ctx, vcpu,
					  VMCS_SEC_PROC_BASED_CTLS, &ctl);
		if (error == 0)
			printf("procbased_ctls2[%d]\t0x%016lx\n", vcpu, ctl);
	}

	if (!error && (get_vmcs_gla || get_all)) {
		error = vm_get_vmcs_field(ctx, vcpu,
					  VMCS_GUEST_LINEAR_ADDRESS, &u64);
		if (error == 0)
			printf("gla[%d]\t\t0x%016lx\n", vcpu, u64);
	}

	if (!error && (get_vmcs_gpa || get_all)) {
		error = vm_get_vmcs_field(ctx, vcpu,
					  VMCS_GUEST_PHYSICAL_ADDRESS, &u64);
		if (error == 0)
			printf("gpa[%d]\t\t0x%016lx\n", vcpu, u64);
	}

	if (!error && (get_vmcs_entry_interruption_info || 
		get_all)) {
		error = vm_get_vmcs_field(ctx, vcpu, VMCS_ENTRY_INTR_INFO,&u64);
		if (error == 0) {
			printf("entry_interruption_info[%d]\t0x%016lx\n",
				vcpu, u64);
		}
	}

	if (!error && (get_tpr_threshold || get_all)) {
		uint64_t threshold;
		error = vm_get_vmcs_field(ctx, vcpu, VMCS_TPR_THRESHOLD,
					  &threshold);
		if (error == 0)
			printf("tpr_threshold[%d]\t0x%016lx\n", vcpu, threshold);
	}

	if (!error && (get_inst_err || get_all)) {
		uint64_t insterr;
		error = vm_get_vmcs_field(ctx, vcpu, VMCS_INSTRUCTION_ERROR,
					  &insterr);
		if (error == 0) {
			printf("instruction_error[%d]\t0x%016lx\n",
				vcpu, insterr);
		}
	}

	if (!error && (get_exit_ctls || get_all)) {
		error = vm_get_vmcs_field(ctx, vcpu, VMCS_EXIT_CTLS, &ctl);
		if (error == 0)
			printf("exit_ctls[%d]\t\t0x%016lx\n", vcpu, ctl);
	}

	if (!error && (get_entry_ctls || get_all)) {
		error = vm_get_vmcs_field(ctx, vcpu, VMCS_ENTRY_CTLS, &ctl);
		if (error == 0)
			printf("entry_ctls[%d]\t\t0x%016lx\n", vcpu, ctl);
	}

	if (!error && (get_host_pat || get_all)) {
		error = vm_get_vmcs_field(ctx, vcpu, VMCS_HOST_IA32_PAT, &pat);
		if (error == 0)
			printf("host_pat[%d]\t\t0x%016lx\n", vcpu, pat);
	}

	if (!error && (get_host_cr0 || get_all)) {
		error = vm_get_vmcs_field(ctx, vcpu, VMCS_HOST_CR0, &cr0);
		if (error == 0)
			printf("host_cr0[%d]\t\t0x%016lx\n", vcpu, cr0);
	}

	if (!error && (get_host_cr3 || get_all)) {
		error = vm_get_vmcs_field(ctx, vcpu, VMCS_HOST_CR3, &cr3);
		if (error == 0)
			printf("host_cr3[%d]\t\t0x%016lx\n", vcpu, cr3);
	}

	if (!error && (get_host_cr4 || get_all)) {
		error = vm_get_vmcs_field(ctx, vcpu, VMCS_HOST_CR4, &cr4);
		if (error == 0)
			printf("host_cr4[%d]\t\t0x%016lx\n", vcpu, cr4);
	}

	if (!error && (get_host_rip || get_all)) {
		error = vm_get_vmcs_field(ctx, vcpu, VMCS_HOST_RIP, &rip);
		if (error == 0)
			printf("host_rip[%d]\t\t0x%016lx\n", vcpu, rip);
	}

	if (!error && (get_host_rsp || get_all)) {
		error = vm_get_vmcs_field(ctx, vcpu, VMCS_HOST_RSP, &rsp);
		if (error == 0)
			printf("host_rsp[%d]\t\t0x%016lx\n", vcpu, rsp);
	}

	if (!error && (get_vmcs_link || get_all)) {
		error = vm_get_vmcs_field(ctx, vcpu, VMCS_LINK_POINTER, &addr);
		if (error == 0)
			printf("vmcs_pointer[%d]\t0x%016lx\n", vcpu, addr);
	}

	if (!error && (get_vmcs_exit_interruption_info || get_all)) {
		error = vm_get_vmcs_field(ctx, vcpu, VMCS_EXIT_INTR_INFO, &u64);
		if (error == 0) {
			printf("vmcs_exit_interruption_info[%d]\t0x%016lx\n",
				vcpu, u64);
		}
	}

	if (!error && (get_vmcs_exit_interruption_error || get_all)) {
		error = vm_get_vmcs_field(ctx, vcpu, VMCS_EXIT_INTR_ERRCODE,
		    			  &u64);
		if (error == 0) {
			printf("vmcs_exit_interruption_error[%d]\t0x%016lx\n",
				vcpu, u64);
		}
	}

	if (!error && (get_vmcs_interruptibility || get_all)) {
		error = vm_get_vmcs_field(ctx, vcpu,
					  VMCS_GUEST_INTERRUPTIBILITY, &u64);
		if (error == 0) {
			printf("vmcs_guest_interruptibility[%d]\t0x%016lx\n",
				vcpu, u64);
		}
	}

	if (!error && (get_vmcs_exit_inst_length || get_all)) {
		error = vm_get_vmcs_field(ctx, vcpu,
		    VMCS_EXIT_INSTRUCTION_LENGTH, &u64);
		if (error == 0)
			printf("vmcs_exit_inst_length[%d]\t0x%08x\n", vcpu,
			    (uint32_t)u64);
	}

	if (!error && (get_vmcs_exit_qualification || get_all)) {
		error = vm_get_vmcs_field(ctx, vcpu, VMCS_EXIT_QUALIFICATION,
					  &u64);
		if (error == 0)
			printf("vmcs_exit_qualification[%d]\t0x%016lx\n",
				vcpu, u64);
	}
	
	return (error);
}