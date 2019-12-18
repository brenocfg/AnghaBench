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
struct desc_struct {scalar_t__ g; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_desc (struct desc_struct*,short) ; 
 unsigned long get_desc_limit (struct desc_struct*) ; 
 short get_segment_selector (struct pt_regs*,int) ; 
 scalar_t__ user_64bit_mode (struct pt_regs*) ; 
 scalar_t__ v8086_mode (struct pt_regs*) ; 

__attribute__((used)) static unsigned long get_seg_limit(struct pt_regs *regs, int seg_reg_idx)
{
	struct desc_struct desc;
	unsigned long limit;
	short sel;

	sel = get_segment_selector(regs, seg_reg_idx);
	if (sel < 0)
		return 0;

	if (user_64bit_mode(regs) || v8086_mode(regs))
		return -1L;

	if (!sel)
		return 0;

	if (!get_desc(&desc, sel))
		return 0;

	/*
	 * If the granularity bit is set, the limit is given in multiples
	 * of 4096. This also means that the 12 least significant bits are
	 * not tested when checking the segment limits. In practice,
	 * this means that the segment ends in (limit << 12) + 0xfff.
	 */
	limit = get_desc_limit(&desc);
	if (desc.g)
		limit = (limit << 12) + 0xfff;

	return limit;
}