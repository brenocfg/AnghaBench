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
struct ifmedia {int dummy; } ;
struct mii_data {struct ifmedia mii_media; } ;
struct dc_softc {int /*<<< orphan*/  dc_miibus; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ DC_IS_DAVICOM (struct dc_softc*) ; 
 int DC_REVISION_DM9102A ; 
 int IFM_ETHER ; 
 int IFM_HPNA_1 ; 
 void* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifmedia_add (struct ifmedia*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int pci_get_revid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dc_miibus_mediainit(device_t dev)
{
	struct dc_softc *sc;
	struct mii_data *mii;
	struct ifmedia *ifm;
	int rev;

	rev = pci_get_revid(dev);

	sc = device_get_softc(dev);
	mii = device_get_softc(sc->dc_miibus);
	ifm = &mii->mii_media;

	if (DC_IS_DAVICOM(sc) && rev >= DC_REVISION_DM9102A)
		ifmedia_add(ifm, IFM_ETHER | IFM_HPNA_1, 0, NULL);
}