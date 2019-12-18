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
typedef  int uint32_t ;
struct omap_ehci_softc {int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  OMAP_USBHOST_INSNREG05_ULPI ; 
 int OMAP_USBHOST_INSNREG05_ULPI_CONTROL_SHIFT ; 
 int OMAP_USBHOST_INSNREG05_ULPI_OPSEL_SHIFT ; 
 unsigned int OMAP_USBHOST_INSNREG05_ULPI_PORTSEL_SHIFT ; 
 int OMAP_USBHOST_INSNREG05_ULPI_REGADD_SHIFT ; 
 int /*<<< orphan*/  ULPI_FUNC_CTRL ; 
 int ULPI_FUNC_CTRL_RESET ; 
 int ULPI_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int hz ; 
 int omap_ehci_read_4 (struct omap_ehci_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_ehci_write_4 (struct omap_ehci_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pause (char*,int) ; 

__attribute__((used)) static void 
omap_ehci_soft_phy_reset(struct omap_ehci_softc *isc, unsigned int port)
{
	unsigned long timeout = (hz < 10) ? 1 : ((100 * hz) / 1000);
	uint32_t reg;

	reg = ULPI_FUNC_CTRL_RESET
		/* FUNCTION_CTRL_SET register */
		| (ULPI_SET(ULPI_FUNC_CTRL) << OMAP_USBHOST_INSNREG05_ULPI_REGADD_SHIFT)
		/* Write */
		| (2 << OMAP_USBHOST_INSNREG05_ULPI_OPSEL_SHIFT)
		/* PORTn */
		| ((port + 1) << OMAP_USBHOST_INSNREG05_ULPI_PORTSEL_SHIFT)
		/* start ULPI access*/
		| (1 << OMAP_USBHOST_INSNREG05_ULPI_CONTROL_SHIFT);

	omap_ehci_write_4(isc, OMAP_USBHOST_INSNREG05_ULPI, reg);

	/* Wait for ULPI access completion */
	while ((omap_ehci_read_4(isc, OMAP_USBHOST_INSNREG05_ULPI)
	       & (1 << OMAP_USBHOST_INSNREG05_ULPI_CONTROL_SHIFT))) {

		/* Sleep for a tick */
		pause("USBPHY_RESET", 1);
		
		if (timeout-- == 0) {
			device_printf(isc->sc_dev, "PHY reset operation timed out\n");
			break;
		}
	}
}