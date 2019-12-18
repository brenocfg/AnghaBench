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
struct cpuinfo_mips {int /*<<< orphan*/  options; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIPS_CPU_DRG ; 
 int /*<<< orphan*/  MIPS_CPU_GUESTCTL0EXT ; 
 int /*<<< orphan*/  MIPS_CPU_GUESTCTL1 ; 
 int /*<<< orphan*/  MIPS_CPU_GUESTCTL2 ; 
 int /*<<< orphan*/  MIPS_CPU_GUESTID ; 
 unsigned int MIPS_GCTL0_DRG ; 
 unsigned int MIPS_GCTL0_G0E ; 
 unsigned int MIPS_GCTL0_G1 ; 
 unsigned int MIPS_GCTL0_G2 ; 
 unsigned int MIPS_GCTL0_RAD ; 
 int /*<<< orphan*/  back_to_back_c0_hazard () ; 
 unsigned int read_c0_guestctl0 () ; 
 int /*<<< orphan*/  tlbw_use_hazard () ; 
 int /*<<< orphan*/  write_c0_guestctl0 (unsigned int) ; 
 int /*<<< orphan*/  write_c0_guestctl1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void cpu_probe_guestctl0(struct cpuinfo_mips *c)
{
	unsigned int guestctl0, temp;

	guestctl0 = read_c0_guestctl0();

	if (guestctl0 & MIPS_GCTL0_G0E)
		c->options |= MIPS_CPU_GUESTCTL0EXT;
	if (guestctl0 & MIPS_GCTL0_G1)
		c->options |= MIPS_CPU_GUESTCTL1;
	if (guestctl0 & MIPS_GCTL0_G2)
		c->options |= MIPS_CPU_GUESTCTL2;
	if (!(guestctl0 & MIPS_GCTL0_RAD)) {
		c->options |= MIPS_CPU_GUESTID;

		/*
		 * Probe for Direct Root to Guest (DRG). Set GuestCtl1.RID = 0
		 * first, otherwise all data accesses will be fully virtualised
		 * as if they were performed by guest mode.
		 */
		write_c0_guestctl1(0);
		tlbw_use_hazard();

		write_c0_guestctl0(guestctl0 | MIPS_GCTL0_DRG);
		back_to_back_c0_hazard();
		temp = read_c0_guestctl0();

		if (temp & MIPS_GCTL0_DRG) {
			write_c0_guestctl0(guestctl0);
			c->options |= MIPS_CPU_DRG;
		}
	}
}