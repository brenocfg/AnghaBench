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
struct desc_struct {int dummy; } ;

/* Variables and functions */
 int INAT_SEG_REG_FS ; 
 int INAT_SEG_REG_GS ; 
 int /*<<< orphan*/  MSR_FS_BASE ; 
 int /*<<< orphan*/  MSR_KERNEL_GS_BASE ; 
 int /*<<< orphan*/  get_desc (struct desc_struct*,short) ; 
 unsigned long get_desc_base (struct desc_struct*) ; 
 short get_segment_selector (struct pt_regs*,int) ; 
 int /*<<< orphan*/  rdmsrl (int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ user_64bit_mode (struct pt_regs*) ; 
 scalar_t__ v8086_mode (struct pt_regs*) ; 

unsigned long insn_get_seg_base(struct pt_regs *regs, int seg_reg_idx)
{
	struct desc_struct desc;
	short sel;

	sel = get_segment_selector(regs, seg_reg_idx);
	if (sel < 0)
		return -1L;

	if (v8086_mode(regs))
		/*
		 * Base is simply the segment selector shifted 4
		 * bits to the right.
		 */
		return (unsigned long)(sel << 4);

	if (user_64bit_mode(regs)) {
		/*
		 * Only FS or GS will have a base address, the rest of
		 * the segments' bases are forced to 0.
		 */
		unsigned long base;

		if (seg_reg_idx == INAT_SEG_REG_FS)
			rdmsrl(MSR_FS_BASE, base);
		else if (seg_reg_idx == INAT_SEG_REG_GS)
			/*
			 * swapgs was called at the kernel entry point. Thus,
			 * MSR_KERNEL_GS_BASE will have the user-space GS base.
			 */
			rdmsrl(MSR_KERNEL_GS_BASE, base);
		else
			base = 0;
		return base;
	}

	/* In protected mode the segment selector cannot be null. */
	if (!sel)
		return -1L;

	if (!get_desc(&desc, sel))
		return -1L;

	return get_desc_base(&desc);
}