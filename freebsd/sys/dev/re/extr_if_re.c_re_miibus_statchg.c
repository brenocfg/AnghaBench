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
struct rl_softc {int rl_flags; struct ifnet* rl_ifp; int /*<<< orphan*/  rl_miibus; } ;
struct mii_data {int mii_media_status; int /*<<< orphan*/  mii_media_active; } ;
struct ifnet {int if_drv_flags; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int IFF_DRV_RUNNING ; 
#define  IFM_1000_T 130 
#define  IFM_100_TX 129 
#define  IFM_10_T 128 
 int IFM_ACTIVE ; 
 int IFM_AVALID ; 
 int IFM_SUBTYPE (int /*<<< orphan*/ ) ; 
 int RL_FLAG_FASTETHER ; 
 int RL_FLAG_LINK ; 
 void* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
re_miibus_statchg(device_t dev)
{
	struct rl_softc		*sc;
	struct ifnet		*ifp;
	struct mii_data		*mii;

	sc = device_get_softc(dev);
	mii = device_get_softc(sc->rl_miibus);
	ifp = sc->rl_ifp;
	if (mii == NULL || ifp == NULL ||
	    (ifp->if_drv_flags & IFF_DRV_RUNNING) == 0)
		return;

	sc->rl_flags &= ~RL_FLAG_LINK;
	if ((mii->mii_media_status & (IFM_ACTIVE | IFM_AVALID)) ==
	    (IFM_ACTIVE | IFM_AVALID)) {
		switch (IFM_SUBTYPE(mii->mii_media_active)) {
		case IFM_10_T:
		case IFM_100_TX:
			sc->rl_flags |= RL_FLAG_LINK;
			break;
		case IFM_1000_T:
			if ((sc->rl_flags & RL_FLAG_FASTETHER) != 0)
				break;
			sc->rl_flags |= RL_FLAG_LINK;
			break;
		default:
			break;
		}
	}
	/*
	 * RealTek controllers do not provide any interface to the RX/TX
	 * MACs for resolved speed, duplex and flow-control parameters.
	 */
}