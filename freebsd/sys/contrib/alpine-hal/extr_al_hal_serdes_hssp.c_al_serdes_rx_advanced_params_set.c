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
struct al_serdes_adv_rx_params {int /*<<< orphan*/  high_freq_agc_boost; int /*<<< orphan*/  precal_code_sel; int /*<<< orphan*/  low_freq_agc_gain; int /*<<< orphan*/  dfe_fourth_tap_ctrl; int /*<<< orphan*/  dfe_third_tap_ctrl; int /*<<< orphan*/  dfe_secound_tap_ctrl; int /*<<< orphan*/  dfe_first_tap_ctrl; int /*<<< orphan*/  dfe_gain; int /*<<< orphan*/  dfe_3db_freq; int /*<<< orphan*/  dcgain; int /*<<< orphan*/  override; } ;
typedef  enum al_serdes_reg_page { ____Placeholder_al_serdes_reg_page } al_serdes_reg_page ;
typedef  enum al_serdes_lane { ____Placeholder_al_serdes_lane } al_serdes_lane ;

/* Variables and functions */
 int /*<<< orphan*/  AL_REG_FIELD_SET (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AL_SRDS_REG_TYPE_PMA ; 
 int /*<<< orphan*/  SERDES_IREG_FLD_RX_DRV_OVERRIDE_EN ; 
 int /*<<< orphan*/  SERDES_IREG_FLD_RX_DRV_OVERRIDE_EN_REG_NUM ; 
 int /*<<< orphan*/  SERDES_IREG_RX_CALEQ_1_DCGAIN_MASK ; 
 int /*<<< orphan*/  SERDES_IREG_RX_CALEQ_1_DCGAIN_SHIFT ; 
 int /*<<< orphan*/  SERDES_IREG_RX_CALEQ_1_DFEPSTAP3DB_MASK ; 
 int /*<<< orphan*/  SERDES_IREG_RX_CALEQ_1_DFEPSTAP3DB_SHIFT ; 
 int /*<<< orphan*/  SERDES_IREG_RX_CALEQ_1_REG_NUM ; 
 int /*<<< orphan*/  SERDES_IREG_RX_CALEQ_2_DFEPSTAPGAIN_MASK ; 
 int /*<<< orphan*/  SERDES_IREG_RX_CALEQ_2_DFEPSTAPGAIN_SHIFT ; 
 int /*<<< orphan*/  SERDES_IREG_RX_CALEQ_2_DFETAP1GAIN_MASK ; 
 int /*<<< orphan*/  SERDES_IREG_RX_CALEQ_2_DFETAP1GAIN_SHIFT ; 
 int /*<<< orphan*/  SERDES_IREG_RX_CALEQ_2_REG_NUM ; 
 int /*<<< orphan*/  SERDES_IREG_RX_CALEQ_3_DFETAP2GAIN_MASK ; 
 int /*<<< orphan*/  SERDES_IREG_RX_CALEQ_3_DFETAP2GAIN_SHIFT ; 
 int /*<<< orphan*/  SERDES_IREG_RX_CALEQ_3_DFETAP3GAIN_MASK ; 
 int /*<<< orphan*/  SERDES_IREG_RX_CALEQ_3_DFETAP3GAIN_SHIFT ; 
 int /*<<< orphan*/  SERDES_IREG_RX_CALEQ_3_REG_NUM ; 
 int /*<<< orphan*/  SERDES_IREG_RX_CALEQ_4_DFETAP4GAIN_MASK ; 
 int /*<<< orphan*/  SERDES_IREG_RX_CALEQ_4_DFETAP4GAIN_SHIFT ; 
 int /*<<< orphan*/  SERDES_IREG_RX_CALEQ_4_LOFREQAGCGAIN_MASK ; 
 int /*<<< orphan*/  SERDES_IREG_RX_CALEQ_4_LOFREQAGCGAIN_SHIFT ; 
 int /*<<< orphan*/  SERDES_IREG_RX_CALEQ_4_REG_NUM ; 
 int /*<<< orphan*/  SERDES_IREG_RX_CALEQ_5_HIFREQAGCCAP_MASK ; 
 int /*<<< orphan*/  SERDES_IREG_RX_CALEQ_5_HIFREQAGCCAP_SHIFT ; 
 int /*<<< orphan*/  SERDES_IREG_RX_CALEQ_5_PRECAL_CODE_SEL_MASK ; 
 int /*<<< orphan*/  SERDES_IREG_RX_CALEQ_5_PRECAL_CODE_SEL_SHIFT ; 
 int /*<<< orphan*/  SERDES_IREG_RX_CALEQ_5_REG_NUM ; 
 int /*<<< orphan*/  al_serdes_grp_reg_masked_write (struct al_serdes_grp_obj*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  al_serdes_grp_reg_write (struct al_serdes_grp_obj*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void al_serdes_rx_advanced_params_set(struct al_serdes_grp_obj	*obj,
				      enum al_serdes_lane		lane,
				      void				*rx_params)
{
	struct al_serdes_adv_rx_params	*params = rx_params;
	uint8_t reg = 0;

	if (!params->override) {
		al_serdes_grp_reg_masked_write(obj,
			(enum al_serdes_reg_page)lane,
			AL_SRDS_REG_TYPE_PMA,
			SERDES_IREG_FLD_RX_DRV_OVERRIDE_EN_REG_NUM,
			SERDES_IREG_FLD_RX_DRV_OVERRIDE_EN,
			SERDES_IREG_FLD_RX_DRV_OVERRIDE_EN);

		return;
	}

	al_serdes_grp_reg_masked_write(obj,
			(enum al_serdes_reg_page)lane,
			AL_SRDS_REG_TYPE_PMA,
			SERDES_IREG_FLD_RX_DRV_OVERRIDE_EN_REG_NUM,
			SERDES_IREG_FLD_RX_DRV_OVERRIDE_EN,
			0);

	AL_REG_FIELD_SET(reg,
			 SERDES_IREG_RX_CALEQ_1_DCGAIN_MASK,
			 SERDES_IREG_RX_CALEQ_1_DCGAIN_SHIFT,
			 params->dcgain);

	AL_REG_FIELD_SET(reg,
			 SERDES_IREG_RX_CALEQ_1_DFEPSTAP3DB_MASK,
			 SERDES_IREG_RX_CALEQ_1_DFEPSTAP3DB_SHIFT,
			 params->dfe_3db_freq);

	al_serdes_grp_reg_write(obj,
				(enum al_serdes_reg_page)lane,
				AL_SRDS_REG_TYPE_PMA,
				SERDES_IREG_RX_CALEQ_1_REG_NUM,
				reg);

	reg = 0;
	AL_REG_FIELD_SET(reg,
			 SERDES_IREG_RX_CALEQ_2_DFEPSTAPGAIN_MASK,
			 SERDES_IREG_RX_CALEQ_2_DFEPSTAPGAIN_SHIFT,
			 params->dfe_gain);

	AL_REG_FIELD_SET(reg,
			 SERDES_IREG_RX_CALEQ_2_DFETAP1GAIN_MASK,
			 SERDES_IREG_RX_CALEQ_2_DFETAP1GAIN_SHIFT,
			 params->dfe_first_tap_ctrl);

	al_serdes_grp_reg_write(obj,
				(enum al_serdes_reg_page)lane,
				AL_SRDS_REG_TYPE_PMA,
				SERDES_IREG_RX_CALEQ_2_REG_NUM,
				reg);

	reg = 0;
	AL_REG_FIELD_SET(reg,
			 SERDES_IREG_RX_CALEQ_3_DFETAP2GAIN_MASK,
			 SERDES_IREG_RX_CALEQ_3_DFETAP2GAIN_SHIFT,
			 params->dfe_secound_tap_ctrl);

	AL_REG_FIELD_SET(reg,
			 SERDES_IREG_RX_CALEQ_3_DFETAP3GAIN_MASK,
			 SERDES_IREG_RX_CALEQ_3_DFETAP3GAIN_SHIFT,
			 params->dfe_third_tap_ctrl);

	al_serdes_grp_reg_write(obj,
				(enum al_serdes_reg_page)lane,
				AL_SRDS_REG_TYPE_PMA,
				SERDES_IREG_RX_CALEQ_3_REG_NUM,
				reg);

	reg = 0;
	AL_REG_FIELD_SET(reg,
			 SERDES_IREG_RX_CALEQ_4_DFETAP4GAIN_MASK,
			 SERDES_IREG_RX_CALEQ_4_DFETAP4GAIN_SHIFT,
			 params->dfe_fourth_tap_ctrl);

	AL_REG_FIELD_SET(reg,
			 SERDES_IREG_RX_CALEQ_4_LOFREQAGCGAIN_MASK,
			 SERDES_IREG_RX_CALEQ_4_LOFREQAGCGAIN_SHIFT,
			 params->low_freq_agc_gain);

	al_serdes_grp_reg_write(obj,
				(enum al_serdes_reg_page)lane,
				AL_SRDS_REG_TYPE_PMA,
				SERDES_IREG_RX_CALEQ_4_REG_NUM,
				reg);

	reg = 0;
	AL_REG_FIELD_SET(reg,
			 SERDES_IREG_RX_CALEQ_5_PRECAL_CODE_SEL_MASK,
			 SERDES_IREG_RX_CALEQ_5_PRECAL_CODE_SEL_SHIFT,
			 params->precal_code_sel);

	AL_REG_FIELD_SET(reg,
			 SERDES_IREG_RX_CALEQ_5_HIFREQAGCCAP_MASK,
			 SERDES_IREG_RX_CALEQ_5_HIFREQAGCCAP_SHIFT,
			 params->high_freq_agc_boost);

	al_serdes_grp_reg_write(obj,
				(enum al_serdes_reg_page)lane,
				AL_SRDS_REG_TYPE_PMA,
				SERDES_IREG_RX_CALEQ_5_REG_NUM,
				reg);
}