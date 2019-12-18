#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  val; } ;
struct TYPE_7__ {int /*<<< orphan*/  val; } ;
struct TYPE_9__ {TYPE_3__ guest; TYPE_2__ host; } ;
struct TYPE_6__ {int /*<<< orphan*/  msr_bitmap; } ;
struct TYPE_10__ {int vmcs02_initialized; TYPE_1__ vmcs02; } ;
struct vcpu_vmx {TYPE_4__ msr_autoload; int /*<<< orphan*/  pml_pg; TYPE_5__ nested; int /*<<< orphan*/  vcpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENCLS_EXITING_BITMAP ; 
 int /*<<< orphan*/  EPT_POINTER ; 
 int /*<<< orphan*/  GUEST_PML_INDEX ; 
 int /*<<< orphan*/  MSR_BITMAP ; 
 int /*<<< orphan*/  PML_ADDRESS ; 
 scalar_t__ PML_ENTITY_NUM ; 
 scalar_t__ POSTED_INTR_NESTED_VECTOR ; 
 int /*<<< orphan*/  POSTED_INTR_NV ; 
 int /*<<< orphan*/  VM_ENTRY_MSR_LOAD_ADDR ; 
 int /*<<< orphan*/  VM_EXIT_MSR_LOAD_ADDR ; 
 int /*<<< orphan*/  VM_EXIT_MSR_STORE_COUNT ; 
 int /*<<< orphan*/  VM_FUNCTION_CONTROL ; 
 unsigned long long __pa (int /*<<< orphan*/ ) ; 
 unsigned long long construct_eptp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_has_vmx_encls_vmexit () ; 
 scalar_t__ cpu_has_vmx_msr_bitmap () ; 
 scalar_t__ cpu_has_vmx_posted_intr () ; 
 scalar_t__ cpu_has_vmx_vmfunc () ; 
 scalar_t__ enable_ept ; 
 scalar_t__ enable_pml ; 
 scalar_t__ nested_early_check ; 
 unsigned long long page_to_phys (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmcs_write16 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  vmcs_write32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmcs_write64 (int /*<<< orphan*/ ,unsigned long long) ; 
 int /*<<< orphan*/  vmx_set_constant_host_state (struct vcpu_vmx*) ; 

__attribute__((used)) static void prepare_vmcs02_constant_state(struct vcpu_vmx *vmx)
{
	/*
	 * If vmcs02 hasn't been initialized, set the constant vmcs02 state
	 * according to L0's settings (vmcs12 is irrelevant here).  Host
	 * fields that come from L0 and are not constant, e.g. HOST_CR3,
	 * will be set as needed prior to VMLAUNCH/VMRESUME.
	 */
	if (vmx->nested.vmcs02_initialized)
		return;
	vmx->nested.vmcs02_initialized = true;

	/*
	 * We don't care what the EPTP value is we just need to guarantee
	 * it's valid so we don't get a false positive when doing early
	 * consistency checks.
	 */
	if (enable_ept && nested_early_check)
		vmcs_write64(EPT_POINTER, construct_eptp(&vmx->vcpu, 0));

	/* All VMFUNCs are currently emulated through L0 vmexits.  */
	if (cpu_has_vmx_vmfunc())
		vmcs_write64(VM_FUNCTION_CONTROL, 0);

	if (cpu_has_vmx_posted_intr())
		vmcs_write16(POSTED_INTR_NV, POSTED_INTR_NESTED_VECTOR);

	if (cpu_has_vmx_msr_bitmap())
		vmcs_write64(MSR_BITMAP, __pa(vmx->nested.vmcs02.msr_bitmap));

	/*
	 * The PML address never changes, so it is constant in vmcs02.
	 * Conceptually we want to copy the PML index from vmcs01 here,
	 * and then back to vmcs01 on nested vmexit.  But since we flush
	 * the log and reset GUEST_PML_INDEX on each vmexit, the PML
	 * index is also effectively constant in vmcs02.
	 */
	if (enable_pml) {
		vmcs_write64(PML_ADDRESS, page_to_phys(vmx->pml_pg));
		vmcs_write16(GUEST_PML_INDEX, PML_ENTITY_NUM - 1);
	}

	if (cpu_has_vmx_encls_vmexit())
		vmcs_write64(ENCLS_EXITING_BITMAP, -1ull);

	/*
	 * Set the MSR load/store lists to match L0's settings.  Only the
	 * addresses are constant (for vmcs02), the counts can change based
	 * on L2's behavior, e.g. switching to/from long mode.
	 */
	vmcs_write32(VM_EXIT_MSR_STORE_COUNT, 0);
	vmcs_write64(VM_EXIT_MSR_LOAD_ADDR, __pa(vmx->msr_autoload.host.val));
	vmcs_write64(VM_ENTRY_MSR_LOAD_ADDR, __pa(vmx->msr_autoload.guest.val));

	vmx_set_constant_host_state(vmx);
}