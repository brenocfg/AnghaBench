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
struct TYPE_4__ {int efer; } ;
struct TYPE_5__ {TYPE_1__ arch; } ;
struct vcpu_vmx {TYPE_3__* guest_msrs; TYPE_2__ vcpu; } ;
struct TYPE_6__ {int data; int mask; } ;

/* Variables and functions */
 int EFER_LMA ; 
 int EFER_LME ; 
 int EFER_NX ; 
 int EFER_SCE ; 
 int /*<<< orphan*/  MSR_EFER ; 
 int /*<<< orphan*/  add_atomic_switch_msr (struct vcpu_vmx*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  clear_atomic_switch_msr (struct vcpu_vmx*,int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_has_load_ia32_efer () ; 
 scalar_t__ enable_ept ; 
 int host_efer ; 

__attribute__((used)) static bool update_transition_efer(struct vcpu_vmx *vmx, int efer_offset)
{
	u64 guest_efer = vmx->vcpu.arch.efer;
	u64 ignore_bits = 0;

	/* Shadow paging assumes NX to be available.  */
	if (!enable_ept)
		guest_efer |= EFER_NX;

	/*
	 * LMA and LME handled by hardware; SCE meaningless outside long mode.
	 */
	ignore_bits |= EFER_SCE;
#ifdef CONFIG_X86_64
	ignore_bits |= EFER_LMA | EFER_LME;
	/* SCE is meaningful only in long mode on Intel */
	if (guest_efer & EFER_LMA)
		ignore_bits &= ~(u64)EFER_SCE;
#endif

	/*
	 * On EPT, we can't emulate NX, so we must switch EFER atomically.
	 * On CPUs that support "load IA32_EFER", always switch EFER
	 * atomically, since it's faster than switching it manually.
	 */
	if (cpu_has_load_ia32_efer() ||
	    (enable_ept && ((vmx->vcpu.arch.efer ^ host_efer) & EFER_NX))) {
		if (!(guest_efer & EFER_LMA))
			guest_efer &= ~EFER_LME;
		if (guest_efer != host_efer)
			add_atomic_switch_msr(vmx, MSR_EFER,
					      guest_efer, host_efer, false);
		else
			clear_atomic_switch_msr(vmx, MSR_EFER);
		return false;
	} else {
		clear_atomic_switch_msr(vmx, MSR_EFER);

		guest_efer &= ~ignore_bits;
		guest_efer |= host_efer & ignore_bits;

		vmx->guest_msrs[efer_offset].data = guest_efer;
		vmx->guest_msrs[efer_offset].mask = ~ignore_bits;

		return true;
	}
}