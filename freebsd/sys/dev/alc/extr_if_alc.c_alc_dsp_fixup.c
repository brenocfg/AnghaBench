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
typedef  int uint16_t ;
struct alc_softc {int alc_flags; int /*<<< orphan*/  alc_rev; } ;

/* Variables and functions */
 int ALC_FLAG_AR816X_FAMILY ; 
 int ALC_FLAG_LINK ; 
 int ALC_FLAG_LINK_WAR ; 
 int ANEG_AFEE_10BT_100M_TH ; 
 scalar_t__ AR816X_REV (int /*<<< orphan*/ ) ; 
 scalar_t__ AR816X_REV_B0 ; 
 scalar_t__ AR816X_REV_C0 ; 
 int DBG_AGC_2_VGA_MASK ; 
 int DBG_AGC_2_VGA_SHIFT ; 
 int DBG_AGC_LONG100M_LIMT ; 
 int DBG_AGC_LONG1G_LIMT ; 
 int DBG_AZ_ANADECT_DEFAULT ; 
 int DBG_AZ_ANADECT_LONG ; 
 int DBG_MSE16DB_DOWN ; 
 int DBG_MSE16DB_UP ; 
 int DBG_MSE20DB_TH_DEFAULT ; 
 int DBG_MSE20DB_TH_HI ; 
 int DBG_MSE20DB_TH_MASK ; 
 int DBG_MSE20DB_TH_SHIFT ; 
 int EXT_CLDCTL6_CAB_LEN_MASK ; 
 int EXT_CLDCTL6_CAB_LEN_SHIFT ; 
 int EXT_CLDCTL6_CAB_LEN_SHORT1G ; 
 int IFM_1000_T ; 
 int IFM_100_TX ; 
 int /*<<< orphan*/  MII_DBG_AGC ; 
 int /*<<< orphan*/  MII_DBG_AZ_ANADECT ; 
 int /*<<< orphan*/  MII_DBG_MSE16DB ; 
 int /*<<< orphan*/  MII_DBG_MSE20DB ; 
 int /*<<< orphan*/  MII_EXT_ANEG ; 
 int /*<<< orphan*/  MII_EXT_ANEG_AFE ; 
 int /*<<< orphan*/  MII_EXT_CLDCTL6 ; 
 int /*<<< orphan*/  MII_EXT_PCS ; 
 int alc_miidbg_readreg (struct alc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alc_miidbg_writereg (struct alc_softc*,int /*<<< orphan*/ ,int) ; 
 int alc_miiext_readreg (struct alc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alc_miiext_writereg (struct alc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
alc_dsp_fixup(struct alc_softc *sc, int media)
{
	uint16_t agc, len, val;

	if ((sc->alc_flags & ALC_FLAG_AR816X_FAMILY) != 0)
		return;
	if (AR816X_REV(sc->alc_rev) >= AR816X_REV_C0)
		return;

	/*
	 * Vendor PHY magic.
	 * 1000BT/AZ, wrong cable length
	 */
	if ((sc->alc_flags & ALC_FLAG_LINK) != 0) {
		len = alc_miiext_readreg(sc, MII_EXT_PCS, MII_EXT_CLDCTL6);
		len = (len >> EXT_CLDCTL6_CAB_LEN_SHIFT) &
		    EXT_CLDCTL6_CAB_LEN_MASK;
		agc = alc_miidbg_readreg(sc, MII_DBG_AGC);
		agc = (agc >> DBG_AGC_2_VGA_SHIFT) & DBG_AGC_2_VGA_MASK;
		if ((media == IFM_1000_T && len > EXT_CLDCTL6_CAB_LEN_SHORT1G &&
		    agc > DBG_AGC_LONG1G_LIMT) ||
		    (media == IFM_100_TX && len > DBG_AGC_LONG100M_LIMT &&
		    agc > DBG_AGC_LONG1G_LIMT)) {
			alc_miidbg_writereg(sc, MII_DBG_AZ_ANADECT,
			    DBG_AZ_ANADECT_LONG);
			val = alc_miiext_readreg(sc, MII_EXT_ANEG,
			    MII_EXT_ANEG_AFE);
			val |= ANEG_AFEE_10BT_100M_TH;
			alc_miiext_writereg(sc, MII_EXT_ANEG, MII_EXT_ANEG_AFE,
			    val);
		} else {
			alc_miidbg_writereg(sc, MII_DBG_AZ_ANADECT,
			    DBG_AZ_ANADECT_DEFAULT);
			val = alc_miiext_readreg(sc, MII_EXT_ANEG,
			    MII_EXT_ANEG_AFE);
			val &= ~ANEG_AFEE_10BT_100M_TH;
			alc_miiext_writereg(sc, MII_EXT_ANEG, MII_EXT_ANEG_AFE,
			    val);
		}
		if ((sc->alc_flags & ALC_FLAG_LINK_WAR) != 0 &&
		    AR816X_REV(sc->alc_rev) == AR816X_REV_B0) {
			if (media == IFM_1000_T) {
				/*
				 * Giga link threshold, raise the tolerance of
				 * noise 50%.
				 */
				val = alc_miidbg_readreg(sc, MII_DBG_MSE20DB);
				val &= ~DBG_MSE20DB_TH_MASK;
				val |= (DBG_MSE20DB_TH_HI <<
				    DBG_MSE20DB_TH_SHIFT);
				alc_miidbg_writereg(sc, MII_DBG_MSE20DB, val);
			} else if (media == IFM_100_TX)
				alc_miidbg_writereg(sc, MII_DBG_MSE16DB,
				    DBG_MSE16DB_UP);
		}
	} else {
		val = alc_miiext_readreg(sc, MII_EXT_ANEG, MII_EXT_ANEG_AFE);
		val &= ~ANEG_AFEE_10BT_100M_TH;
		alc_miiext_writereg(sc, MII_EXT_ANEG, MII_EXT_ANEG_AFE, val);
		if ((sc->alc_flags & ALC_FLAG_LINK_WAR) != 0 &&
		    AR816X_REV(sc->alc_rev) == AR816X_REV_B0) {
			alc_miidbg_writereg(sc, MII_DBG_MSE16DB,
			    DBG_MSE16DB_DOWN);
			val = alc_miidbg_readreg(sc, MII_DBG_MSE20DB);
			val &= ~DBG_MSE20DB_TH_MASK;
			val |= (DBG_MSE20DB_TH_DEFAULT << DBG_MSE20DB_TH_SHIFT);
			alc_miidbg_writereg(sc, MII_DBG_MSE20DB, val);
		}
	}
}