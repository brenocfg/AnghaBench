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
struct rtl8366_smi {int /*<<< orphan*/  parent; } ;
typedef  enum rtl8367_extif_mode { ____Placeholder_rtl8367_extif_mode } rtl8367_extif_mode ;

/* Variables and functions */
 int BIT (int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  REG_RMW (struct rtl8366_smi*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  REG_WR (struct rtl8366_smi*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RTL8367B_BYPASS_LINE_RATE_REG ; 
 int RTL8367B_CHIP_DEBUG0_DUMMY0 (int) ; 
 int /*<<< orphan*/  RTL8367B_CHIP_DEBUG0_REG ; 
 int /*<<< orphan*/  RTL8367B_CHIP_DEBUG1_REG ; 
 int /*<<< orphan*/  RTL8367B_DIS_REG ; 
 int RTL8367B_DIS_RGMII_MASK ; 
 int RTL8367B_DIS_RGMII_SHIFT (int) ; 
 int /*<<< orphan*/  RTL8367B_EXT_RGMXF_REG (int) ; 
#define  RTL8367_EXTIF_MODE_DISABLED 135 
#define  RTL8367_EXTIF_MODE_GMII 134 
#define  RTL8367_EXTIF_MODE_MII_MAC 133 
#define  RTL8367_EXTIF_MODE_MII_PHY 132 
#define  RTL8367_EXTIF_MODE_RGMII 131 
#define  RTL8367_EXTIF_MODE_RGMII_33V 130 
#define  RTL8367_EXTIF_MODE_TMII_MAC 129 
#define  RTL8367_EXTIF_MODE_TMII_PHY 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int rtl8367b_extif_set_mode(struct rtl8366_smi *smi, int id,
				   enum rtl8367_extif_mode mode)
{
	int err;

	/* set port mode */
	switch (mode) {
	case RTL8367_EXTIF_MODE_RGMII:
	case RTL8367_EXTIF_MODE_RGMII_33V:
		REG_WR(smi, RTL8367B_CHIP_DEBUG0_REG, 0x0367);
		REG_WR(smi, RTL8367B_CHIP_DEBUG1_REG, 0x7777);
		break;

	case RTL8367_EXTIF_MODE_TMII_MAC:
	case RTL8367_EXTIF_MODE_TMII_PHY:
		REG_RMW(smi, RTL8367B_BYPASS_LINE_RATE_REG,
			BIT((id + 1) % 2), BIT((id + 1) % 2));
		break;

	case RTL8367_EXTIF_MODE_GMII:
		REG_RMW(smi, RTL8367B_CHIP_DEBUG0_REG,
		        RTL8367B_CHIP_DEBUG0_DUMMY0(id),
			RTL8367B_CHIP_DEBUG0_DUMMY0(id));
		REG_RMW(smi, RTL8367B_EXT_RGMXF_REG(id), BIT(6), BIT(6));
		break;

	case RTL8367_EXTIF_MODE_MII_MAC:
	case RTL8367_EXTIF_MODE_MII_PHY:
	case RTL8367_EXTIF_MODE_DISABLED:
		REG_RMW(smi, RTL8367B_BYPASS_LINE_RATE_REG,
			BIT((id + 1) % 2), 0);
		REG_RMW(smi, RTL8367B_EXT_RGMXF_REG(id), BIT(6), 0);
		break;

	default:
		dev_err(smi->parent,
			"invalid mode for external interface %d\n", id);
		return -EINVAL;
	}

	REG_RMW(smi, RTL8367B_DIS_REG,
		RTL8367B_DIS_RGMII_MASK << RTL8367B_DIS_RGMII_SHIFT(id),
		mode << RTL8367B_DIS_RGMII_SHIFT(id));

	return 0;
}