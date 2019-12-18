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
struct thunder_mdio_softc {int /*<<< orphan*/  phy_desc_head; int /*<<< orphan*/ * reg_base; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  MDIO_LOCK_INIT (struct thunder_mdio_softc*,char*) ; 
 int REG_BASE_RID ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SMI_EN ; 
 int /*<<< orphan*/  SMI_EN_EN ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 struct thunder_mdio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mdio_reg_write (struct thunder_mdio_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
thunder_mdio_attach(device_t dev)
{
	struct thunder_mdio_softc *sc;
	int rid;

	sc = device_get_softc(dev);
	sc->dev = dev;

	/* Allocate memory resources */
	rid = REG_BASE_RID;
	sc->reg_base = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid,
	    RF_ACTIVE);
	if (sc->reg_base == NULL) {
		device_printf(dev, "Could not allocate memory\n");
		return (ENXIO);
	}

	TAILQ_INIT(&sc->phy_desc_head);
	MDIO_LOCK_INIT(sc, "ThunderX MDIO lock");

	/* Enable SMI/MDIO interface */
	mdio_reg_write(sc, SMI_EN, SMI_EN_EN);

	return (0);
}