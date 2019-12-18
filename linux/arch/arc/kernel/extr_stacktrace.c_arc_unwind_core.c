#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  r31; int /*<<< orphan*/  r63; } ;
struct unwind_frame_info {TYPE_1__ regs; } ;
struct task_struct {int dummy; } ;
struct pt_regs {int dummy; } ;

/* Variables and functions */
 unsigned int UNW_PC (struct unwind_frame_info*) ; 
 int /*<<< orphan*/  __kernel_text_address (unsigned int) ; 
 int arc_unwind (struct unwind_frame_info*) ; 
 int /*<<< orphan*/  pr_warn_once (char*) ; 
 int /*<<< orphan*/  seed_unwind_frame_info (struct task_struct*,struct pt_regs*,struct unwind_frame_info*) ; 

unsigned int
arc_unwind_core(struct task_struct *tsk, struct pt_regs *regs,
		int (*consumer_fn) (unsigned int, void *), void *arg)
{
#ifdef CONFIG_ARC_DW2_UNWIND
	int ret = 0;
	unsigned int address;
	struct unwind_frame_info frame_info;

	seed_unwind_frame_info(tsk, regs, &frame_info);

	while (1) {
		address = UNW_PC(&frame_info);

		if (!address || !__kernel_text_address(address))
			break;

		if (consumer_fn(address, arg) == -1)
			break;

		ret = arc_unwind(&frame_info);
		if (ret)
			break;

		frame_info.regs.r63 = frame_info.regs.r31;
	}

	return address;		/* return the last address it saw */
#else
	/* On ARC, only Dward based unwinder works. fp based backtracing is
	 * not possible (-fno-omit-frame-pointer) because of the way function
	 * prelogue is setup (callee regs saved and then fp set and not other
	 * way around
	 */
	pr_warn_once("CONFIG_ARC_DW2_UNWIND needs to be enabled\n");
	return 0;

#endif
}