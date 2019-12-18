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
struct ar8xxx_priv {int chip_rev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ar8xxx_phy_dbg_write (struct ar8xxx_priv*,int,int,int) ; 
 int /*<<< orphan*/  ar8xxx_phy_mmd_write (struct ar8xxx_priv*,int,int,int,int) ; 

__attribute__((used)) static void
ar8327_phy_fixup(struct ar8xxx_priv *priv, int phy)
{
	switch (priv->chip_rev) {
	case 1:
		/* For 100M waveform */
		ar8xxx_phy_dbg_write(priv, phy, 0, 0x02ea);
		/* Turn on Gigabit clock */
		ar8xxx_phy_dbg_write(priv, phy, 0x3d, 0x68a0);
		break;

	case 2:
		ar8xxx_phy_mmd_write(priv, phy, 0x7, 0x3c, 0x0);
		/* fallthrough */
	case 4:
		ar8xxx_phy_mmd_write(priv, phy, 0x3, 0x800d, 0x803f);
		ar8xxx_phy_dbg_write(priv, phy, 0x3d, 0x6860);
		ar8xxx_phy_dbg_write(priv, phy, 0x5, 0x2c46);
		ar8xxx_phy_dbg_write(priv, phy, 0x3c, 0x6000);
		break;
	}
}