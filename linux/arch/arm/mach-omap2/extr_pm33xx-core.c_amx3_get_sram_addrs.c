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
struct am33xx_pm_sram_addr {int dummy; } ;

/* Variables and functions */
 struct am33xx_pm_sram_addr am33xx_pm_sram ; 
 struct am33xx_pm_sram_addr am43xx_pm_sram ; 
 scalar_t__ soc_is_am33xx () ; 
 scalar_t__ soc_is_am437x () ; 

__attribute__((used)) static struct am33xx_pm_sram_addr *amx3_get_sram_addrs(void)
{
	if (soc_is_am33xx())
		return &am33xx_pm_sram;
	else if (soc_is_am437x())
		return &am43xx_pm_sram;
	else
		return NULL;
}