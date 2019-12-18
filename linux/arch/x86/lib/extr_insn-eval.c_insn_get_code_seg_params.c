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
struct desc_struct {int type; int l; int d; } ;

/* Variables and functions */
 int BIT (int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  INAT_SEG_REG_CS ; 
 int INSN_CODE_SEG_PARAMS (int,int) ; 
 int /*<<< orphan*/  get_desc (struct desc_struct*,short) ; 
 short get_segment_selector (struct pt_regs*,int /*<<< orphan*/ ) ; 
 scalar_t__ v8086_mode (struct pt_regs*) ; 

int insn_get_code_seg_params(struct pt_regs *regs)
{
	struct desc_struct desc;
	short sel;

	if (v8086_mode(regs))
		/* Address and operand size are both 16-bit. */
		return INSN_CODE_SEG_PARAMS(2, 2);

	sel = get_segment_selector(regs, INAT_SEG_REG_CS);
	if (sel < 0)
		return sel;

	if (!get_desc(&desc, sel))
		return -EINVAL;

	/*
	 * The most significant byte of the Type field of the segment descriptor
	 * determines whether a segment contains data or code. If this is a data
	 * segment, return error.
	 */
	if (!(desc.type & BIT(3)))
		return -EINVAL;

	switch ((desc.l << 1) | desc.d) {
	case 0: /*
		 * Legacy mode. CS.L=0, CS.D=0. Address and operand size are
		 * both 16-bit.
		 */
		return INSN_CODE_SEG_PARAMS(2, 2);
	case 1: /*
		 * Legacy mode. CS.L=0, CS.D=1. Address and operand size are
		 * both 32-bit.
		 */
		return INSN_CODE_SEG_PARAMS(4, 4);
	case 2: /*
		 * IA-32e 64-bit mode. CS.L=1, CS.D=0. Address size is 64-bit;
		 * operand size is 32-bit.
		 */
		return INSN_CODE_SEG_PARAMS(4, 8);
	case 3: /* Invalid setting. CS.L=1, CS.D=1 */
		/* fall through */
	default:
		return -EINVAL;
	}
}