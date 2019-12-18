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
struct gsw_mt753x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CORE_PLL_GROUP10 ; 
 int /*<<< orphan*/  CORE_PLL_GROUP11 ; 
 int /*<<< orphan*/  CORE_PLL_GROUP5 ; 
 int /*<<< orphan*/  CORE_PLL_GROUP6 ; 
 int /*<<< orphan*/  TRGMII_TCK_CTRL ; 
 int /*<<< orphan*/  TRGMII_TXCTRL ; 
 int TXC_INV ; 
 int TX_TAP_S ; 
 int TX_TRAIN_WD_S ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  mt7530_core_reg_write (struct gsw_mt753x*,int /*<<< orphan*/ ,int) ; 
 int mt753x_reg_read (struct gsw_mt753x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt753x_reg_write (struct gsw_mt753x*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mt7530_rgmii_setting(struct gsw_mt753x *gsw)
{
	u32 val;

	mt7530_core_reg_write(gsw, CORE_PLL_GROUP5, 0x0c80);
	mdelay(1);
	mt7530_core_reg_write(gsw, CORE_PLL_GROUP6, 0);
	mt7530_core_reg_write(gsw, CORE_PLL_GROUP10, 0x87);
	mdelay(1);
	mt7530_core_reg_write(gsw, CORE_PLL_GROUP11, 0x87);

	val = mt753x_reg_read(gsw, TRGMII_TXCTRL);
	val &= ~TXC_INV;
	mt753x_reg_write(gsw, TRGMII_TXCTRL, val);

	mt753x_reg_write(gsw, TRGMII_TCK_CTRL,
			 (8 << TX_TAP_S) | (0x55 << TX_TRAIN_WD_S));
}