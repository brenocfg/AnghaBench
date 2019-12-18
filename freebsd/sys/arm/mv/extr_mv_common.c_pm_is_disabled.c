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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 scalar_t__ soc_power_ctrl_get (scalar_t__) ; 

__attribute__((used)) static __inline int
pm_is_disabled(uint32_t mask)
{
#if SOC_MV_POWER_STAT_SUPPORTED
	return (soc_power_ctrl_get(mask) == mask ? 0 : 1);
#else
	return (0);
#endif
}