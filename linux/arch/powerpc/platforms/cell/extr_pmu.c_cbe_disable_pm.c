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
 int CBE_PM_ENABLE_PERF_MON ; 
 int cbe_read_pm (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cbe_write_pm (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pm_control ; 

void cbe_disable_pm(u32 cpu)
{
	u32 pm_ctrl;
	pm_ctrl = cbe_read_pm(cpu, pm_control) & ~CBE_PM_ENABLE_PERF_MON;
	cbe_write_pm(cpu, pm_control, pm_ctrl);
}