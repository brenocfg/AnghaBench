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

/* Variables and functions */
 scalar_t__ TIMER_CTRL_OFF ; 
 scalar_t__ local_base ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void local_timer_ctrl_clrset(u32 clr, u32 set)
{
	writel((readl(local_base + TIMER_CTRL_OFF) & ~clr) | set,
		local_base + TIMER_CTRL_OFF);
}