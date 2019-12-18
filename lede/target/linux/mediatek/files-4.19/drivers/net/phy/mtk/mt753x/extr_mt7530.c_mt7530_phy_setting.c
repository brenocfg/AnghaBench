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
typedef  int u32 ;
struct gsw_mt753x {int (* mii_read ) (struct gsw_mt753x*,int,int) ;int /*<<< orphan*/  (* mmd_write ) (struct gsw_mt753x*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* mii_write ) (struct gsw_mt753x*,int,int,int) ;} ;

/* Variables and functions */
 int MT753X_NUM_PHYS ; 
 int /*<<< orphan*/  PHY_DEV07 ; 
 int /*<<< orphan*/  PHY_DEV07_REG_03C ; 
 int /*<<< orphan*/  PHY_DEV1E ; 
 int /*<<< orphan*/  PHY_DEV1E_REG_123 ; 
 int /*<<< orphan*/  PHY_DEV1E_REG_A6 ; 
 int PHY_EN_DOWN_SHFIT ; 
 int PHY_EXT_REG_14 ; 
 int PHY_LPI_REG_11 ; 
 int PHY_TR_REG_10 ; 
 int PHY_TR_REG_12 ; 
 int /*<<< orphan*/  stub1 (struct gsw_mt753x*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub10 (struct gsw_mt753x*,int,int,int) ; 
 int /*<<< orphan*/  stub11 (struct gsw_mt753x*,int,int,int) ; 
 int /*<<< orphan*/  stub12 (struct gsw_mt753x*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub13 (struct gsw_mt753x*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct gsw_mt753x*,int,int,int) ; 
 int stub3 (struct gsw_mt753x*,int,int) ; 
 int /*<<< orphan*/  stub4 (struct gsw_mt753x*,int,int,int) ; 
 int /*<<< orphan*/  stub5 (struct gsw_mt753x*,int,int,int) ; 
 int /*<<< orphan*/  stub6 (struct gsw_mt753x*,int,int,int) ; 
 int /*<<< orphan*/  stub7 (struct gsw_mt753x*,int,int,int) ; 
 int /*<<< orphan*/  stub8 (struct gsw_mt753x*,int,int,int) ; 
 int /*<<< orphan*/  stub9 (struct gsw_mt753x*,int,int,int) ; 

__attribute__((used)) static void mt7530_phy_setting(struct gsw_mt753x *gsw)
{
	int i;
	u32 val;

	for (i = 0; i < MT753X_NUM_PHYS; i++) {
		/* Disable EEE */
		gsw->mmd_write(gsw, i, PHY_DEV07, PHY_DEV07_REG_03C, 0);

		/* Enable HW auto downshift */
		gsw->mii_write(gsw, i, 0x1f, 0x1);
		val = gsw->mii_read(gsw, i, PHY_EXT_REG_14);
		val |= PHY_EN_DOWN_SHFIT;
		gsw->mii_write(gsw, i, PHY_EXT_REG_14, val);

		/* Increase SlvDPSready time */
		gsw->mii_write(gsw, i, 0x1f, 0x52b5);
		gsw->mii_write(gsw, i, PHY_TR_REG_10, 0xafae);
		gsw->mii_write(gsw, i, PHY_TR_REG_12, 0x2f);
		gsw->mii_write(gsw, i, PHY_TR_REG_10, 0x8fae);

		/* Increase post_update_timer */
		gsw->mii_write(gsw, i, 0x1f, 0x3);
		gsw->mii_write(gsw, i, PHY_LPI_REG_11, 0x4b);
		gsw->mii_write(gsw, i, 0x1f, 0);

		/* Adjust 100_mse_threshold */
		gsw->mmd_write(gsw, i, PHY_DEV1E, PHY_DEV1E_REG_123, 0xffff);

		/* Disable mcc */
		gsw->mmd_write(gsw, i, PHY_DEV1E, PHY_DEV1E_REG_A6, 0x300);
	}
}