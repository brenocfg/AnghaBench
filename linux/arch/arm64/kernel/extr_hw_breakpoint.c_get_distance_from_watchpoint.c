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
typedef  unsigned long u64 ;
typedef  unsigned long u32 ;
struct arch_hw_breakpoint_ctrl {int /*<<< orphan*/  len; } ;

/* Variables and functions */
 unsigned long __ffs (int /*<<< orphan*/ ) ; 
 unsigned long __fls (int /*<<< orphan*/ ) ; 
 unsigned long untagged_addr (unsigned long) ; 

__attribute__((used)) static u64 get_distance_from_watchpoint(unsigned long addr, u64 val,
					struct arch_hw_breakpoint_ctrl *ctrl)
{
	u64 wp_low, wp_high;
	u32 lens, lene;

	addr = untagged_addr(addr);

	lens = __ffs(ctrl->len);
	lene = __fls(ctrl->len);

	wp_low = val + lens;
	wp_high = val + lene;
	if (addr < wp_low)
		return wp_low - addr;
	else if (addr > wp_high)
		return addr - wp_high;
	else
		return 0;
}