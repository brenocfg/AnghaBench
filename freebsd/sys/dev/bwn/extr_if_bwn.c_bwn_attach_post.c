#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct TYPE_6__ {int /*<<< orphan*/  wme_update; } ;
struct ieee80211com {int ic_caps; int ic_headroom; int /*<<< orphan*/  ic_parent; int /*<<< orphan*/  ic_transmit; int /*<<< orphan*/  ic_vap_delete; int /*<<< orphan*/  ic_vap_create; int /*<<< orphan*/  ic_set_channel; int /*<<< orphan*/  ic_scan_end; int /*<<< orphan*/  ic_scan_start; TYPE_2__ ic_wme; int /*<<< orphan*/  ic_update_promisc; int /*<<< orphan*/  ic_updateslot; int /*<<< orphan*/  ic_raw_xmit; int /*<<< orphan*/  ic_macaddr; int /*<<< orphan*/  ic_flags_ext; int /*<<< orphan*/  ic_opmode; int /*<<< orphan*/  ic_phytype; int /*<<< orphan*/  ic_name; struct bwn_softc* ic_softc; } ;
struct bwn_txhdr {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  wr_ihdr; } ;
struct TYPE_7__ {int /*<<< orphan*/  wt_ihdr; } ;
struct TYPE_5__ {int board_srom_rev; } ;
struct bwn_softc {TYPE_4__ sc_rx_th; TYPE_3__ sc_tx_th; int /*<<< orphan*/  sc_dev; TYPE_1__ sc_board_info; struct ieee80211com sc_ic; } ;

/* Variables and functions */
 char* BHND_NVAR_ET1MACADDR ; 
 char* BHND_NVAR_IL0MACADDR ; 
 char* BHND_NVAR_MACADDR ; 
 int /*<<< orphan*/  BHND_NVRAM_TYPE_UINT8_ARRAY ; 
 int /*<<< orphan*/  BWN_RX_RADIOTAP_PRESENT ; 
 int /*<<< orphan*/  BWN_TX_RADIOTAP_PRESENT ; 
 int ENXIO ; 
 int IEEE80211_C_AHDEMO ; 
 int IEEE80211_C_BGSCAN ; 
 int IEEE80211_C_MONITOR ; 
 int IEEE80211_C_SHPREAMBLE ; 
 int IEEE80211_C_SHSLOT ; 
 int IEEE80211_C_STA ; 
 int IEEE80211_C_TXPMGT ; 
 int IEEE80211_C_WME ; 
 int IEEE80211_C_WPA ; 
 int /*<<< orphan*/  IEEE80211_FEXT_SWBMISS ; 
 int /*<<< orphan*/  IEEE80211_M_STA ; 
 int /*<<< orphan*/  IEEE80211_T_OFDM ; 
 int bhnd_get_core_unit (int /*<<< orphan*/ ) ; 
 int bhnd_nvram_getvar_array (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  bwn_parent ; 
 int /*<<< orphan*/  bwn_raw_xmit ; 
 int /*<<< orphan*/  bwn_scan_end ; 
 int /*<<< orphan*/  bwn_scan_start ; 
 int /*<<< orphan*/  bwn_set_channel ; 
 int /*<<< orphan*/  bwn_sysctl_node (struct bwn_softc*) ; 
 int /*<<< orphan*/  bwn_transmit ; 
 int /*<<< orphan*/  bwn_update_promisc ; 
 int /*<<< orphan*/  bwn_updateslot ; 
 int /*<<< orphan*/  bwn_vap_create ; 
 int /*<<< orphan*/  bwn_vap_delete ; 
 int /*<<< orphan*/  bwn_wme_update ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ieee80211_announce (struct ieee80211com*) ; 
 int /*<<< orphan*/  ieee80211_ifattach (struct ieee80211com*) ; 
 int /*<<< orphan*/  ieee80211_radiotap_attach (struct ieee80211com*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bwn_attach_post(struct bwn_softc *sc)
{
	struct ieee80211com	*ic;
	const char		*mac_varname;
	u_int			 core_unit;
	int			 error;

	ic = &sc->sc_ic;

	ic->ic_softc = sc;
	ic->ic_name = device_get_nameunit(sc->sc_dev);
	/* XXX not right but it's not used anywhere important */
	ic->ic_phytype = IEEE80211_T_OFDM;
	ic->ic_opmode = IEEE80211_M_STA;
	ic->ic_caps =
		  IEEE80211_C_STA		/* station mode supported */
		| IEEE80211_C_MONITOR		/* monitor mode */
		| IEEE80211_C_AHDEMO		/* adhoc demo mode */
		| IEEE80211_C_SHPREAMBLE	/* short preamble supported */
		| IEEE80211_C_SHSLOT		/* short slot time supported */
		| IEEE80211_C_WME		/* WME/WMM supported */
		| IEEE80211_C_WPA		/* capable of WPA1+WPA2 */
#if 0
		| IEEE80211_C_BGSCAN		/* capable of bg scanning */
#endif
		| IEEE80211_C_TXPMGT		/* capable of txpow mgt */
		;

	ic->ic_flags_ext |= IEEE80211_FEXT_SWBMISS;	/* s/w bmiss */

	/* Determine the NVRAM variable containing our MAC address */
	core_unit = bhnd_get_core_unit(sc->sc_dev);
	mac_varname = NULL;
	if (sc->sc_board_info.board_srom_rev <= 2) {
		if (core_unit == 0) {
			mac_varname = BHND_NVAR_IL0MACADDR;
		} else if (core_unit == 1) {
			mac_varname = BHND_NVAR_ET1MACADDR;
		}
	} else {
		if (core_unit == 0) {
			mac_varname = BHND_NVAR_MACADDR;
		}
	}

	if (mac_varname == NULL) {
		device_printf(sc->sc_dev, "missing MAC address variable for "
		    "D11 core %u", core_unit);
		return (ENXIO);
	}

	/* Read the MAC address from NVRAM */
	error = bhnd_nvram_getvar_array(sc->sc_dev, mac_varname, ic->ic_macaddr,
	    sizeof(ic->ic_macaddr), BHND_NVRAM_TYPE_UINT8_ARRAY);
	if (error) {
		device_printf(sc->sc_dev, "error reading %s: %d\n", mac_varname,
		    error);
		return (error);
	}

	/* call MI attach routine. */
	ieee80211_ifattach(ic);

	ic->ic_headroom = sizeof(struct bwn_txhdr);

	/* override default methods */
	ic->ic_raw_xmit = bwn_raw_xmit;
	ic->ic_updateslot = bwn_updateslot;
	ic->ic_update_promisc = bwn_update_promisc;
	ic->ic_wme.wme_update = bwn_wme_update;
	ic->ic_scan_start = bwn_scan_start;
	ic->ic_scan_end = bwn_scan_end;
	ic->ic_set_channel = bwn_set_channel;
	ic->ic_vap_create = bwn_vap_create;
	ic->ic_vap_delete = bwn_vap_delete;
	ic->ic_transmit = bwn_transmit;
	ic->ic_parent = bwn_parent;

	ieee80211_radiotap_attach(ic,
	    &sc->sc_tx_th.wt_ihdr, sizeof(sc->sc_tx_th),
	    BWN_TX_RADIOTAP_PRESENT,
	    &sc->sc_rx_th.wr_ihdr, sizeof(sc->sc_rx_th),
	    BWN_RX_RADIOTAP_PRESENT);

	bwn_sysctl_node(sc);

	if (bootverbose)
		ieee80211_announce(ic);
	return (0);
}