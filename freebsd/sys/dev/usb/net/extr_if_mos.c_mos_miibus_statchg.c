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
struct mos_softc {int /*<<< orphan*/  sc_mtx; } ;
struct mii_data {int mii_media_active; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct mii_data* GET_MII (struct mos_softc*) ; 
#define  IFM_100_TX 129 
#define  IFM_10_T 128 
 int IFM_FDX ; 
 int IFM_GMASK ; 
 int IFM_SUBTYPE (int) ; 
 int /*<<< orphan*/  MOS_CTL ; 
 int MOS_CTL_FDX_ENB ; 
 int MOS_CTL_RX_ENB ; 
 int MOS_CTL_SPEEDSEL ; 
 int MOS_CTL_TX_ENB ; 
 int /*<<< orphan*/  MOS_DPRINTFN (char*) ; 
 int /*<<< orphan*/  MOS_FRAME_DROP_CNT ; 
 int /*<<< orphan*/  MOS_LOCK (struct mos_softc*) ; 
 int /*<<< orphan*/  MOS_UNLOCK (struct mos_softc*) ; 
 struct mos_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int mos_reg_read_1 (struct mos_softc*,int /*<<< orphan*/ ) ; 
 int mos_reg_write_1 (struct mos_softc*,int /*<<< orphan*/ ,int) ; 
 int mtx_owned (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mos_miibus_statchg(device_t dev)
{
	struct mos_softc *sc = device_get_softc(dev);
	struct mii_data *mii = GET_MII(sc);
	int val, err, locked;

	locked = mtx_owned(&sc->sc_mtx);
	if (!locked)
		MOS_LOCK(sc);

	/* disable RX, TX prior to changing FDX, SPEEDSEL */
	val = mos_reg_read_1(sc, MOS_CTL);
	val &= ~(MOS_CTL_TX_ENB | MOS_CTL_RX_ENB);
	mos_reg_write_1(sc, MOS_CTL, val);

	/* reset register which counts dropped frames */
	mos_reg_write_1(sc, MOS_FRAME_DROP_CNT, 0);

	if ((mii->mii_media_active & IFM_GMASK) == IFM_FDX)
		val |= MOS_CTL_FDX_ENB;
	else
		val &= ~(MOS_CTL_FDX_ENB);

	switch (IFM_SUBTYPE(mii->mii_media_active)) {
	case IFM_100_TX:
		val |= MOS_CTL_SPEEDSEL;
		break;
	case IFM_10_T:
		val &= ~(MOS_CTL_SPEEDSEL);
		break;
	}

	/* re-enable TX, RX */
	val |= (MOS_CTL_TX_ENB | MOS_CTL_RX_ENB);
	err = mos_reg_write_1(sc, MOS_CTL, val);

	if (err)
		MOS_DPRINTFN("media change failed");

	if (!locked)
		MOS_UNLOCK(sc);
}