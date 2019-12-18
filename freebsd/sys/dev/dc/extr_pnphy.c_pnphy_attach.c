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
struct mii_softc {int mii_capabilities; int mii_capmask; int /*<<< orphan*/  mii_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BMSR_100TXFDX ; 
 int BMSR_100TXHDX ; 
 int BMSR_10TFDX ; 
 int BMSR_10THDX ; 
 int /*<<< orphan*/  MIIBUS_MEDIAINIT (int /*<<< orphan*/ ) ; 
 int MIIF_NOISOLATE ; 
 int MIIF_NOMANPAUSE ; 
 struct mii_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mii_phy_add_media (struct mii_softc*) ; 
 int /*<<< orphan*/  mii_phy_dev_attach (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pnphy_funcs ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int
pnphy_attach(device_t dev)
{
	struct mii_softc *sc;

	sc = device_get_softc(dev);

	mii_phy_dev_attach(dev, MIIF_NOISOLATE | MIIF_NOMANPAUSE,
	    &pnphy_funcs, 0);

	sc->mii_capabilities =
	    BMSR_100TXFDX | BMSR_100TXHDX | BMSR_10TFDX | BMSR_10THDX;
	sc->mii_capabilities &= sc->mii_capmask;
	device_printf(dev, " ");
	mii_phy_add_media(sc);
	printf("\n");

	MIIBUS_MEDIAINIT(sc->mii_dev);
	return (0);
}