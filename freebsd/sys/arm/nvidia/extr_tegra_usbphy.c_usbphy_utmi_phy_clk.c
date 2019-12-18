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
typedef  int /*<<< orphan*/  uint32_t ;
struct usbphy_softc {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL_USB_HOSTPC1_DEVLC ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  IF_USB_SUSP_CTRL ; 
 int /*<<< orphan*/  RD4 (struct usbphy_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_HOSTPC1_DEVLC_PHCD ; 
 int /*<<< orphan*/  USB_PHY_CLK_VALID ; 
 int /*<<< orphan*/  WR4 (struct usbphy_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int reg_wait (struct usbphy_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
usbphy_utmi_phy_clk(struct usbphy_softc *sc, bool enable)
{
	uint32_t val;
	int rv;

	val = RD4(sc, CTRL_USB_HOSTPC1_DEVLC);
	if (enable)
		val &= ~USB_HOSTPC1_DEVLC_PHCD;
	else
		val |= USB_HOSTPC1_DEVLC_PHCD;
	WR4(sc, CTRL_USB_HOSTPC1_DEVLC, val);

	rv = reg_wait(sc, IF_USB_SUSP_CTRL, USB_PHY_CLK_VALID,
	    enable ? USB_PHY_CLK_VALID: 0);
	if (rv != 0) {
		device_printf(sc->dev, "USB phy clock timeout.\n");
		return (ETIMEDOUT);
	}
	return (0);
}