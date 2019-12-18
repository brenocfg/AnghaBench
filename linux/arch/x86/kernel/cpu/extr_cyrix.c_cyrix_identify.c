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
struct cpuinfo_x86 {int x86; int /*<<< orphan*/  x86_vendor; int /*<<< orphan*/  x86_vendor_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX86_CCR3 ; 
 int /*<<< orphan*/  CX86_CCR4 ; 
 int /*<<< orphan*/  X86_VENDOR_CYRIX ; 
 int /*<<< orphan*/  do_cyrix_devid (unsigned char*,unsigned char*) ; 
 int getCx86 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  setCx86 (int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ test_cyrix_52div () ; 

__attribute__((used)) static void cyrix_identify(struct cpuinfo_x86 *c)
{
	/* Detect Cyrix with disabled CPUID */
	if (c->x86 == 4 && test_cyrix_52div()) {
		unsigned char dir0, dir1;

		strcpy(c->x86_vendor_id, "CyrixInstead");
		c->x86_vendor = X86_VENDOR_CYRIX;

		/* Actually enable cpuid on the older cyrix */

		/* Retrieve CPU revisions */

		do_cyrix_devid(&dir0, &dir1);

		dir0 >>= 4;

		/* Check it is an affected model */

		if (dir0 == 5 || dir0 == 3) {
			unsigned char ccr3;
			unsigned long flags;
			pr_info("Enabling CPUID on Cyrix processor.\n");
			local_irq_save(flags);
			ccr3 = getCx86(CX86_CCR3);
			/* enable MAPEN  */
			setCx86(CX86_CCR3, (ccr3 & 0x0f) | 0x10);
			/* enable cpuid  */
			setCx86(CX86_CCR4, getCx86(CX86_CCR4) | 0x80);
			/* disable MAPEN */
			setCx86(CX86_CCR3, ccr3);
			local_irq_restore(flags);
		}
	}
}