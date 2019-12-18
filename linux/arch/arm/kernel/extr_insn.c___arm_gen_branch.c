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

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_THUMB2_KERNEL ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 unsigned long __arm_gen_branch_arm (unsigned long,unsigned long,int) ; 
 unsigned long __arm_gen_branch_thumb2 (unsigned long,unsigned long,int) ; 

unsigned long
__arm_gen_branch(unsigned long pc, unsigned long addr, bool link)
{
	if (IS_ENABLED(CONFIG_THUMB2_KERNEL))
		return __arm_gen_branch_thumb2(pc, addr, link);
	else
		return __arm_gen_branch_arm(pc, addr, link);
}