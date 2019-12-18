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
struct ccu_common {scalar_t__ reg; scalar_t__ base; } ;

/* Variables and functions */
 int readl (scalar_t__) ; 

int ccu_gate_helper_is_enabled(struct ccu_common *common, u32 gate)
{
	if (!gate)
		return 1;

	return readl(common->base + common->reg) & gate;
}