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
typedef  scalar_t__ al_bool ;

/* Variables and functions */
 int /*<<< orphan*/  AL_SRDS_REG_PAGE_4_COMMON ; 
 int /*<<< orphan*/  AL_SRDS_REG_TYPE_PMA ; 
 int /*<<< orphan*/  SERDES_IREG_FLD_CMNCTLPOR_HARDRSTBYPASSEN_SYNTH_MASK ; 
 int /*<<< orphan*/  SERDES_IREG_FLD_CMNCTLPOR_HARDRSTBYPASSEN_SYNTH_REG_NUM ; 
 int /*<<< orphan*/  SERDES_IREG_FLD_CMNCTLPOR_HARDRSTBYPASSEN_SYNTH_VAL_REGS ; 
 int /*<<< orphan*/  SERDES_IREG_FLD_CMNCTLPOR_HARDRSTBYPASS_SYNTH_MASK ; 
 int /*<<< orphan*/  SERDES_IREG_FLD_CMNCTLPOR_HARDRSTBYPASS_SYNTH_REG_NUM ; 
 int /*<<< orphan*/  SERDES_IREG_FLD_CMNCTLPOR_HARDRSTBYPASS_SYNTH_VAL_ASSERT ; 
 int /*<<< orphan*/  SERDES_IREG_FLD_CMNCTLPOR_HARDRSTBYPASS_SYNTH_VAL_DEASSERT ; 
 int /*<<< orphan*/  al_serdes_group_rx_rate_change_sw_flow_dis (struct al_serdes_grp_obj*) ; 
 int /*<<< orphan*/  al_serdes_group_rx_rate_change_sw_flow_en_cond (struct al_serdes_grp_obj*) ; 
 int /*<<< orphan*/  al_serdes_grp_reg_masked_write (struct al_serdes_grp_obj*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void al_serdes_pma_hard_reset_group(
	struct al_serdes_grp_obj	*obj,
	al_bool				enable)
{
	if (enable)
		al_serdes_group_rx_rate_change_sw_flow_dis(obj);

	/* Enable Hard Reset Override */
	al_serdes_grp_reg_masked_write(
		obj,
		AL_SRDS_REG_PAGE_4_COMMON,
		AL_SRDS_REG_TYPE_PMA,
		SERDES_IREG_FLD_CMNCTLPOR_HARDRSTBYPASSEN_SYNTH_REG_NUM,
		SERDES_IREG_FLD_CMNCTLPOR_HARDRSTBYPASSEN_SYNTH_MASK,
		SERDES_IREG_FLD_CMNCTLPOR_HARDRSTBYPASSEN_SYNTH_VAL_REGS);

	/* Assert/Deassert Hard Reset Override */
	al_serdes_grp_reg_masked_write(
		obj,
		AL_SRDS_REG_PAGE_4_COMMON,
		AL_SRDS_REG_TYPE_PMA,
		SERDES_IREG_FLD_CMNCTLPOR_HARDRSTBYPASS_SYNTH_REG_NUM,
		SERDES_IREG_FLD_CMNCTLPOR_HARDRSTBYPASS_SYNTH_MASK,
		enable ?
		SERDES_IREG_FLD_CMNCTLPOR_HARDRSTBYPASS_SYNTH_VAL_ASSERT :
		SERDES_IREG_FLD_CMNCTLPOR_HARDRSTBYPASS_SYNTH_VAL_DEASSERT);

	if (!enable)
		al_serdes_group_rx_rate_change_sw_flow_en_cond(obj);
}