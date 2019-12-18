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
struct switch_dev {int dummy; } ;
struct rtl_phyregs {int dummy; } ;

/* Variables and functions */
 int RTL8306_NUM_PORTS ; 
 int /*<<< orphan*/  RTL_REG_CPU_LINKUP ; 
 int /*<<< orphan*/  RTL_REG_EN_TRUNK ; 
 int /*<<< orphan*/  RTL_REG_RESET ; 
 int /*<<< orphan*/  RTL_REG_TRUNK_PORTSEL ; 
 int /*<<< orphan*/  msleep (int) ; 
 int rtl_get (struct switch_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_phy_restore (struct switch_dev*,int,struct rtl_phyregs*) ; 
 int /*<<< orphan*/  rtl_phy_save (struct switch_dev*,int,struct rtl_phyregs*) ; 
 int /*<<< orphan*/  rtl_port_set_enable (struct switch_dev*,int,int) ; 
 int /*<<< orphan*/  rtl_set (struct switch_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
rtl_hw_apply(struct switch_dev *dev)
{
	int i;
	int trunk_en, trunk_psel;
	struct rtl_phyregs port5;

	rtl_phy_save(dev, 5, &port5);

	/* disable rx/tx from PHYs */
	for (i = 0; i < RTL8306_NUM_PORTS - 1; i++) {
		rtl_port_set_enable(dev, i, 0);
	}

	/* save trunking status */
	trunk_en = rtl_get(dev, RTL_REG_EN_TRUNK);
	trunk_psel = rtl_get(dev, RTL_REG_TRUNK_PORTSEL);

	/* trunk port 3 and 4
	 * XXX: Big WTF, but RealTek seems to do it */
	rtl_set(dev, RTL_REG_EN_TRUNK, 1);
	rtl_set(dev, RTL_REG_TRUNK_PORTSEL, 1);

	/* execute the software reset */
	rtl_set(dev, RTL_REG_RESET, 1);

	/* wait for the reset to complete,
	 * but don't wait for too long */
	for (i = 0; i < 10; i++) {
		if (rtl_get(dev, RTL_REG_RESET) == 0)
			break;

		msleep(1);
	}

	/* enable rx/tx from PHYs */
	for (i = 0; i < RTL8306_NUM_PORTS - 1; i++) {
		rtl_port_set_enable(dev, i, 1);
	}

	/* restore trunking settings */
	rtl_set(dev, RTL_REG_EN_TRUNK, trunk_en);
	rtl_set(dev, RTL_REG_TRUNK_PORTSEL, trunk_psel);
	rtl_phy_restore(dev, 5, &port5);

	rtl_set(dev, RTL_REG_CPU_LINKUP, 1);

	return 0;
}