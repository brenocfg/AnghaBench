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
struct mii_bus {int dummy; } ;
struct ar8xxx_priv {TYPE_1__* chip; struct mii_bus* mii_bus; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* phy_fixup ) (struct ar8xxx_priv*,int) ;} ;

/* Variables and functions */
 int ADVERTISE_1000FULL ; 
 int ADVERTISE_ALL ; 
 int ADVERTISE_PAUSE_ASYM ; 
 int ADVERTISE_PAUSE_CAP ; 
 int AR8XXX_NUM_PHYS ; 
 int BMCR_ANENABLE ; 
 int BMCR_RESET ; 
 int /*<<< orphan*/  MII_ADVERTISE ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  MII_CTRL1000 ; 
 scalar_t__ ar8xxx_has_gige (struct ar8xxx_priv*) ; 
 int /*<<< orphan*/  ar8xxx_phy_poll_reset (struct mii_bus*) ; 
 int /*<<< orphan*/  mdiobus_write (struct mii_bus*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct ar8xxx_priv*,int) ; 

void
ar8xxx_phy_init(struct ar8xxx_priv *priv)
{
	int i;
	struct mii_bus *bus;

	bus = priv->mii_bus;
	for (i = 0; i < AR8XXX_NUM_PHYS; i++) {
		if (priv->chip->phy_fixup)
			priv->chip->phy_fixup(priv, i);

		/* initialize the port itself */
		mdiobus_write(bus, i, MII_ADVERTISE,
			ADVERTISE_ALL | ADVERTISE_PAUSE_CAP | ADVERTISE_PAUSE_ASYM);
		if (ar8xxx_has_gige(priv))
			mdiobus_write(bus, i, MII_CTRL1000, ADVERTISE_1000FULL);
		mdiobus_write(bus, i, MII_BMCR, BMCR_RESET | BMCR_ANENABLE);
	}

	ar8xxx_phy_poll_reset(bus);
}