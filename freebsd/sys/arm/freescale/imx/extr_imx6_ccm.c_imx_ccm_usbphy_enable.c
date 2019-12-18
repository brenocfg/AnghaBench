#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IMX6_ANALOG_CCM_PLL_USB1 ; 
 int IMX6_ANALOG_CCM_PLL_USB_ENABLE ; 
 int IMX6_ANALOG_CCM_PLL_USB_EN_USB_CLKS ; 
 int IMX6_ANALOG_CCM_PLL_USB_POWER ; 
 TYPE_1__* ccm_sc ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  imx6_anatop_write_4 (scalar_t__,int) ; 

void
imx_ccm_usbphy_enable(device_t _phydev)
{
        /*
         * XXX Which unit?
         * Right now it's not clear how to figure from fdt data which phy unit
         * we're supposed to operate on.  Until this is worked out, just enable
         * both PHYs.
         */
#if 0
	int phy_num, regoff;

	phy_num = 0; /* XXX */

	switch (phy_num) {
	case 0:
		regoff = 0;
		break;
	case 1:
		regoff = 0x10;
		break;
	default:
		device_printf(ccm_sc->dev, "Bad PHY number %u,\n", 
		    phy_num);
		return;
	}

	imx6_anatop_write_4(IMX6_ANALOG_CCM_PLL_USB1 + regoff, 
	    IMX6_ANALOG_CCM_PLL_USB_ENABLE | 
	    IMX6_ANALOG_CCM_PLL_USB_POWER |
	    IMX6_ANALOG_CCM_PLL_USB_EN_USB_CLKS);
#else
	imx6_anatop_write_4(IMX6_ANALOG_CCM_PLL_USB1 + 0,
	    IMX6_ANALOG_CCM_PLL_USB_ENABLE | 
	    IMX6_ANALOG_CCM_PLL_USB_POWER |
	    IMX6_ANALOG_CCM_PLL_USB_EN_USB_CLKS);

	imx6_anatop_write_4(IMX6_ANALOG_CCM_PLL_USB1 + 0x10, 
	    IMX6_ANALOG_CCM_PLL_USB_ENABLE | 
	    IMX6_ANALOG_CCM_PLL_USB_POWER |
	    IMX6_ANALOG_CCM_PLL_USB_EN_USB_CLKS);
#endif
}