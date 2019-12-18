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
struct padctl_softc {int /*<<< orphan*/  dev; } ;
struct padctl_port {int /*<<< orphan*/ * supply_vbus; } ;
struct padctl_lane {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  RD4 (struct padctl_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB2_BIAS_PAD_CTL0_PD ; 
 int /*<<< orphan*/  WR4 (struct padctl_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XUSB_PADCTL_USB2_BIAS_PAD_CTL0 ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int regulator_enable (int /*<<< orphan*/ *) ; 
 struct padctl_port* search_lane_port (struct padctl_softc*,struct padctl_lane*) ; 

__attribute__((used)) static int
usb2_powerdown(struct padctl_softc *sc, struct padctl_lane *lane)
{
	uint32_t reg;
	struct padctl_port *port;
	int rv;

	port = search_lane_port(sc, lane);
	if (port == NULL) {
		device_printf(sc->dev, "Cannot find port for lane: %s\n",
		    lane->name);
	}
	reg = RD4(sc, XUSB_PADCTL_USB2_BIAS_PAD_CTL0);
	reg |= USB2_BIAS_PAD_CTL0_PD;
	WR4(sc, XUSB_PADCTL_USB2_BIAS_PAD_CTL0, reg);

	if (port != NULL && port->supply_vbus != NULL) {
		rv = regulator_enable(port->supply_vbus);
		if (rv != 0) {
			device_printf(sc->dev,
			    "Cannot disable vbus regulator\n");
			return (rv);
		}
	}
	return (0);
}