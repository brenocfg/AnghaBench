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
typedef  int /*<<< orphan*/  uint16_t ;
struct al_hal_eth_adapter {int dummy; } ;
typedef  enum al_eth_an_lt_lane { ____Placeholder_al_eth_an_lt_lane } al_eth_an_lt_lane ;
typedef  int al_bool ;

/* Variables and functions */
 int /*<<< orphan*/  AL_ETH_KR_PMD_STATUS ; 
 int /*<<< orphan*/  AL_ETH_KR_PMD_STATUS_RECEIVER_FRAME_LOCK_SHIFT ; 
 int /*<<< orphan*/  AL_ETH_LT_REGS ; 
 scalar_t__ AL_REG_BIT_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  al_eth_an_lt_reg_read (struct al_hal_eth_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

al_bool al_eth_kr_receiver_frame_lock_get(struct al_hal_eth_adapter *adapter,
					  enum al_eth_an_lt_lane lane)
{
	uint16_t reg;

	reg = al_eth_an_lt_reg_read(adapter, AL_ETH_KR_PMD_STATUS, AL_ETH_LT_REGS, lane);

	return (AL_REG_BIT_GET(reg,
			AL_ETH_KR_PMD_STATUS_RECEIVER_FRAME_LOCK_SHIFT) != 0);
}