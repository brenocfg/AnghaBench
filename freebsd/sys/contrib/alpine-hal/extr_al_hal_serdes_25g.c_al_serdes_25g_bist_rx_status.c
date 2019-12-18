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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct al_serdes_grp_obj {int dummy; } ;
typedef  enum al_serdes_reg_page { ____Placeholder_al_serdes_reg_page } al_serdes_reg_page ;
typedef  enum al_serdes_lane { ____Placeholder_al_serdes_lane } al_serdes_lane ;
typedef  int /*<<< orphan*/  al_bool ;

/* Variables and functions */
 int /*<<< orphan*/  AL_FALSE ; 
 int /*<<< orphan*/  AL_TRUE ; 
 int /*<<< orphan*/  SERDES_25G_LANE_RX_BIST_BER_STATUS0_ADDR ; 
 int /*<<< orphan*/  SERDES_25G_LANE_RX_BIST_BER_STATUS0_BIT_ERROR_COUNT_7_0_MASK ; 
 int /*<<< orphan*/  SERDES_25G_LANE_RX_BIST_BER_STATUS0_BIT_ERROR_COUNT_7_0_SHIFT ; 
 int /*<<< orphan*/  SERDES_25G_LANE_RX_BIST_BER_STATUS1_ADDR ; 
 int /*<<< orphan*/  SERDES_25G_LANE_RX_BIST_BER_STATUS1_BIT_ERROR_COUNT_15_8_MASK ; 
 int /*<<< orphan*/  SERDES_25G_LANE_RX_BIST_BER_STATUS1_BIT_ERROR_COUNT_15_8_SHIFT ; 
 int /*<<< orphan*/  SERDES_25G_LANE_RX_BIST_BER_STATUS2_ADDR ; 
 int /*<<< orphan*/  SERDES_25G_LANE_RX_BIST_BER_STATUS2_BIT_ERROR_COUNT_23_16_MASK ; 
 int /*<<< orphan*/  SERDES_25G_LANE_RX_BIST_BER_STATUS2_BIT_ERROR_COUNT_23_16_SHIFT ; 
 int /*<<< orphan*/  SERDES_25G_LANE_RX_BIST_STATUS_ADDR ; 
 int /*<<< orphan*/  SERDES_25G_LANE_RX_BIST_STATUS_STATE_MASK ; 
 int /*<<< orphan*/  SERDES_25G_LANE_RX_BIST_STATUS_STATE_SHIFT ; 
 int /*<<< orphan*/  al_serdes_25g_reg_masked_read (struct al_serdes_grp_obj*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void al_serdes_25g_bist_rx_status(
	struct al_serdes_grp_obj	*obj,
	enum al_serdes_lane		lane,
	al_bool				*is_locked,
	al_bool				*err_cnt_overflow,
	uint32_t			*err_cnt)
{
	uint8_t status;
	uint8_t err1;
	uint8_t err2;
	uint8_t err3;

	al_serdes_25g_reg_masked_read(
		obj,
		(enum al_serdes_reg_page)lane,
		SERDES_25G_LANE_RX_BIST_STATUS_ADDR,
		SERDES_25G_LANE_RX_BIST_STATUS_STATE_MASK,
		SERDES_25G_LANE_RX_BIST_STATUS_STATE_SHIFT,
		&status);

	if (status != 3) {
		*is_locked = AL_FALSE;
		return;
	}

	*is_locked = AL_TRUE;
	*err_cnt_overflow = AL_FALSE;

	al_serdes_25g_reg_masked_read(
		obj,
		(enum al_serdes_reg_page)lane,
		SERDES_25G_LANE_RX_BIST_BER_STATUS0_ADDR,
		SERDES_25G_LANE_RX_BIST_BER_STATUS0_BIT_ERROR_COUNT_7_0_MASK,
		SERDES_25G_LANE_RX_BIST_BER_STATUS0_BIT_ERROR_COUNT_7_0_SHIFT,
		&err1);

	al_serdes_25g_reg_masked_read(
		obj,
		(enum al_serdes_reg_page)lane,
		SERDES_25G_LANE_RX_BIST_BER_STATUS1_ADDR,
		SERDES_25G_LANE_RX_BIST_BER_STATUS1_BIT_ERROR_COUNT_15_8_MASK,
		SERDES_25G_LANE_RX_BIST_BER_STATUS1_BIT_ERROR_COUNT_15_8_SHIFT,
		&err2);

	al_serdes_25g_reg_masked_read(
		obj,
		(enum al_serdes_reg_page)lane,
		SERDES_25G_LANE_RX_BIST_BER_STATUS2_ADDR,
		SERDES_25G_LANE_RX_BIST_BER_STATUS2_BIT_ERROR_COUNT_23_16_MASK,
		SERDES_25G_LANE_RX_BIST_BER_STATUS2_BIT_ERROR_COUNT_23_16_SHIFT,
		&err3);

	*err_cnt = (err1 + (err2 << 8) + (err3 << 16));
}