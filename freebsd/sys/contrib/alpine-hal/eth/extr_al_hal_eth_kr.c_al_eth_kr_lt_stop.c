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
struct al_hal_eth_adapter {int /*<<< orphan*/  name; } ;
typedef  enum al_eth_an_lt_lane { ____Placeholder_al_eth_an_lt_lane } al_eth_an_lt_lane ;

/* Variables and functions */
 int /*<<< orphan*/  AL_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AL_ETH_KR_PMD_CONTROL ; 
 int /*<<< orphan*/  AL_ETH_KR_PMD_CONTROL_RESTART ; 
 int /*<<< orphan*/  AL_ETH_LT_REGS ; 
 int /*<<< orphan*/  al_dbg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  al_eth_an_lt_reg_write (struct al_hal_eth_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void al_eth_kr_lt_stop(struct al_hal_eth_adapter *adapter,
		       enum al_eth_an_lt_lane lane)
{
	al_dbg("[%s]: KR LT Stop Link Training.\n", adapter->name);

	al_eth_an_lt_reg_write(adapter, AL_ETH_KR_PMD_CONTROL, AL_ETH_LT_REGS,
			       lane, AL_BIT(AL_ETH_KR_PMD_CONTROL_RESTART));
}