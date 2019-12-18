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
 int /*<<< orphan*/  BMIPS_WARM_RESTART_VEC ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned long CKSEG0 ; 
#define  CPU_BMIPS3300 131 
#define  CPU_BMIPS4350 130 
#define  CPU_BMIPS4380 129 
#define  CPU_BMIPS5000 128 
 int /*<<< orphan*/  RESET_FROM_KSEG0 ; 
 int /*<<< orphan*/  __sync () ; 
 int /*<<< orphan*/  bmips_nmi_handler_setup ; 
 int /*<<< orphan*/  bmips_set_reset_vec (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bmips_smp_int_vec ; 
 int /*<<< orphan*/ * board_nmi_handler_setup ; 
 int current_cpu_type () ; 
 unsigned long ebase ; 
 int /*<<< orphan*/  set_uncached_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  write_c0_ebase (unsigned long) ; 

void bmips_ebase_setup(void)
{
	unsigned long new_ebase = ebase;

	BUG_ON(ebase != CKSEG0);

	switch (current_cpu_type()) {
	case CPU_BMIPS4350:
		/*
		 * BMIPS4350 cannot relocate the normal vectors, but it
		 * can relocate the BEV=1 vectors.  So CPU1 starts up at
		 * the relocated BEV=1, IV=0 general exception vector @
		 * 0xa000_0380.
		 *
		 * set_uncached_handler() is used here because:
		 *  - CPU1 will run this from uncached space
		 *  - None of the cacheflush functions are set up yet
		 */
		set_uncached_handler(BMIPS_WARM_RESTART_VEC - CKSEG0,
			&bmips_smp_int_vec, 0x80);
		__sync();
		return;
	case CPU_BMIPS3300:
	case CPU_BMIPS4380:
		/*
		 * 0x8000_0000: reset/NMI (initially in kseg1)
		 * 0x8000_0400: normal vectors
		 */
		new_ebase = 0x80000400;
		bmips_set_reset_vec(0, RESET_FROM_KSEG0);
		break;
	case CPU_BMIPS5000:
		/*
		 * 0x8000_0000: reset/NMI (initially in kseg1)
		 * 0x8000_1000: normal vectors
		 */
		new_ebase = 0x80001000;
		bmips_set_reset_vec(0, RESET_FROM_KSEG0);
		write_c0_ebase(new_ebase);
		break;
	default:
		return;
	}

	board_nmi_handler_setup = &bmips_nmi_handler_setup;
	ebase = new_ebase;
}