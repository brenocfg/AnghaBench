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
struct ieee80211com {int /*<<< orphan*/  ic_curchan; } ;
struct bwn_softc {int /*<<< orphan*/  sc_dev; struct ieee80211com sc_ic; } ;
struct bwn_phy_lp {int /*<<< orphan*/  plp_rssigs; int /*<<< orphan*/  plp_rssivc; int /*<<< orphan*/  plp_rssivf; int /*<<< orphan*/  plp_rxpwroffset; int /*<<< orphan*/  plp_bxarch; int /*<<< orphan*/  plp_txisoband_h; int /*<<< orphan*/  plp_txisoband_m; int /*<<< orphan*/  plp_txisoband_l; } ;
struct TYPE_2__ {struct bwn_phy_lp phy_lp; } ;
struct bwn_mac {struct bwn_softc* mac_sc; TYPE_1__ mac_phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_NVAR_BXA2G ; 
 int /*<<< orphan*/  BHND_NVAR_BXA5G ; 
 int /*<<< orphan*/  BHND_NVAR_RSSISAV2G ; 
 int /*<<< orphan*/  BHND_NVAR_RSSISAV5G ; 
 int /*<<< orphan*/  BHND_NVAR_RSSISMC2G ; 
 int /*<<< orphan*/  BHND_NVAR_RSSISMC5G ; 
 int /*<<< orphan*/  BHND_NVAR_RSSISMF2G ; 
 int /*<<< orphan*/  BHND_NVAR_RSSISMF5G ; 
 int /*<<< orphan*/  BHND_NVAR_RXPO2G ; 
 int /*<<< orphan*/  BHND_NVAR_RXPO5G ; 
 int /*<<< orphan*/  BHND_NVAR_TRI2G ; 
 int /*<<< orphan*/  BHND_NVAR_TRI5G ; 
 int /*<<< orphan*/  BHND_NVAR_TRI5GH ; 
 int /*<<< orphan*/  BHND_NVAR_TRI5GL ; 
 int /*<<< orphan*/  BWN_PHY_LP_READVAR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ IEEE80211_IS_CHAN_2GHZ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  int8 ; 
 int /*<<< orphan*/  uint8 ; 

__attribute__((used)) static int
bwn_phy_lp_readsprom(struct bwn_mac *mac)
{
	struct bwn_phy_lp *plp = &mac->mac_phy.phy_lp;
	struct bwn_softc *sc = mac->mac_sc;
	struct ieee80211com *ic = &sc->sc_ic;

#define	BWN_PHY_LP_READVAR(_dev, _type, _name, _result)		\
do {									\
	int error;							\
									\
	error = bhnd_nvram_getvar_ ##_type((_dev), (_name), (_result));	\
	if (error) {							\
		device_printf((_dev), "NVRAM variable %s unreadable: "	\
		    "%d\n", (_name), error);				\
		return (error);						\
	}								\
} while(0)

	if (IEEE80211_IS_CHAN_2GHZ(ic->ic_curchan)) {
		BWN_PHY_LP_READVAR(sc->sc_dev, uint8, BHND_NVAR_TRI2G,
		    &plp->plp_txisoband_m);
		BWN_PHY_LP_READVAR(sc->sc_dev, uint8, BHND_NVAR_BXA2G,
		    &plp->plp_bxarch);
		BWN_PHY_LP_READVAR(sc->sc_dev, int8, BHND_NVAR_RXPO2G,
		    &plp->plp_rxpwroffset);
		BWN_PHY_LP_READVAR(sc->sc_dev, uint8, BHND_NVAR_RSSISMF2G,
		    &plp->plp_rssivf);
		BWN_PHY_LP_READVAR(sc->sc_dev, uint8, BHND_NVAR_RSSISMC2G,
		    &plp->plp_rssivc);
		BWN_PHY_LP_READVAR(sc->sc_dev, uint8, BHND_NVAR_RSSISAV2G,
		    &plp->plp_rssigs);

		return (0);
	}

	BWN_PHY_LP_READVAR(sc->sc_dev, uint8, BHND_NVAR_TRI5GL,
	    &plp->plp_txisoband_l);
	BWN_PHY_LP_READVAR(sc->sc_dev, uint8, BHND_NVAR_TRI5G,
	    &plp->plp_txisoband_m);
	BWN_PHY_LP_READVAR(sc->sc_dev, uint8, BHND_NVAR_TRI5GH,
	    &plp->plp_txisoband_h);
	BWN_PHY_LP_READVAR(sc->sc_dev, uint8, BHND_NVAR_BXA5G,
	    &plp->plp_bxarch);
	BWN_PHY_LP_READVAR(sc->sc_dev, int8, BHND_NVAR_RXPO5G,
	    &plp->plp_rxpwroffset);
	BWN_PHY_LP_READVAR(sc->sc_dev, uint8, BHND_NVAR_RSSISMF5G,
	    &plp->plp_rssivf);
	BWN_PHY_LP_READVAR(sc->sc_dev, uint8, BHND_NVAR_RSSISMC5G,
	    &plp->plp_rssivc);
	BWN_PHY_LP_READVAR(sc->sc_dev, uint8, BHND_NVAR_RSSISAV5G,
	    &plp->plp_rssigs);

#undef	BWN_PHY_LP_READVAR

	return (0);
}