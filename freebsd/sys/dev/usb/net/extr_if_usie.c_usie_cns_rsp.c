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
struct usie_softc {int sc_rssi; int /*<<< orphan*/  sc_dev; struct ifnet* sc_ifp; } ;
struct usie_cns {int /*<<< orphan*/  id; int /*<<< orphan*/  obj; } ;
struct ifnet {int if_drv_flags; int /*<<< orphan*/  if_flags; } ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  IFF_UP ; 
 int USIE_CNS_ID_INIT ; 
 int USIE_CNS_ID_STOP ; 
#define  USIE_CNS_OB_LINK_UPDATE 131 
#define  USIE_CNS_OB_PDP_READ 130 
#define  USIE_CNS_OB_PROF_WRITE 129 
#define  USIE_CNS_OB_RSSI 128 
 int be16toh (int /*<<< orphan*/ ) ; 
 int be32toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  usie_if_sync_to (struct usie_softc*) ; 

__attribute__((used)) static void
usie_cns_rsp(struct usie_softc *sc, struct usie_cns *cns)
{
	struct ifnet *ifp = sc->sc_ifp;

	DPRINTF("received CnS\n");

	switch (be16toh(cns->obj)) {
	case USIE_CNS_OB_LINK_UPDATE:
		if (be32toh(cns->id) & USIE_CNS_ID_INIT)
			usie_if_sync_to(sc);
		else if (be32toh(cns->id) & USIE_CNS_ID_STOP) {
			ifp->if_flags &= ~IFF_UP;
			ifp->if_drv_flags &=
			    ~(IFF_DRV_RUNNING | IFF_DRV_OACTIVE);
		} else
			DPRINTF("undefined link update\n");
		break;

	case USIE_CNS_OB_RSSI:
		sc->sc_rssi = be16toh(*(int16_t *)(cns + 1));
		if (sc->sc_rssi <= 0)
			device_printf(sc->sc_dev, "No signal\n");
		else {
			device_printf(sc->sc_dev, "RSSI=%ddBm\n",
			    sc->sc_rssi - 110);
		}
		break;

	case USIE_CNS_OB_PROF_WRITE:
		break;

	case USIE_CNS_OB_PDP_READ:
		break;

	default:
		DPRINTF("undefined CnS\n");
		break;
	}
}