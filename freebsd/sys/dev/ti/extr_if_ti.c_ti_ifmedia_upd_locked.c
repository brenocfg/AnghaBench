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
struct ifmedia {int ifm_media; } ;
struct ti_softc {int /*<<< orphan*/  ti_hwrev; struct ifmedia ifmedia; } ;
struct ti_cmd_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_WRITE_4 (struct ti_softc*,int /*<<< orphan*/ ,int) ; 
 int EINVAL ; 
#define  IFM_1000_SX 134 
#define  IFM_1000_T 133 
#define  IFM_100_FX 132 
#define  IFM_100_TX 131 
#define  IFM_10_FL 130 
#define  IFM_10_T 129 
#define  IFM_AUTO 128 
 scalar_t__ IFM_ETHER ; 
 int IFM_FDX ; 
 int IFM_GMASK ; 
 int const IFM_SUBTYPE (int) ; 
 scalar_t__ IFM_TYPE (int) ; 
 int /*<<< orphan*/  TI_CMD_CODE_NEGOTIATE_10_100 ; 
 int /*<<< orphan*/  TI_CMD_CODE_NEGOTIATE_BOTH ; 
 int /*<<< orphan*/  TI_CMD_CODE_NEGOTIATE_GIGABIT ; 
 int /*<<< orphan*/  TI_CMD_LINK_NEGOTIATION ; 
 int /*<<< orphan*/  TI_DO_CMD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TI_GCR_GLINK ; 
 int /*<<< orphan*/  TI_GCR_LINK ; 
 int TI_GLNK_1000MB ; 
 int TI_GLNK_AUTONEGENB ; 
 int TI_GLNK_ENB ; 
 int TI_GLNK_FULL_DUPLEX ; 
 int TI_GLNK_PREF ; 
 int TI_GLNK_RX_FLOWCTL_Y ; 
 int TI_GLNK_TX_FLOWCTL_Y ; 
 int /*<<< orphan*/  TI_HWREV_TIGON ; 
 int TI_LNK_100MB ; 
 int TI_LNK_10MB ; 
 int TI_LNK_AUTONEGENB ; 
 int TI_LNK_ENB ; 
 int TI_LNK_FULL_DUPLEX ; 
 int TI_LNK_HALF_DUPLEX ; 
 int TI_LNK_PREF ; 
 int TI_LNK_RX_FLOWCTL_Y ; 
 int TI_LNK_TX_FLOWCTL_Y ; 
 int /*<<< orphan*/  TI_SETBIT (struct ti_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ti_ifmedia_upd_locked(struct ti_softc *sc)
{
	struct ifmedia *ifm;
	struct ti_cmd_desc cmd;
	uint32_t flowctl;

	ifm = &sc->ifmedia;

	if (IFM_TYPE(ifm->ifm_media) != IFM_ETHER)
		return (EINVAL);

	flowctl = 0;

	switch (IFM_SUBTYPE(ifm->ifm_media)) {
	case IFM_AUTO:
		/*
		 * Transmit flow control doesn't work on the Tigon 1.
		 */
		flowctl = TI_GLNK_RX_FLOWCTL_Y;

		/*
		 * Transmit flow control can also cause problems on the
		 * Tigon 2, apparently with both the copper and fiber
		 * boards.  The symptom is that the interface will just
		 * hang.  This was reproduced with Alteon 180 switches.
		 */
#if 0
		if (sc->ti_hwrev != TI_HWREV_TIGON)
			flowctl |= TI_GLNK_TX_FLOWCTL_Y;
#endif

		CSR_WRITE_4(sc, TI_GCR_GLINK, TI_GLNK_PREF|TI_GLNK_1000MB|
		    TI_GLNK_FULL_DUPLEX| flowctl |
		    TI_GLNK_AUTONEGENB|TI_GLNK_ENB);

		flowctl = TI_LNK_RX_FLOWCTL_Y;
#if 0
		if (sc->ti_hwrev != TI_HWREV_TIGON)
			flowctl |= TI_LNK_TX_FLOWCTL_Y;
#endif

		CSR_WRITE_4(sc, TI_GCR_LINK, TI_LNK_100MB|TI_LNK_10MB|
		    TI_LNK_FULL_DUPLEX|TI_LNK_HALF_DUPLEX| flowctl |
		    TI_LNK_AUTONEGENB|TI_LNK_ENB);
		TI_DO_CMD(TI_CMD_LINK_NEGOTIATION,
		    TI_CMD_CODE_NEGOTIATE_BOTH, 0);
		break;
	case IFM_1000_SX:
	case IFM_1000_T:
		flowctl = TI_GLNK_RX_FLOWCTL_Y;
#if 0
		if (sc->ti_hwrev != TI_HWREV_TIGON)
			flowctl |= TI_GLNK_TX_FLOWCTL_Y;
#endif

		CSR_WRITE_4(sc, TI_GCR_GLINK, TI_GLNK_PREF|TI_GLNK_1000MB|
		    flowctl |TI_GLNK_ENB);
		CSR_WRITE_4(sc, TI_GCR_LINK, 0);
		if ((ifm->ifm_media & IFM_GMASK) == IFM_FDX) {
			TI_SETBIT(sc, TI_GCR_GLINK, TI_GLNK_FULL_DUPLEX);
		}
		TI_DO_CMD(TI_CMD_LINK_NEGOTIATION,
		    TI_CMD_CODE_NEGOTIATE_GIGABIT, 0);
		break;
	case IFM_100_FX:
	case IFM_10_FL:
	case IFM_100_TX:
	case IFM_10_T:
		flowctl = TI_LNK_RX_FLOWCTL_Y;
#if 0
		if (sc->ti_hwrev != TI_HWREV_TIGON)
			flowctl |= TI_LNK_TX_FLOWCTL_Y;
#endif

		CSR_WRITE_4(sc, TI_GCR_GLINK, 0);
		CSR_WRITE_4(sc, TI_GCR_LINK, TI_LNK_ENB|TI_LNK_PREF|flowctl);
		if (IFM_SUBTYPE(ifm->ifm_media) == IFM_100_FX ||
		    IFM_SUBTYPE(ifm->ifm_media) == IFM_100_TX) {
			TI_SETBIT(sc, TI_GCR_LINK, TI_LNK_100MB);
		} else {
			TI_SETBIT(sc, TI_GCR_LINK, TI_LNK_10MB);
		}
		if ((ifm->ifm_media & IFM_GMASK) == IFM_FDX) {
			TI_SETBIT(sc, TI_GCR_LINK, TI_LNK_FULL_DUPLEX);
		} else {
			TI_SETBIT(sc, TI_GCR_LINK, TI_LNK_HALF_DUPLEX);
		}
		TI_DO_CMD(TI_CMD_LINK_NEGOTIATION,
		    TI_CMD_CODE_NEGOTIATE_10_100, 0);
		break;
	}

	return (0);
}