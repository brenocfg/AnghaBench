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
struct cpuinfo_x86 {int /*<<< orphan*/  loops_per_jiffy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX86_CCR3 ; 
 int /*<<< orphan*/  CX86_CCR5 ; 
 int Cx86_dir0_msb ; 
 int /*<<< orphan*/  calibrate_delay () ; 
 unsigned char getCx86 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  loops_per_jiffy ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  setCx86 (int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static void check_cx686_slop(struct cpuinfo_x86 *c)
{
	unsigned long flags;

	if (Cx86_dir0_msb == 3) {
		unsigned char ccr3, ccr5;

		local_irq_save(flags);
		ccr3 = getCx86(CX86_CCR3);
		setCx86(CX86_CCR3, (ccr3 & 0x0f) | 0x10); /* enable MAPEN */
		ccr5 = getCx86(CX86_CCR5);
		if (ccr5 & 2)
			setCx86(CX86_CCR5, ccr5 & 0xfd);  /* reset SLOP */
		setCx86(CX86_CCR3, ccr3);                 /* disable MAPEN */
		local_irq_restore(flags);

		if (ccr5 & 2) { /* possible wrong calibration done */
			pr_info("Recalibrating delay loop with SLOP bit reset\n");
			calibrate_delay();
			c->loops_per_jiffy = loops_per_jiffy;
		}
	}
}