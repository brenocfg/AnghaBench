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
struct vybrid_ehci_softc {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int ENUTMILEVEL2 ; 
 int ENUTMILEVEL3 ; 
 int /*<<< orphan*/  GPIO_PIN_HIGH ; 
 int /*<<< orphan*/  GPIO_PIN_OUTPUT ; 
 int /*<<< orphan*/  GPIO_PIN_SET (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPIO_PIN_SETFLAGS (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPIO_USB_PWR ; 
 int PHY_READ4 (struct vybrid_ehci_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHY_WRITE4 (struct vybrid_ehci_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  USBPHY_CTRL ; 
 int USBPHY_CTRL_CLKGATE ; 
 int /*<<< orphan*/  USBPHY_CTRL_SET ; 
 int USBPHY_CTRL_SFTRST ; 
 int /*<<< orphan*/  USBPHY_DEBUG ; 
 int /*<<< orphan*/  USBPHY_DEBUG0_STATUS ; 
 int /*<<< orphan*/  USBPHY_DEBUG1 ; 
 int USBPHY_DEBUG_CLKGATE ; 
 int /*<<< orphan*/  USBPHY_IP ; 
 int /*<<< orphan*/  USBPHY_PWD ; 
 int /*<<< orphan*/  USBPHY_STATUS ; 
 int /*<<< orphan*/  devclass_find (char*) ; 
 int /*<<< orphan*/ * devclass_get_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static int
phy_init(struct vybrid_ehci_softc *esc)
{
	device_t sc_gpio_dev;
	int reg;

	/* Reset phy */
	reg = PHY_READ4(esc, USBPHY_CTRL);
	reg |= (USBPHY_CTRL_SFTRST);
	PHY_WRITE4(esc, USBPHY_CTRL, reg);

	/* Minimum reset time */
	DELAY(10000);

	reg &= ~(USBPHY_CTRL_SFTRST | USBPHY_CTRL_CLKGATE);
	PHY_WRITE4(esc, USBPHY_CTRL, reg);

	reg = (ENUTMILEVEL2 | ENUTMILEVEL3);
	PHY_WRITE4(esc, USBPHY_CTRL_SET, reg);

	/* Get the GPIO device, we need this to give power to USB */
	sc_gpio_dev = devclass_get_device(devclass_find("gpio"), 0);
	if (sc_gpio_dev == NULL) {
		device_printf(esc->dev, "Error: failed to get the GPIO dev\n");
		return (1);
	}

	/* Give power to USB */
	GPIO_PIN_SETFLAGS(sc_gpio_dev, GPIO_USB_PWR, GPIO_PIN_OUTPUT);
	GPIO_PIN_SET(sc_gpio_dev, GPIO_USB_PWR, GPIO_PIN_HIGH);

	/* Power up PHY */
	PHY_WRITE4(esc, USBPHY_PWD, 0x00);

	/* Ungate clocks */
	reg = PHY_READ4(esc, USBPHY_DEBUG);
	reg &= ~(USBPHY_DEBUG_CLKGATE);
	PHY_WRITE4(esc, USBPHY_DEBUG, reg);

#if 0
	printf("USBPHY_CTRL == 0x%08x\n",
	    PHY_READ4(esc, USBPHY_CTRL));
	printf("USBPHY_IP == 0x%08x\n",
	    PHY_READ4(esc, USBPHY_IP));
	printf("USBPHY_STATUS == 0x%08x\n",
	    PHY_READ4(esc, USBPHY_STATUS));
	printf("USBPHY_DEBUG == 0x%08x\n",
	    PHY_READ4(esc, USBPHY_DEBUG));
	printf("USBPHY_DEBUG0_STATUS == 0x%08x\n",
	    PHY_READ4(esc, USBPHY_DEBUG0_STATUS));
	printf("USBPHY_DEBUG1 == 0x%08x\n",
	    PHY_READ4(esc, USBPHY_DEBUG1));
#endif

	return (0);
}