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
struct vmcs_host_state {int gs_sel; int fs_sel; int ds_sel; int es_sel; scalar_t__ ldt_sel; } ;
struct TYPE_5__ {int /*<<< orphan*/  host_state_reload; } ;
struct TYPE_6__ {TYPE_2__ stat; } ;
struct vcpu_vmx {int guest_state_loaded; int guest_msrs_ready; int /*<<< orphan*/  msr_host_kernel_gs_base; int /*<<< orphan*/  msr_guest_kernel_gs_base; TYPE_3__ vcpu; TYPE_1__* loaded_vmcs; } ;
struct TYPE_4__ {struct vmcs_host_state host_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_KERNEL_GS_BASE ; 
 int /*<<< orphan*/  ds ; 
 int /*<<< orphan*/  es ; 
 int /*<<< orphan*/  fs ; 
 int /*<<< orphan*/  gs ; 
 int /*<<< orphan*/  invalidate_tss_limit () ; 
 int /*<<< orphan*/  kvm_load_ldt (scalar_t__) ; 
 int /*<<< orphan*/  load_fixmap_gdt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_gs_index (int) ; 
 int /*<<< orphan*/  loadsegment (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  raw_smp_processor_id () ; 
 int /*<<< orphan*/  rdmsrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vmx_prepare_switch_to_host(struct vcpu_vmx *vmx)
{
	struct vmcs_host_state *host_state;

	if (!vmx->guest_state_loaded)
		return;

	host_state = &vmx->loaded_vmcs->host_state;

	++vmx->vcpu.stat.host_state_reload;

#ifdef CONFIG_X86_64
	rdmsrl(MSR_KERNEL_GS_BASE, vmx->msr_guest_kernel_gs_base);
#endif
	if (host_state->ldt_sel || (host_state->gs_sel & 7)) {
		kvm_load_ldt(host_state->ldt_sel);
#ifdef CONFIG_X86_64
		load_gs_index(host_state->gs_sel);
#else
		loadsegment(gs, host_state->gs_sel);
#endif
	}
	if (host_state->fs_sel & 7)
		loadsegment(fs, host_state->fs_sel);
#ifdef CONFIG_X86_64
	if (unlikely(host_state->ds_sel | host_state->es_sel)) {
		loadsegment(ds, host_state->ds_sel);
		loadsegment(es, host_state->es_sel);
	}
#endif
	invalidate_tss_limit();
#ifdef CONFIG_X86_64
	wrmsrl(MSR_KERNEL_GS_BASE, vmx->msr_host_kernel_gs_base);
#endif
	load_fixmap_gdt(raw_smp_processor_id());
	vmx->guest_state_loaded = false;
	vmx->guest_msrs_ready = false;
}