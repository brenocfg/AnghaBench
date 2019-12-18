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
 int L2X0_EVENT_CNT_CFG_INT_DISABLED ; 
 int L2X0_EVENT_CNT_CFG_SRC_SHIFT ; 
 int /*<<< orphan*/  l2x0_pmu_counter_config_write (int,int) ; 

__attribute__((used)) static void __l2x0_pmu_event_enable(int idx, u32 event)
{
	u32 val;

	val = event << L2X0_EVENT_CNT_CFG_SRC_SHIFT;
	val |= L2X0_EVENT_CNT_CFG_INT_DISABLED;
	l2x0_pmu_counter_config_write(idx, val);
}