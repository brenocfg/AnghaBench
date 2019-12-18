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
struct vcpu {int /*<<< orphan*/  guestfpu; int /*<<< orphan*/  guest_xcr0; } ;

/* Variables and functions */
 int CR0_TS ; 
 int CR4_XSAVE ; 
 int /*<<< orphan*/  fpu_start_emulating () ; 
 int /*<<< orphan*/  fpu_stop_emulating () ; 
 int /*<<< orphan*/  fpusave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_xcr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int rcr0 () ; 
 int rcr4 () ; 
 int /*<<< orphan*/  rxcr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmm_get_host_xcr0 () ; 

__attribute__((used)) static void
save_guest_fpustate(struct vcpu *vcpu)
{

	if ((rcr0() & CR0_TS) == 0)
		panic("fpu emulation not enabled in host!");

	/* save guest XCR0 and restore host XCR0 */
	if (rcr4() & CR4_XSAVE) {
		vcpu->guest_xcr0 = rxcr(0);
		load_xcr(0, vmm_get_host_xcr0());
	}

	/* save guest FPU state */
	fpu_stop_emulating();
	fpusave(vcpu->guestfpu);
	fpu_start_emulating();
}