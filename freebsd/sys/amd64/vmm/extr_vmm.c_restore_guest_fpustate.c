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
struct vcpu {int /*<<< orphan*/  guest_xcr0; int /*<<< orphan*/  guestfpu; } ;

/* Variables and functions */
 int CR4_XSAVE ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  fpu_start_emulating () ; 
 int /*<<< orphan*/  fpu_stop_emulating () ; 
 int /*<<< orphan*/  fpuexit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fpurestore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_xcr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rcr4 () ; 

__attribute__((used)) static void
restore_guest_fpustate(struct vcpu *vcpu)
{

	/* flush host state to the pcb */
	fpuexit(curthread);

	/* restore guest FPU state */
	fpu_stop_emulating();
	fpurestore(vcpu->guestfpu);

	/* restore guest XCR0 if XSAVE is enabled in the host */
	if (rcr4() & CR4_XSAVE)
		load_xcr(0, vcpu->guest_xcr0);

	/*
	 * The FPU is now "dirty" with the guest's state so turn on emulation
	 * to trap any access to the FPU by the host.
	 */
	fpu_start_emulating();
}