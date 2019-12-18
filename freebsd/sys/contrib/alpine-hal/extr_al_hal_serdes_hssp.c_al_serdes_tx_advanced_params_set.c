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
typedef  scalar_t__ uint8_t ;
struct al_serdes_grp_obj {int dummy; } ;
struct al_serdes_adv_tx_params {int /*<<< orphan*/  slew_rate; int /*<<< orphan*/  c_minus_1; int /*<<< orphan*/  c_plus_2; int /*<<< orphan*/  c_plus_1; int /*<<< orphan*/  total_driver_units; int /*<<< orphan*/  amp; int /*<<< orphan*/  override; } ;
typedef  enum al_serdes_reg_page { ____Placeholder_al_serdes_reg_page } al_serdes_reg_page ;
typedef  enum al_serdes_lane { ____Placeholder_al_serdes_lane } al_serdes_lane ;

/* Variables and functions */
 int /*<<< orphan*/  AL_REG_FIELD_SET (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AL_SRDS_REG_TYPE_PMA ; 
 int /*<<< orphan*/  SERDES_IREG_FLD_TX_DRV_OVERRIDE_EN ; 
 int /*<<< orphan*/  SERDES_IREG_FLD_TX_DRV_OVERRIDE_EN_REG_NUM ; 
 int /*<<< orphan*/  SERDES_IREG_TX_DRV_1_HLEV_MASK ; 
 int /*<<< orphan*/  SERDES_IREG_TX_DRV_1_HLEV_SHIFT ; 
 int /*<<< orphan*/  SERDES_IREG_TX_DRV_1_LEVN_MASK ; 
 int /*<<< orphan*/  SERDES_IREG_TX_DRV_1_LEVN_SHIFT ; 
 int /*<<< orphan*/  SERDES_IREG_TX_DRV_1_REG_NUM ; 
 int /*<<< orphan*/  SERDES_IREG_TX_DRV_2_LEVNM1_MASK ; 
 int /*<<< orphan*/  SERDES_IREG_TX_DRV_2_LEVNM1_SHIFT ; 
 int /*<<< orphan*/  SERDES_IREG_TX_DRV_2_LEVNM2_MASK ; 
 int /*<<< orphan*/  SERDES_IREG_TX_DRV_2_LEVNM2_SHIFT ; 
 int /*<<< orphan*/  SERDES_IREG_TX_DRV_2_REG_NUM ; 
 int /*<<< orphan*/  SERDES_IREG_TX_DRV_3_LEVNP1_MASK ; 
 int /*<<< orphan*/  SERDES_IREG_TX_DRV_3_LEVNP1_SHIFT ; 
 int /*<<< orphan*/  SERDES_IREG_TX_DRV_3_REG_NUM ; 
 int /*<<< orphan*/  SERDES_IREG_TX_DRV_3_SLEW_MASK ; 
 int /*<<< orphan*/  SERDES_IREG_TX_DRV_3_SLEW_SHIFT ; 
 int /*<<< orphan*/  al_serdes_grp_reg_masked_write (struct al_serdes_grp_obj*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  al_serdes_grp_reg_write (struct al_serdes_grp_obj*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void al_serdes_tx_advanced_params_set(struct al_serdes_grp_obj	*obj,
				      enum al_serdes_lane		lane,
				      void				*tx_params)
{
	uint8_t reg = 0;
	struct al_serdes_adv_tx_params	*params = tx_params;

	if (!params->override) {
		al_serdes_grp_reg_masked_write(obj,
			(enum al_serdes_reg_page)lane,
			AL_SRDS_REG_TYPE_PMA,
			SERDES_IREG_FLD_TX_DRV_OVERRIDE_EN_REG_NUM,
			SERDES_IREG_FLD_TX_DRV_OVERRIDE_EN,
			SERDES_IREG_FLD_TX_DRV_OVERRIDE_EN);

		return;
	}

	al_serdes_grp_reg_masked_write(obj,
			(enum al_serdes_reg_page)lane,
			AL_SRDS_REG_TYPE_PMA,
			SERDES_IREG_FLD_TX_DRV_OVERRIDE_EN_REG_NUM,
			SERDES_IREG_FLD_TX_DRV_OVERRIDE_EN,
			0);

	AL_REG_FIELD_SET(reg,
			 SERDES_IREG_TX_DRV_1_HLEV_MASK,
			 SERDES_IREG_TX_DRV_1_HLEV_SHIFT,
			 params->amp);

	AL_REG_FIELD_SET(reg,
			 SERDES_IREG_TX_DRV_1_LEVN_MASK,
			 SERDES_IREG_TX_DRV_1_LEVN_SHIFT,
			 params->total_driver_units);

	al_serdes_grp_reg_write(obj,
				(enum al_serdes_reg_page)lane,
				AL_SRDS_REG_TYPE_PMA,
				SERDES_IREG_TX_DRV_1_REG_NUM,
				reg);

	reg = 0;
	AL_REG_FIELD_SET(reg,
			 SERDES_IREG_TX_DRV_2_LEVNM1_MASK,
			 SERDES_IREG_TX_DRV_2_LEVNM1_SHIFT,
			 params->c_plus_1);

	AL_REG_FIELD_SET(reg,
			 SERDES_IREG_TX_DRV_2_LEVNM2_MASK,
			 SERDES_IREG_TX_DRV_2_LEVNM2_SHIFT,
			 params->c_plus_2);

	al_serdes_grp_reg_write(obj,
				(enum al_serdes_reg_page)lane,
				AL_SRDS_REG_TYPE_PMA,
				SERDES_IREG_TX_DRV_2_REG_NUM,
				reg);

	reg = 0;
	AL_REG_FIELD_SET(reg,
			 SERDES_IREG_TX_DRV_3_LEVNP1_MASK,
			 SERDES_IREG_TX_DRV_3_LEVNP1_SHIFT,
			 params->c_minus_1);

	AL_REG_FIELD_SET(reg,
			 SERDES_IREG_TX_DRV_3_SLEW_MASK,
			 SERDES_IREG_TX_DRV_3_SLEW_SHIFT,
			 params->slew_rate);

	al_serdes_grp_reg_write(obj,
				(enum al_serdes_reg_page)lane,
				AL_SRDS_REG_TYPE_PMA,
				SERDES_IREG_TX_DRV_3_REG_NUM,
				reg);

}