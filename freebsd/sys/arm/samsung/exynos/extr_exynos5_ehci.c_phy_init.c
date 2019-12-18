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
struct exynos_ehci_softc {int /*<<< orphan*/  host_bsh; int /*<<< orphan*/  host_bst; int /*<<< orphan*/  sysreg_bsh; int /*<<< orphan*/  sysreg_bst; } ;
typedef  int phandle_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int EXYNOS5_SYSREG_USB2_PHY ; 
 int /*<<< orphan*/  GPIO_INPUT ; 
 int /*<<< orphan*/  GPIO_OUTPUT ; 
 int HOST_CTRL_CLK_24MHZ ; 
 int HOST_CTRL_CLK_MASK ; 
 int HOST_CTRL_RESET_LINK ; 
 int HOST_CTRL_RESET_PHY ; 
 int HOST_CTRL_RESET_PHY_ALL ; 
 int HOST_CTRL_SIDDQ ; 
 int HOST_CTRL_SLEEP ; 
 int HOST_CTRL_SUSPEND ; 
 int OF_finddevice (char*) ; 
 int USB2_MODE_HOST ; 
 int bus_space_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_space_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  gpio_ctrl (struct exynos_ehci_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reset_hsic_hub (struct exynos_ehci_softc*,int) ; 
 int /*<<< orphan*/  usb2_phy_power_on () ; 

__attribute__((used)) static int
phy_init(struct exynos_ehci_softc *esc)
{
	int reg;
	phandle_t hub;

	gpio_ctrl(esc, GPIO_INPUT, 1);

	/* set USB HOST mode */
	bus_space_write_4(esc->sysreg_bst, esc->sysreg_bsh,
	    EXYNOS5_SYSREG_USB2_PHY, USB2_MODE_HOST);

	/* Power ON phy */
	usb2_phy_power_on();

	reg = bus_space_read_4(esc->host_bst, esc->host_bsh, 0x0);
	reg &= ~(HOST_CTRL_CLK_MASK |
	    HOST_CTRL_RESET_PHY |
	    HOST_CTRL_RESET_PHY_ALL |
	    HOST_CTRL_SIDDQ |
	    HOST_CTRL_SUSPEND |
	    HOST_CTRL_SLEEP);

	reg |= (HOST_CTRL_CLK_24MHZ |
	    HOST_CTRL_RESET_LINK);
	bus_space_write_4(esc->host_bst, esc->host_bsh, 0x0, reg);

	DELAY(10);

	reg = bus_space_read_4(esc->host_bst, esc->host_bsh, 0x0);
	reg &= ~(HOST_CTRL_RESET_LINK);
	bus_space_write_4(esc->host_bst, esc->host_bsh, 0x0, reg);

	if ((hub = OF_finddevice("/hsichub")) != -1) {
		reset_hsic_hub(esc, hub);
	}

	gpio_ctrl(esc, GPIO_OUTPUT, 1);

	return (0);
}