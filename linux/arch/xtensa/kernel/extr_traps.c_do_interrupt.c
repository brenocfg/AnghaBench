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
struct pt_regs {int dummy; } ;

/* Variables and functions */
 unsigned int LOCKLEVEL ; 
#define  XCHAL_INTLEVEL1_MASK 134 
#define  XCHAL_INTLEVEL2_MASK 133 
#define  XCHAL_INTLEVEL3_MASK 132 
#define  XCHAL_INTLEVEL4_MASK 131 
#define  XCHAL_INTLEVEL5_MASK 130 
#define  XCHAL_INTLEVEL6_MASK 129 
#define  XCHAL_INTLEVEL7_MASK 128 
 int /*<<< orphan*/  __ffs (unsigned int) ; 
 int /*<<< orphan*/  do_IRQ (int /*<<< orphan*/ ,struct pt_regs*) ; 
 unsigned int intenable ; 
 int /*<<< orphan*/  interrupt ; 
 int /*<<< orphan*/  irq_enter () ; 
 int /*<<< orphan*/  irq_exit () ; 
 struct pt_regs* set_irq_regs (struct pt_regs*) ; 
 int /*<<< orphan*/  trace_hardirqs_off () ; 
 unsigned int xtensa_get_sr (int /*<<< orphan*/ ) ; 

void do_interrupt(struct pt_regs *regs)
{
	static const unsigned int_level_mask[] = {
		0,
		XCHAL_INTLEVEL1_MASK,
		XCHAL_INTLEVEL2_MASK,
		XCHAL_INTLEVEL3_MASK,
		XCHAL_INTLEVEL4_MASK,
		XCHAL_INTLEVEL5_MASK,
		XCHAL_INTLEVEL6_MASK,
		XCHAL_INTLEVEL7_MASK,
	};
	struct pt_regs *old_regs;

	trace_hardirqs_off();

	old_regs = set_irq_regs(regs);
	irq_enter();

	for (;;) {
		unsigned intread = xtensa_get_sr(interrupt);
		unsigned intenable = xtensa_get_sr(intenable);
		unsigned int_at_level = intread & intenable;
		unsigned level;

		for (level = LOCKLEVEL; level > 0; --level) {
			if (int_at_level & int_level_mask[level]) {
				int_at_level &= int_level_mask[level];
				break;
			}
		}

		if (level == 0)
			break;

		do_IRQ(__ffs(int_at_level), regs);
	}

	irq_exit();
	set_irq_regs(old_regs);
}