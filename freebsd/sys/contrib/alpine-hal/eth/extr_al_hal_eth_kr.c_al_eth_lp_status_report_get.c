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
struct al_eth_kr_status_report_data {int receiver_ready; void* c_plus; void* c_zero; void* c_minus; } ;
typedef  enum al_eth_an_lt_lane { ____Placeholder_al_eth_an_lt_lane } al_eth_an_lt_lane ;

/* Variables and functions */
 int /*<<< orphan*/  AL_ETH_KR_PMD_LP_STATUS_RECEIVER_READY_SHIFT ; 
 int /*<<< orphan*/  AL_ETH_KR_PMD_LP_STATUS_REPORT ; 
 int /*<<< orphan*/  AL_ETH_KR_PMD_LP_STATUS_REPORT_MINUS_MASK ; 
 int /*<<< orphan*/  AL_ETH_KR_PMD_LP_STATUS_REPORT_MINUS_SHIFT ; 
 int /*<<< orphan*/  AL_ETH_KR_PMD_LP_STATUS_REPORT_PLUS_MASK ; 
 int /*<<< orphan*/  AL_ETH_KR_PMD_LP_STATUS_REPORT_PLUS_SHIFT ; 
 int /*<<< orphan*/  AL_ETH_KR_PMD_LP_STATUS_REPORT_ZERO_MASK ; 
 int /*<<< orphan*/  AL_ETH_KR_PMD_LP_STATUS_REPORT_ZERO_SHIFT ; 
 int /*<<< orphan*/  AL_ETH_LT_REGS ; 
 scalar_t__ AL_REG_BIT_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* AL_REG_FIELD_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  al_eth_an_lt_reg_read (struct al_hal_eth_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void al_eth_lp_status_report_get(
			struct al_hal_eth_adapter *adapter,
			enum al_eth_an_lt_lane lane,
			struct al_eth_kr_status_report_data *status)
{
	uint16_t reg;

	reg = al_eth_an_lt_reg_read(adapter, AL_ETH_KR_PMD_LP_STATUS_REPORT, AL_ETH_LT_REGS, lane);

	status->c_minus = AL_REG_FIELD_GET(reg,
				    AL_ETH_KR_PMD_LP_STATUS_REPORT_MINUS_MASK,
				    AL_ETH_KR_PMD_LP_STATUS_REPORT_MINUS_SHIFT);

	status->c_zero = AL_REG_FIELD_GET(reg,
				   AL_ETH_KR_PMD_LP_STATUS_REPORT_ZERO_MASK,
				   AL_ETH_KR_PMD_LP_STATUS_REPORT_ZERO_SHIFT);

	status->c_plus = AL_REG_FIELD_GET(reg,
				   AL_ETH_KR_PMD_LP_STATUS_REPORT_PLUS_MASK,
				   AL_ETH_KR_PMD_LP_STATUS_REPORT_PLUS_SHIFT);

	status->receiver_ready =
		(AL_REG_BIT_GET(
			reg, AL_ETH_KR_PMD_LP_STATUS_RECEIVER_READY_SHIFT) != 0);

}