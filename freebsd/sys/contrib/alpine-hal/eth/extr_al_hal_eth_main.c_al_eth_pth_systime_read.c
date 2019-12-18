#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  scalar_t__ uint32_t ;
struct al_hal_eth_adapter {TYPE_2__* ec_regs_base; } ;
struct al_eth_pth_time {int femto; scalar_t__ seconds; } ;
struct TYPE_3__ {int /*<<< orphan*/  system_time_seconds; int /*<<< orphan*/  system_time_subseconds_msb; } ;
struct TYPE_4__ {TYPE_1__ pth; } ;

/* Variables and functions */
 scalar_t__ al_reg_read32 (int /*<<< orphan*/ *) ; 

int al_eth_pth_systime_read(struct al_hal_eth_adapter *adapter,
			    struct al_eth_pth_time *systime)
{
	uint32_t reg;

	/* first we must read the subseconds MSB so the seconds register will be
	 * shadowed
	 */
	reg = al_reg_read32(&adapter->ec_regs_base->pth.system_time_subseconds_msb);
	systime->femto = (uint64_t)reg << 18;
	reg = al_reg_read32(&adapter->ec_regs_base->pth.system_time_seconds);
	systime->seconds = reg;

	return 0;
}