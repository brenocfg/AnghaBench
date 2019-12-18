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
typedef  int uint32_t ;
struct sge_softc {int sge_flags; struct ifnet* sge_ifp; int /*<<< orphan*/  sge_miibus; } ;
struct mii_data {int mii_media_status; int /*<<< orphan*/  mii_media_active; } ;
struct ifnet {int if_drv_flags; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CSR_READ_4 (struct sge_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct sge_softc*,int /*<<< orphan*/ ,int) ; 
 int IFF_DRV_RUNNING ; 
#define  IFM_1000_T 130 
#define  IFM_100_TX 129 
#define  IFM_10_T 128 
 int IFM_ACTIVE ; 
 int IFM_AVALID ; 
 int IFM_FDX ; 
 int IFM_OPTIONS (int /*<<< orphan*/ ) ; 
 int IFM_SUBTYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RGMIIDelay ; 
 int SC_FDX ; 
 int SC_SPEED_10 ; 
 int SC_SPEED_100 ; 
 int SC_SPEED_1000 ; 
 int SC_SPEED_MASK ; 
 int SGE_FLAG_FASTETHER ; 
 int SGE_FLAG_FDX ; 
 int SGE_FLAG_GMII ; 
 int SGE_FLAG_LINK ; 
 int SGE_FLAG_RGMII ; 
 int SGE_FLAG_SPEED_1000 ; 
 int /*<<< orphan*/  StationControl ; 
 void* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sge_miibus_statchg(device_t dev)
{
	struct sge_softc *sc;
	struct mii_data *mii;
	struct ifnet *ifp;
	uint32_t ctl, speed;

	sc = device_get_softc(dev);
	mii = device_get_softc(sc->sge_miibus);
	ifp = sc->sge_ifp;
	if (mii == NULL || ifp == NULL ||
	    (ifp->if_drv_flags & IFF_DRV_RUNNING) == 0)
		return;
	speed = 0;
	sc->sge_flags &= ~SGE_FLAG_LINK;
	if ((mii->mii_media_status & (IFM_ACTIVE | IFM_AVALID)) ==
	    (IFM_ACTIVE | IFM_AVALID)) {
		switch (IFM_SUBTYPE(mii->mii_media_active)) {
		case IFM_10_T:
			sc->sge_flags |= SGE_FLAG_LINK;
			speed = SC_SPEED_10;
			break;
		case IFM_100_TX:
			sc->sge_flags |= SGE_FLAG_LINK;
			speed = SC_SPEED_100;
			break;
		case IFM_1000_T:
			if ((sc->sge_flags & SGE_FLAG_FASTETHER) == 0) {
				sc->sge_flags |= SGE_FLAG_LINK;
				speed = SC_SPEED_1000;
			}
			break;
		default:
			break;
                }
        }
	if ((sc->sge_flags & SGE_FLAG_LINK) == 0)
		return;
	/* Reprogram MAC to resolved speed/duplex/flow-control parameters. */
	ctl = CSR_READ_4(sc, StationControl);
	ctl &= ~(0x0f000000 | SC_FDX | SC_SPEED_MASK);
	if (speed == SC_SPEED_1000) {
		ctl |= 0x07000000;
		sc->sge_flags |= SGE_FLAG_SPEED_1000;
	} else {
		ctl |= 0x04000000;
		sc->sge_flags &= ~SGE_FLAG_SPEED_1000;
	}
#ifdef notyet
	if ((sc->sge_flags & SGE_FLAG_GMII) != 0)
		ctl |= 0x03000000;
#endif
	ctl |= speed;
	if ((IFM_OPTIONS(mii->mii_media_active) & IFM_FDX) != 0) {
		ctl |= SC_FDX;
		sc->sge_flags |= SGE_FLAG_FDX;
	} else
		sc->sge_flags &= ~SGE_FLAG_FDX;
	CSR_WRITE_4(sc, StationControl, ctl);
	if ((sc->sge_flags & SGE_FLAG_RGMII) != 0) {
		CSR_WRITE_4(sc, RGMIIDelay, 0x0441);
		CSR_WRITE_4(sc, RGMIIDelay, 0x0440);
	}
}