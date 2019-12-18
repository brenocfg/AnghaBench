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
struct vmcs12 {int /*<<< orphan*/  guest_bndcfgs; void* guest_pending_dbg_exceptions; void* guest_idtr_base; void* guest_gdtr_base; void* guest_tr_base; void* guest_ldtr_base; void* guest_gs_base; void* guest_fs_base; void* guest_ds_base; void* guest_ss_base; void* guest_cs_base; void* guest_es_base; void* guest_tr_ar_bytes; void* guest_ldtr_ar_bytes; void* guest_gs_ar_bytes; void* guest_fs_ar_bytes; void* guest_ds_ar_bytes; void* guest_es_ar_bytes; void* guest_idtr_limit; void* guest_gdtr_limit; void* guest_tr_limit; void* guest_ldtr_limit; void* guest_gs_limit; void* guest_fs_limit; void* guest_ds_limit; void* guest_ss_limit; void* guest_cs_limit; void* guest_es_limit; void* guest_tr_selector; void* guest_ldtr_selector; void* guest_gs_selector; void* guest_fs_selector; void* guest_ds_selector; void* guest_ss_selector; void* guest_cs_selector; void* guest_es_selector; } ;
struct TYPE_2__ {int need_sync_vmcs02_to_vmcs12_rare; } ;
struct vcpu_vmx {TYPE_1__ nested; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GUEST_BNDCFGS ; 
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
 int /*<<< orphan*/  GUEST_PENDING_DBG_EXCEPTIONS ; 
 int /*<<< orphan*/  GUEST_SS_BASE ; 
 int /*<<< orphan*/  GUEST_SS_LIMIT ; 
 int /*<<< orphan*/  GUEST_SS_SELECTOR ; 
 int /*<<< orphan*/  GUEST_TR_AR_BYTES ; 
 int /*<<< orphan*/  GUEST_TR_BASE ; 
 int /*<<< orphan*/  GUEST_TR_LIMIT ; 
 int /*<<< orphan*/  GUEST_TR_SELECTOR ; 
 scalar_t__ kvm_mpx_supported () ; 
 struct vcpu_vmx* to_vmx (struct kvm_vcpu*) ; 
 void* vmcs_read16 (int /*<<< orphan*/ ) ; 
 void* vmcs_read32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmcs_read64 (int /*<<< orphan*/ ) ; 
 void* vmcs_readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sync_vmcs02_to_vmcs12_rare(struct kvm_vcpu *vcpu,
				       struct vmcs12 *vmcs12)
{
	struct vcpu_vmx *vmx = to_vmx(vcpu);

	vmcs12->guest_es_selector = vmcs_read16(GUEST_ES_SELECTOR);
	vmcs12->guest_cs_selector = vmcs_read16(GUEST_CS_SELECTOR);
	vmcs12->guest_ss_selector = vmcs_read16(GUEST_SS_SELECTOR);
	vmcs12->guest_ds_selector = vmcs_read16(GUEST_DS_SELECTOR);
	vmcs12->guest_fs_selector = vmcs_read16(GUEST_FS_SELECTOR);
	vmcs12->guest_gs_selector = vmcs_read16(GUEST_GS_SELECTOR);
	vmcs12->guest_ldtr_selector = vmcs_read16(GUEST_LDTR_SELECTOR);
	vmcs12->guest_tr_selector = vmcs_read16(GUEST_TR_SELECTOR);
	vmcs12->guest_es_limit = vmcs_read32(GUEST_ES_LIMIT);
	vmcs12->guest_cs_limit = vmcs_read32(GUEST_CS_LIMIT);
	vmcs12->guest_ss_limit = vmcs_read32(GUEST_SS_LIMIT);
	vmcs12->guest_ds_limit = vmcs_read32(GUEST_DS_LIMIT);
	vmcs12->guest_fs_limit = vmcs_read32(GUEST_FS_LIMIT);
	vmcs12->guest_gs_limit = vmcs_read32(GUEST_GS_LIMIT);
	vmcs12->guest_ldtr_limit = vmcs_read32(GUEST_LDTR_LIMIT);
	vmcs12->guest_tr_limit = vmcs_read32(GUEST_TR_LIMIT);
	vmcs12->guest_gdtr_limit = vmcs_read32(GUEST_GDTR_LIMIT);
	vmcs12->guest_idtr_limit = vmcs_read32(GUEST_IDTR_LIMIT);
	vmcs12->guest_es_ar_bytes = vmcs_read32(GUEST_ES_AR_BYTES);
	vmcs12->guest_ds_ar_bytes = vmcs_read32(GUEST_DS_AR_BYTES);
	vmcs12->guest_fs_ar_bytes = vmcs_read32(GUEST_FS_AR_BYTES);
	vmcs12->guest_gs_ar_bytes = vmcs_read32(GUEST_GS_AR_BYTES);
	vmcs12->guest_ldtr_ar_bytes = vmcs_read32(GUEST_LDTR_AR_BYTES);
	vmcs12->guest_tr_ar_bytes = vmcs_read32(GUEST_TR_AR_BYTES);
	vmcs12->guest_es_base = vmcs_readl(GUEST_ES_BASE);
	vmcs12->guest_cs_base = vmcs_readl(GUEST_CS_BASE);
	vmcs12->guest_ss_base = vmcs_readl(GUEST_SS_BASE);
	vmcs12->guest_ds_base = vmcs_readl(GUEST_DS_BASE);
	vmcs12->guest_fs_base = vmcs_readl(GUEST_FS_BASE);
	vmcs12->guest_gs_base = vmcs_readl(GUEST_GS_BASE);
	vmcs12->guest_ldtr_base = vmcs_readl(GUEST_LDTR_BASE);
	vmcs12->guest_tr_base = vmcs_readl(GUEST_TR_BASE);
	vmcs12->guest_gdtr_base = vmcs_readl(GUEST_GDTR_BASE);
	vmcs12->guest_idtr_base = vmcs_readl(GUEST_IDTR_BASE);
	vmcs12->guest_pending_dbg_exceptions =
		vmcs_readl(GUEST_PENDING_DBG_EXCEPTIONS);
	if (kvm_mpx_supported())
		vmcs12->guest_bndcfgs = vmcs_read64(GUEST_BNDCFGS);

	vmx->nested.need_sync_vmcs02_to_vmcs12_rare = false;
}