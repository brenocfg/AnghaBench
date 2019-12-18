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

/* Variables and functions */
 int /*<<< orphan*/  AL_SRDS_REG_PAGE_4_COMMON ; 
 int /*<<< orphan*/  AL_SRDS_REG_TYPE_PMA ; 
 int /*<<< orphan*/  SERDES_IREG_FLD_TXBIST_BITERROR_EN ; 
 int /*<<< orphan*/  SERDES_IREG_FLD_TXBIST_BITERROR_EN_REG_NUM ; 
 int /*<<< orphan*/  al_serdes_grp_reg_masked_write (struct al_serdes_grp_obj*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void al_serdes_bist_tx_err_inject(
	struct al_serdes_grp_obj	*obj)
{
	al_serdes_grp_reg_masked_write(
		obj,
		AL_SRDS_REG_PAGE_4_COMMON,
		AL_SRDS_REG_TYPE_PMA,
		SERDES_IREG_FLD_TXBIST_BITERROR_EN_REG_NUM,
		SERDES_IREG_FLD_TXBIST_BITERROR_EN,
		SERDES_IREG_FLD_TXBIST_BITERROR_EN);

	al_serdes_grp_reg_masked_write(
		obj,
		AL_SRDS_REG_PAGE_4_COMMON,
		AL_SRDS_REG_TYPE_PMA,
		SERDES_IREG_FLD_TXBIST_BITERROR_EN_REG_NUM,
		SERDES_IREG_FLD_TXBIST_BITERROR_EN,
		0);
}