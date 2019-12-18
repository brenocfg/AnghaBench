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
struct al_eth_kr_status_report_data {scalar_t__ receiver_ready; int /*<<< orphan*/  c_plus; int /*<<< orphan*/  c_zero; int /*<<< orphan*/  c_minus; } ;
typedef  enum al_eth_an_lt_lane { ____Placeholder_al_eth_an_lt_lane } al_eth_an_lt_lane ;

/* Variables and functions */
 int /*<<< orphan*/  AL_ETH_KR_PMD_LD_STATUS_REPORT ; 
 int /*<<< orphan*/  AL_ETH_KR_PMD_LD_STATUS_REPORT_MINUS_MASK ; 
 int /*<<< orphan*/  AL_ETH_KR_PMD_LD_STATUS_REPORT_MINUS_SHIFT ; 
 int /*<<< orphan*/  AL_ETH_KR_PMD_LD_STATUS_REPORT_PLUS_MASK ; 
 int /*<<< orphan*/  AL_ETH_KR_PMD_LD_STATUS_REPORT_PLUS_SHIFT ; 
 int /*<<< orphan*/  AL_ETH_KR_PMD_LD_STATUS_REPORT_RECEIVER_READY_SHIFT ; 
 int /*<<< orphan*/  AL_ETH_KR_PMD_LD_STATUS_REPORT_ZERO_MASK ; 
 int /*<<< orphan*/  AL_ETH_KR_PMD_LD_STATUS_REPORT_ZERO_SHIFT ; 
 int /*<<< orphan*/  AL_ETH_LT_REGS ; 
 int /*<<< orphan*/  AL_REG_BIT_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AL_REG_FIELD_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  al_eth_an_lt_reg_write (struct al_hal_eth_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void al_eth_ld_status_report_set(
			struct al_hal_eth_adapter *adapter,
			enum al_eth_an_lt_lane lane,
			struct al_eth_kr_status_report_data *status)
{
	uint16_t reg = 0;

	AL_REG_FIELD_SET(reg,
			 AL_ETH_KR_PMD_LD_STATUS_REPORT_MINUS_MASK,
			 AL_ETH_KR_PMD_LD_STATUS_REPORT_MINUS_SHIFT,
			 status->c_minus);

	AL_REG_FIELD_SET(reg,
			 AL_ETH_KR_PMD_LD_STATUS_REPORT_ZERO_MASK,
			 AL_ETH_KR_PMD_LD_STATUS_REPORT_ZERO_SHIFT,
			 status->c_zero);

	AL_REG_FIELD_SET(reg,
			 AL_ETH_KR_PMD_LD_STATUS_REPORT_PLUS_MASK,
			 AL_ETH_KR_PMD_LD_STATUS_REPORT_PLUS_SHIFT,
			 status->c_plus);

	if (status->receiver_ready)
		AL_REG_BIT_SET(reg,
			AL_ETH_KR_PMD_LD_STATUS_REPORT_RECEIVER_READY_SHIFT);

	al_eth_an_lt_reg_write(adapter, AL_ETH_KR_PMD_LD_STATUS_REPORT, AL_ETH_LT_REGS, lane, reg);
}