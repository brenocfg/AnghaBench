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
struct al_serdes_sris_params {int ppm_drift_count; int ppm_drift_max; int synth_ppm_drift_max; int full_d2r1; int full_pcie_g3; int rd_threshold_d2r1; int rd_threshold_pcie_g3; } ;
struct al_serdes_grp_obj {int dummy; } ;

/* Variables and functions */
 int AL_FIELD_MASK (int,int) ; 
 int /*<<< orphan*/  AL_SRDS_REG_PAGE_4_COMMON ; 
 int /*<<< orphan*/  AL_SRDS_REG_TYPE_PCS ; 
 int /*<<< orphan*/  AL_SRDS_REG_TYPE_PMA ; 
 int /*<<< orphan*/  SERDES_IREG_FLD_PCS_EBUF_FULL_D2R1_REG_MASK ; 
 int /*<<< orphan*/  SERDES_IREG_FLD_PCS_EBUF_FULL_D2R1_REG_NUM ; 
 int SERDES_IREG_FLD_PCS_EBUF_FULL_D2R1_REG_SHIFT ; 
 int /*<<< orphan*/  SERDES_IREG_FLD_PCS_EBUF_FULL_PCIE_G3_REG_MASK ; 
 int /*<<< orphan*/  SERDES_IREG_FLD_PCS_EBUF_FULL_PCIE_G3_REG_NUM ; 
 int SERDES_IREG_FLD_PCS_EBUF_FULL_PCIE_G3_REG_SHIFT ; 
 int /*<<< orphan*/  SERDES_IREG_FLD_PCS_EBUF_RD_THRESHOLD_D2R1_REG_MASK ; 
 int /*<<< orphan*/  SERDES_IREG_FLD_PCS_EBUF_RD_THRESHOLD_D2R1_REG_NUM ; 
 int SERDES_IREG_FLD_PCS_EBUF_RD_THRESHOLD_D2R1_REG_SHIFT ; 
 int /*<<< orphan*/  SERDES_IREG_FLD_PCS_EBUF_RD_THRESHOLD_PCIE_G3_REG_MASK ; 
 int /*<<< orphan*/  SERDES_IREG_FLD_PCS_EBUF_RD_THRESHOLD_PCIE_G3_REG_NUM ; 
 int SERDES_IREG_FLD_PCS_EBUF_RD_THRESHOLD_PCIE_G3_REG_SHIFT ; 
 int /*<<< orphan*/  SERDES_IREG_FLD_PPMDRIFTCOUNT1_REG_NUM ; 
 int /*<<< orphan*/  SERDES_IREG_FLD_PPMDRIFTCOUNT2_REG_NUM ; 
 int /*<<< orphan*/  SERDES_IREG_FLD_PPMDRIFTMAX1_REG_NUM ; 
 int /*<<< orphan*/  SERDES_IREG_FLD_PPMDRIFTMAX2_REG_NUM ; 
 int /*<<< orphan*/  SERDES_IREG_FLD_SYNTHPPMDRIFTMAX1_REG_NUM ; 
 int /*<<< orphan*/  SERDES_IREG_FLD_SYNTHPPMDRIFTMAX2_REG_NUM ; 
 int /*<<< orphan*/  al_serdes_grp_reg_masked_write (struct al_serdes_grp_obj*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  al_serdes_reg_write (struct al_serdes_grp_obj*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void al_serdes_sris_config(
	struct al_serdes_grp_obj	*obj,
	void				*sris_params)
{
	struct al_serdes_sris_params	*params = sris_params;

	al_serdes_reg_write(obj, AL_SRDS_REG_PAGE_4_COMMON, AL_SRDS_REG_TYPE_PMA,
		SERDES_IREG_FLD_PPMDRIFTCOUNT1_REG_NUM,
		(params->ppm_drift_count & AL_FIELD_MASK(7, 0)) >> 0);
	al_serdes_reg_write(obj, AL_SRDS_REG_PAGE_4_COMMON, AL_SRDS_REG_TYPE_PMA,
		SERDES_IREG_FLD_PPMDRIFTCOUNT2_REG_NUM,
		(params->ppm_drift_count & AL_FIELD_MASK(15, 8)) >> 8);

	al_serdes_reg_write(obj, AL_SRDS_REG_PAGE_4_COMMON, AL_SRDS_REG_TYPE_PMA,
		SERDES_IREG_FLD_PPMDRIFTMAX1_REG_NUM,
		(params->ppm_drift_max & AL_FIELD_MASK(7, 0)) >> 0);
	al_serdes_reg_write(obj, AL_SRDS_REG_PAGE_4_COMMON, AL_SRDS_REG_TYPE_PMA,
		SERDES_IREG_FLD_PPMDRIFTMAX2_REG_NUM,
		(params->ppm_drift_max & AL_FIELD_MASK(15, 8)) >> 8);

	al_serdes_reg_write(obj, AL_SRDS_REG_PAGE_4_COMMON, AL_SRDS_REG_TYPE_PMA,
		SERDES_IREG_FLD_SYNTHPPMDRIFTMAX1_REG_NUM,
		(params->synth_ppm_drift_max & AL_FIELD_MASK(7, 0)) >> 0);
	al_serdes_reg_write(obj, AL_SRDS_REG_PAGE_4_COMMON, AL_SRDS_REG_TYPE_PMA,
		SERDES_IREG_FLD_SYNTHPPMDRIFTMAX2_REG_NUM,
		(params->synth_ppm_drift_max & AL_FIELD_MASK(15, 8)) >> 8);

	al_serdes_grp_reg_masked_write(obj, AL_SRDS_REG_PAGE_4_COMMON, AL_SRDS_REG_TYPE_PCS,
		SERDES_IREG_FLD_PCS_EBUF_FULL_D2R1_REG_NUM,
		SERDES_IREG_FLD_PCS_EBUF_FULL_D2R1_REG_MASK,
		(params->full_d2r1)
			<< SERDES_IREG_FLD_PCS_EBUF_FULL_D2R1_REG_SHIFT);

	al_serdes_grp_reg_masked_write(obj, AL_SRDS_REG_PAGE_4_COMMON, AL_SRDS_REG_TYPE_PCS,
		SERDES_IREG_FLD_PCS_EBUF_FULL_PCIE_G3_REG_NUM,
		SERDES_IREG_FLD_PCS_EBUF_FULL_PCIE_G3_REG_MASK,
		(params->full_pcie_g3)
			<< SERDES_IREG_FLD_PCS_EBUF_FULL_PCIE_G3_REG_SHIFT);

	al_serdes_grp_reg_masked_write(obj, AL_SRDS_REG_PAGE_4_COMMON, AL_SRDS_REG_TYPE_PCS,
		SERDES_IREG_FLD_PCS_EBUF_RD_THRESHOLD_D2R1_REG_NUM,
		SERDES_IREG_FLD_PCS_EBUF_RD_THRESHOLD_D2R1_REG_MASK,
		(params->rd_threshold_d2r1)
			<< SERDES_IREG_FLD_PCS_EBUF_RD_THRESHOLD_D2R1_REG_SHIFT);

	al_serdes_grp_reg_masked_write(obj, AL_SRDS_REG_PAGE_4_COMMON, AL_SRDS_REG_TYPE_PCS,
		SERDES_IREG_FLD_PCS_EBUF_RD_THRESHOLD_PCIE_G3_REG_NUM,
		SERDES_IREG_FLD_PCS_EBUF_RD_THRESHOLD_PCIE_G3_REG_MASK,
		(params->rd_threshold_pcie_g3)
			<< SERDES_IREG_FLD_PCS_EBUF_RD_THRESHOLD_PCIE_G3_REG_SHIFT);
}