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
typedef  scalar_t__ u64 ;
struct TYPE_5__ {scalar_t__ revision_id; } ;
struct vmcs12 {TYPE_1__ hdr; } ;
struct TYPE_8__ {TYPE_2__* hva; } ;
struct TYPE_7__ {scalar_t__ hv_evmcs_vmptr; unsigned long long current_vmptr; int dirty_vmcs12; TYPE_2__* hv_evmcs; TYPE_4__ hv_evmcs_map; int /*<<< orphan*/  enlightened_vmcs_enabled; } ;
struct vcpu_vmx {TYPE_3__ nested; } ;
struct kvm_vcpu {int dummy; } ;
struct TYPE_6__ {scalar_t__ revision_id; int /*<<< orphan*/  hv_clean_fields; } ;

/* Variables and functions */
 int /*<<< orphan*/  HV_VMX_ENLIGHTENED_CLEAN_FIELD_ALL ; 
 scalar_t__ KVM_EVMCS_VERSION ; 
 scalar_t__ VMCS12_REVISION ; 
 struct vmcs12* get_vmcs12 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  gpa_to_gfn (scalar_t__) ; 
 scalar_t__ kvm_vcpu_map (struct kvm_vcpu*,int /*<<< orphan*/ ,TYPE_4__*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  memset (struct vmcs12*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nested_enlightened_vmentry (struct kvm_vcpu*,scalar_t__*) ; 
 int /*<<< orphan*/  nested_release_evmcs (struct kvm_vcpu*) ; 
 struct vcpu_vmx* to_vmx (struct kvm_vcpu*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int nested_vmx_handle_enlightened_vmptrld(struct kvm_vcpu *vcpu,
						 bool from_launch)
{
	struct vcpu_vmx *vmx = to_vmx(vcpu);
	bool evmcs_gpa_changed = false;
	u64 evmcs_gpa;

	if (likely(!vmx->nested.enlightened_vmcs_enabled))
		return 1;

	if (!nested_enlightened_vmentry(vcpu, &evmcs_gpa))
		return 1;

	if (unlikely(evmcs_gpa != vmx->nested.hv_evmcs_vmptr)) {
		if (!vmx->nested.hv_evmcs)
			vmx->nested.current_vmptr = -1ull;

		nested_release_evmcs(vcpu);

		if (kvm_vcpu_map(vcpu, gpa_to_gfn(evmcs_gpa),
				 &vmx->nested.hv_evmcs_map))
			return 0;

		vmx->nested.hv_evmcs = vmx->nested.hv_evmcs_map.hva;

		/*
		 * Currently, KVM only supports eVMCS version 1
		 * (== KVM_EVMCS_VERSION) and thus we expect guest to set this
		 * value to first u32 field of eVMCS which should specify eVMCS
		 * VersionNumber.
		 *
		 * Guest should be aware of supported eVMCS versions by host by
		 * examining CPUID.0x4000000A.EAX[0:15]. Host userspace VMM is
		 * expected to set this CPUID leaf according to the value
		 * returned in vmcs_version from nested_enable_evmcs().
		 *
		 * However, it turns out that Microsoft Hyper-V fails to comply
		 * to their own invented interface: When Hyper-V use eVMCS, it
		 * just sets first u32 field of eVMCS to revision_id specified
		 * in MSR_IA32_VMX_BASIC. Instead of used eVMCS version number
		 * which is one of the supported versions specified in
		 * CPUID.0x4000000A.EAX[0:15].
		 *
		 * To overcome Hyper-V bug, we accept here either a supported
		 * eVMCS version or VMCS12 revision_id as valid values for first
		 * u32 field of eVMCS.
		 */
		if ((vmx->nested.hv_evmcs->revision_id != KVM_EVMCS_VERSION) &&
		    (vmx->nested.hv_evmcs->revision_id != VMCS12_REVISION)) {
			nested_release_evmcs(vcpu);
			return 0;
		}

		vmx->nested.dirty_vmcs12 = true;
		vmx->nested.hv_evmcs_vmptr = evmcs_gpa;

		evmcs_gpa_changed = true;
		/*
		 * Unlike normal vmcs12, enlightened vmcs12 is not fully
		 * reloaded from guest's memory (read only fields, fields not
		 * present in struct hv_enlightened_vmcs, ...). Make sure there
		 * are no leftovers.
		 */
		if (from_launch) {
			struct vmcs12 *vmcs12 = get_vmcs12(vcpu);
			memset(vmcs12, 0, sizeof(*vmcs12));
			vmcs12->hdr.revision_id = VMCS12_REVISION;
		}

	}

	/*
	 * Clean fields data can't de used on VMLAUNCH and when we switch
	 * between different L2 guests as KVM keeps a single VMCS12 per L1.
	 */
	if (from_launch || evmcs_gpa_changed)
		vmx->nested.hv_evmcs->hv_clean_fields &=
			~HV_VMX_ENLIGHTENED_CLEAN_FIELD_ALL;

	return 1;
}