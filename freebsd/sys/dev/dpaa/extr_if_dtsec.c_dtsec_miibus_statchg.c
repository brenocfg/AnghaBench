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
struct dtsec_softc {int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_mach; TYPE_1__* sc_mii; } ;
typedef  int /*<<< orphan*/  e_EnetSpeed ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int mii_media_active; } ;

/* Variables and functions */
 int /*<<< orphan*/  DTSEC_LOCK_ASSERT (struct dtsec_softc*) ; 
 int E_OK ; 
 int FM_MAC_AdjustLink (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
#define  IFM_1000_SX 131 
#define  IFM_1000_T 130 
#define  IFM_100_TX 129 
#define  IFM_10_T 128 
 int IFM_FDX ; 
 int IFM_GMASK ; 
 int IFM_SUBTYPE (int) ; 
 struct dtsec_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  e_ENET_SPEED_10 ; 
 int /*<<< orphan*/  e_ENET_SPEED_100 ; 
 int /*<<< orphan*/  e_ENET_SPEED_1000 ; 

void
dtsec_miibus_statchg(device_t dev)
{
	struct dtsec_softc *sc;
	e_EnetSpeed speed;
	bool duplex;
	int error;

	sc = device_get_softc(dev);

	DTSEC_LOCK_ASSERT(sc);

	duplex = ((sc->sc_mii->mii_media_active & IFM_GMASK) == IFM_FDX);

	switch (IFM_SUBTYPE(sc->sc_mii->mii_media_active)) {
	case IFM_1000_T:
	case IFM_1000_SX:
		speed = e_ENET_SPEED_1000;
		break;

        case IFM_100_TX:
		speed = e_ENET_SPEED_100;
		break;

        case IFM_10_T:
		speed = e_ENET_SPEED_10;
		break;

	default:
		speed = e_ENET_SPEED_10;
	}

	error = FM_MAC_AdjustLink(sc->sc_mach, speed, duplex);
	if (error != E_OK)
		device_printf(sc->sc_dev, "error while adjusting MAC speed.\n");
}