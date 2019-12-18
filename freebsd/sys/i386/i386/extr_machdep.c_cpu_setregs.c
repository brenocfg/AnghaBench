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

/* Variables and functions */
 unsigned int CR0_AM ; 
 unsigned int CR0_MP ; 
 unsigned int CR0_NE ; 
 unsigned int CR0_TS ; 
 unsigned int CR0_WP ; 
 int /*<<< orphan*/  _udatasel ; 
 int /*<<< orphan*/  load_cr0 (unsigned int) ; 
 int /*<<< orphan*/  load_gs (int /*<<< orphan*/ ) ; 
 unsigned int rcr0 () ; 

void
cpu_setregs(void)
{
	unsigned int cr0;

	cr0 = rcr0();

	/*
	 * CR0_MP, CR0_NE and CR0_TS are set for NPX (FPU) support:
	 *
	 * Prepare to trap all ESC (i.e., NPX) instructions and all WAIT
	 * instructions.  We must set the CR0_MP bit and use the CR0_TS
	 * bit to control the trap, because setting the CR0_EM bit does
	 * not cause WAIT instructions to trap.  It's important to trap
	 * WAIT instructions - otherwise the "wait" variants of no-wait
	 * control instructions would degenerate to the "no-wait" variants
	 * after FP context switches but work correctly otherwise.  It's
	 * particularly important to trap WAITs when there is no NPX -
	 * otherwise the "wait" variants would always degenerate.
	 *
	 * Try setting CR0_NE to get correct error reporting on 486DX's.
	 * Setting it should fail or do nothing on lesser processors.
	 */
	cr0 |= CR0_MP | CR0_NE | CR0_TS | CR0_WP | CR0_AM;
	load_cr0(cr0);
	load_gs(_udatasel);
}