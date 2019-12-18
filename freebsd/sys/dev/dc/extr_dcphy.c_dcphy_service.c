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
typedef  int u_int32_t ;
struct mii_softc {int mii_ticks; } ;
struct TYPE_2__ {struct ifmedia_entry* ifm_cur; } ;
struct mii_data {int /*<<< orphan*/  mii_ifp; int /*<<< orphan*/  mii_media_active; TYPE_1__ mii_media; } ;
struct ifmedia_entry {int ifm_media; } ;
struct dc_softc {int dummy; } ;

/* Variables and functions */
 void* CSR_READ_4 (struct dc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct dc_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DC_10BTCTRL ; 
 int /*<<< orphan*/  DC_10BTSTAT ; 
 int /*<<< orphan*/  DC_CLRBIT (struct dc_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DC_NETCFG ; 
 int DC_NETCFG_FULLDUPLEX ; 
 int DC_NETCFG_PCS ; 
 int DC_NETCFG_PORTSEL ; 
 int DC_NETCFG_SCRAMBLER ; 
 int DC_NETCFG_SPEEDSEL ; 
 int /*<<< orphan*/  DC_SETBIT (struct dc_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DC_SIARESET ; 
 int DC_SIA_RESET ; 
 int DC_TCTL_AUTONEGENBL ; 
 int DC_TSTAT_LS10 ; 
 int DC_TSTAT_LS100 ; 
 int EINVAL ; 
 int IFF_UP ; 
#define  IFM_100_TX 133 
#define  IFM_10_T 132 
#define  IFM_AUTO 131 
 int IFM_FDX ; 
 int /*<<< orphan*/  IFM_NONE ; 
 int const IFM_SUBTYPE (int) ; 
#define  MII_MEDIACHG 130 
#define  MII_POLLSTAT 129 
#define  MII_TICK 128 
 int /*<<< orphan*/  PHY_RESET (struct mii_softc*) ; 
 int /*<<< orphan*/  PHY_STATUS (struct mii_softc*) ; 
 int /*<<< orphan*/  dcphy_auto (struct mii_softc*) ; 
 int if_getflags (int /*<<< orphan*/ ) ; 
 struct dc_softc* if_getsoftc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mii_phy_update (struct mii_softc*,int) ; 

__attribute__((used)) static int
dcphy_service(struct mii_softc *sc, struct mii_data *mii, int cmd)
{
	struct dc_softc		*dc_sc;
	struct ifmedia_entry *ife = mii->mii_media.ifm_cur;
	int reg;
	u_int32_t		mode;

	dc_sc = if_getsoftc(mii->mii_ifp);

	switch (cmd) {
	case MII_POLLSTAT:
		break;

	case MII_MEDIACHG:
		/*
		 * If the interface is not up, don't do anything.
		 */
		if ((if_getflags(mii->mii_ifp) & IFF_UP) == 0)
			break;

		mii->mii_media_active = IFM_NONE;
		mode = CSR_READ_4(dc_sc, DC_NETCFG);
		mode &= ~(DC_NETCFG_FULLDUPLEX | DC_NETCFG_PORTSEL |
		    DC_NETCFG_PCS | DC_NETCFG_SCRAMBLER | DC_NETCFG_SPEEDSEL);

		switch (IFM_SUBTYPE(ife->ifm_media)) {
		case IFM_AUTO:
			/*PHY_RESET(sc);*/
			(void)dcphy_auto(sc);
			break;
		case IFM_100_TX:
			PHY_RESET(sc);
			DC_CLRBIT(dc_sc, DC_10BTCTRL, DC_TCTL_AUTONEGENBL);
			mode |= DC_NETCFG_PORTSEL | DC_NETCFG_PCS |
			    DC_NETCFG_SCRAMBLER;
			if ((ife->ifm_media & IFM_FDX) != 0)
				mode |= DC_NETCFG_FULLDUPLEX;
			else
				mode &= ~DC_NETCFG_FULLDUPLEX;
			CSR_WRITE_4(dc_sc, DC_NETCFG, mode);
			break;
		case IFM_10_T:
			DC_CLRBIT(dc_sc, DC_SIARESET, DC_SIA_RESET);
			DC_CLRBIT(dc_sc, DC_10BTCTRL, 0xFFFF);
			if ((ife->ifm_media & IFM_FDX) != 0)
				DC_SETBIT(dc_sc, DC_10BTCTRL, 0x7F3D);
			else
				DC_SETBIT(dc_sc, DC_10BTCTRL, 0x7F3F);
			DC_SETBIT(dc_sc, DC_SIARESET, DC_SIA_RESET);
			DC_CLRBIT(dc_sc, DC_10BTCTRL, DC_TCTL_AUTONEGENBL);
			mode &= ~DC_NETCFG_PORTSEL;
			mode |= DC_NETCFG_SPEEDSEL;
			if ((ife->ifm_media & IFM_FDX) != 0)
				mode |= DC_NETCFG_FULLDUPLEX;
			else
				mode &= ~DC_NETCFG_FULLDUPLEX;
			CSR_WRITE_4(dc_sc, DC_NETCFG, mode);
			break;
		default:
			return (EINVAL);
		}
		break;

	case MII_TICK:
		/*
		 * Is the interface even up?
		 */
		if ((if_getflags(mii->mii_ifp) & IFF_UP) == 0)
			return (0);

		/*
		 * Only used for autonegotiation.
		 */
		if (IFM_SUBTYPE(ife->ifm_media) != IFM_AUTO)
			break;

		reg = CSR_READ_4(dc_sc, DC_10BTSTAT);
		if (!(reg & DC_TSTAT_LS10) || !(reg & DC_TSTAT_LS100))
			break;

                /*
                 * Only retry autonegotiation every 5 seconds.
		 *
		 * Otherwise, fall through to calling dcphy_status()
		 * since real Intel 21143 chips don't show valid link
		 * status until autonegotiation is switched off, and
		 * that only happens in dcphy_status().  Without this,
		 * successful autonegotiation is never recognised on
		 * these chips.
                 */
                if (++sc->mii_ticks <= 50)
			break;

		sc->mii_ticks = 0;
		dcphy_auto(sc);

		break;
	}

	/* Update the media status. */
	PHY_STATUS(sc);

	/* Callback if something changed. */
	mii_phy_update(sc, cmd);
	return (0);
}