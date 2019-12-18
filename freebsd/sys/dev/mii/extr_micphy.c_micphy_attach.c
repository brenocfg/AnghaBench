#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mii_softc {scalar_t__ mii_mpd_model; } ;
typedef  int phandle_t ;
struct TYPE_3__ {int /*<<< orphan*/  phynode; } ;
typedef  TYPE_1__ mii_fdt_phy_config_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  MIIF_NOMANPAUSE ; 
 scalar_t__ MII_MODEL_MICREL_KSZ8081 ; 
 scalar_t__ MII_MODEL_MICREL_KSZ9031 ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct mii_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ksz9021_load_values (struct mii_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ksz9031_load_values (struct mii_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  micphy_funcs ; 
 TYPE_1__* mii_fdt_get_config (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mii_phy_dev_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mii_phy_setmedia (struct mii_softc*) ; 
 int ofw_bus_get_node (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
micphy_attach(device_t dev)
{
	mii_fdt_phy_config_t *cfg;
	struct mii_softc *sc;
	phandle_t node;
	device_t miibus;
	device_t parent;

	sc = device_get_softc(dev);

	mii_phy_dev_attach(dev, MIIF_NOMANPAUSE, &micphy_funcs, 1);
	mii_phy_setmedia(sc);

	/* Nothing further to configure for 8081 model. */
	if (sc->mii_mpd_model == MII_MODEL_MICREL_KSZ8081)
		return (0);

	miibus = device_get_parent(dev);
	parent = device_get_parent(miibus);

	if ((node = ofw_bus_get_node(parent)) == -1)
		return (ENXIO);

	cfg = mii_fdt_get_config(dev);

	if (sc->mii_mpd_model == MII_MODEL_MICREL_KSZ9031)
		ksz9031_load_values(sc, cfg->phynode);
	else
		ksz9021_load_values(sc, cfg->phynode);

	return (0);
}