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
typedef  int u32 ;
struct mstp_clock_group {scalar_t__ smstpcr; scalar_t__ mstpsr; } ;
struct mstp_clock {int /*<<< orphan*/  bit_index; struct mstp_clock_group* group; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int cpg_mstp_read (struct mstp_clock_group*,scalar_t__) ; 
 struct mstp_clock* to_mstp_clock (struct clk_hw*) ; 

__attribute__((used)) static int cpg_mstp_clock_is_enabled(struct clk_hw *hw)
{
	struct mstp_clock *clock = to_mstp_clock(hw);
	struct mstp_clock_group *group = clock->group;
	u32 value;

	if (group->mstpsr)
		value = cpg_mstp_read(group, group->mstpsr);
	else
		value = cpg_mstp_read(group, group->smstpcr);

	return !(value & BIT(clock->bit_index));
}