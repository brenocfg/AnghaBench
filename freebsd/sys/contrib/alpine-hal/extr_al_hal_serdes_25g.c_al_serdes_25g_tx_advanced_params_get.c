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
struct al_serdes_grp_obj {int dummy; } ;
struct al_serdes_adv_tx_params {int /*<<< orphan*/  total_driver_units; int /*<<< orphan*/  c_plus_1; int /*<<< orphan*/  c_minus_1; } ;
typedef  enum al_serdes_reg_page { ____Placeholder_al_serdes_reg_page } al_serdes_reg_page ;
typedef  enum al_serdes_lane { ____Placeholder_al_serdes_lane } al_serdes_lane ;

/* Variables and functions */
 int /*<<< orphan*/  SERDES_25G_LANE_DRV_TXEQ_CTRL1_ADDR ; 
 int /*<<< orphan*/  SERDES_25G_LANE_DRV_TXEQ_CTRL1_TXEQ_C1_MASK ; 
 int /*<<< orphan*/  SERDES_25G_LANE_DRV_TXEQ_CTRL1_TXEQ_C1_SHIFT ; 
 int /*<<< orphan*/  SERDES_25G_LANE_DRV_TXEQ_CTRL3_ADDR ; 
 int /*<<< orphan*/  SERDES_25G_LANE_DRV_TXEQ_CTRL3_TXEQ_CM1_MASK ; 
 int /*<<< orphan*/  SERDES_25G_LANE_DRV_TXEQ_CTRL3_TXEQ_CM1_SHIFT ; 
 int /*<<< orphan*/  SERDES_25G_LANE_DRV_TXEQ_CTRL5_ADDR ; 
 int /*<<< orphan*/  SERDES_25G_LANE_DRV_TXEQ_CTRL5_DRV_SWING_MASK ; 
 int /*<<< orphan*/  SERDES_25G_LANE_DRV_TXEQ_CTRL5_DRV_SWING_SHIFT ; 
 int /*<<< orphan*/  al_serdes_25g_reg_masked_read (struct al_serdes_grp_obj*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void al_serdes_25g_tx_advanced_params_get(struct al_serdes_grp_obj	*obj,
		enum al_serdes_lane			lane,
		void					*tx_params)
{
	struct al_serdes_adv_tx_params	*params = tx_params;

	al_serdes_25g_reg_masked_read(obj,
					(enum al_serdes_reg_page)lane,
					SERDES_25G_LANE_DRV_TXEQ_CTRL3_ADDR,
					SERDES_25G_LANE_DRV_TXEQ_CTRL3_TXEQ_CM1_MASK,
					SERDES_25G_LANE_DRV_TXEQ_CTRL3_TXEQ_CM1_SHIFT,
					&params->c_minus_1);

	al_serdes_25g_reg_masked_read(obj,
					(enum al_serdes_reg_page)lane,
					SERDES_25G_LANE_DRV_TXEQ_CTRL1_ADDR,
					SERDES_25G_LANE_DRV_TXEQ_CTRL1_TXEQ_C1_MASK,
					SERDES_25G_LANE_DRV_TXEQ_CTRL1_TXEQ_C1_SHIFT,
					&params->c_plus_1);

	al_serdes_25g_reg_masked_read(obj,
					(enum al_serdes_reg_page)lane,
					SERDES_25G_LANE_DRV_TXEQ_CTRL5_ADDR,
					SERDES_25G_LANE_DRV_TXEQ_CTRL5_DRV_SWING_MASK,
					SERDES_25G_LANE_DRV_TXEQ_CTRL5_DRV_SWING_SHIFT,
					&params->total_driver_units);
}