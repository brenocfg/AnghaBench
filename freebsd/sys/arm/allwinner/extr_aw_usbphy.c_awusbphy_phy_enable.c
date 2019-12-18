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
struct phynode {int dummy; } ;
struct awusbphy_softc {int /*<<< orphan*/ ** reg; TYPE_1__* phy_conf; } ;
typedef  int /*<<< orphan*/ * regulator_t ;
typedef  int /*<<< orphan*/  intmax_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {intptr_t num_phys; } ;

/* Variables and functions */
 int ERANGE ; 
 int /*<<< orphan*/  awusbphy_configure (int /*<<< orphan*/ ,intptr_t) ; 
 int awusbphy_vbus_detect (int /*<<< orphan*/ ,int*) ; 
 scalar_t__ bootverbose ; 
 struct awusbphy_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  phynode_get_device (struct phynode*) ; 
 intptr_t phynode_get_id (struct phynode*) ; 
 int regulator_disable (int /*<<< orphan*/ *) ; 
 int regulator_enable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
awusbphy_phy_enable(struct phynode *phynode, bool enable)
{
	device_t dev;
	intptr_t phy;
	struct awusbphy_softc *sc;
	regulator_t reg;
	int error, vbus_det;

	dev = phynode_get_device(phynode);
	phy = phynode_get_id(phynode);
	sc = device_get_softc(dev);

	if (phy < 0 || phy >= sc->phy_conf->num_phys)
		return (ERANGE);

	/* Configure PHY */
	awusbphy_configure(dev, phy);

	/* Regulators are optional. If not found, return success. */
	reg = sc->reg[phy];
	if (reg == NULL)
		return (0);

	if (phy == 0) {
		/* If an external vbus is detected, do not enable phy 0 */
		error = awusbphy_vbus_detect(dev, &vbus_det);
		if (error)
			goto out;

		if (vbus_det == 1) {
			if (bootverbose)
				device_printf(dev, "External VBUS detected, not enabling the regulator\n");

			return (0);
		}
	}
	if (enable) {
		/* Depending on the PHY we need to route OTG to OHCI/EHCI */
		error = regulator_enable(reg);
	} else
		error = regulator_disable(reg);

out:
	if (error != 0) {
		device_printf(dev,
		    "couldn't %s regulator for phy %jd\n",
		    enable ? "enable" : "disable", (intmax_t)phy);
		return (error);
	}

	return (0);
}