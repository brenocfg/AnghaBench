#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct ieee80211com {int ic_caps; int ic_txpowlimit; int /*<<< orphan*/ * ic_curchan; int /*<<< orphan*/ * ic_bsschan; int /*<<< orphan*/ * ic_channels; int /*<<< orphan*/  ic_curmode; int /*<<< orphan*/  ic_vaps; } ;
struct ndis_softc {int /*<<< orphan*/  ndis_dev; struct ieee80211com ndis_ic; } ;
struct ieee80211vap {int iv_flags; struct ieee80211_node* iv_bss; } ;
struct ieee80211_node {void* ni_authmode; int /*<<< orphan*/ * ni_chan; int /*<<< orphan*/  ni_esslen; int /*<<< orphan*/  ni_essid; int /*<<< orphan*/  ni_bssid; } ;
struct TYPE_7__ {int nc_dsconfig; } ;
struct TYPE_6__ {int /*<<< orphan*/  ns_ssidlen; int /*<<< orphan*/  ns_ssid; } ;
struct TYPE_8__ {TYPE_2__ nwbx_config; TYPE_1__ nwbx_ssid; int /*<<< orphan*/  nwbx_macaddr; int /*<<< orphan*/  nwbx_nettype; } ;
typedef  TYPE_3__ ndis_wlan_bssid_ex ;
typedef  int /*<<< orphan*/  arg ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_ADDR_COPY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* IEEE80211_AUTH_AUTO ; 
 void* IEEE80211_AUTH_NONE ; 
 void* IEEE80211_AUTH_OPEN ; 
 void* IEEE80211_AUTH_SHARED ; 
 void* IEEE80211_AUTH_WPA ; 
 int IEEE80211_C_PMGT ; 
 int IEEE80211_C_TXPMGT ; 
 int IEEE80211_F_DROPUNENC ; 
 int IEEE80211_F_PMGTON ; 
 int IEEE80211_F_PRIVACY ; 
 int IEEE80211_F_WPA ; 
 int IEEE80211_F_WPA1 ; 
 int IEEE80211_F_WPA2 ; 
 int /*<<< orphan*/  M_TEMP ; 
#define  NDIS_80211_AUTHMODE_AUTO 135 
#define  NDIS_80211_AUTHMODE_OPEN 134 
#define  NDIS_80211_AUTHMODE_SHARED 133 
#define  NDIS_80211_AUTHMODE_WPA 132 
#define  NDIS_80211_AUTHMODE_WPA2 131 
#define  NDIS_80211_AUTHMODE_WPA2PSK 130 
#define  NDIS_80211_AUTHMODE_WPANONE 129 
#define  NDIS_80211_AUTHMODE_WPAPSK 128 
 int NDIS_80211_POWERMODE_CAM ; 
 int NDIS_80211_WEPSTAT_ENABLED ; 
 int /*<<< orphan*/  NDIS_INITIALIZED (struct ndis_softc*) ; 
 int /*<<< orphan*/  OID_802_11_AUTHENTICATION_MODE ; 
 int /*<<< orphan*/  OID_802_11_POWER_MODE ; 
 int /*<<< orphan*/  OID_802_11_TX_POWER_LEVEL ; 
 int /*<<< orphan*/  OID_802_11_WEP_STATUS ; 
 struct ieee80211vap* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int* dBm2mW ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  free (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ieee80211_find_channel (struct ieee80211com*,int,int) ; 
 int ndis_get_assoc (struct ndis_softc*,TYPE_3__**) ; 
 int ndis_get_info (struct ndis_softc*,int /*<<< orphan*/ ,int*,int*) ; 
 int ndis_nettype_chan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ndis_nettype_mode (int /*<<< orphan*/ ) ; 
 int nitems (int*) ; 

__attribute__((used)) static void
ndis_getstate_80211(struct ndis_softc *sc)
{
	struct ieee80211com	*ic = &sc->ndis_ic;
	struct ieee80211vap	*vap = TAILQ_FIRST(&ic->ic_vaps);
	struct ieee80211_node	*ni = vap->iv_bss;
	ndis_wlan_bssid_ex	*bs;
	int			rval, len, i = 0;
	int			chanflag;
	uint32_t		arg;

	if (!NDIS_INITIALIZED(sc))
		return;

	if ((rval = ndis_get_assoc(sc, &bs)) != 0)
		return;

	/* We're associated, retrieve info on the current bssid. */
	ic->ic_curmode = ndis_nettype_mode(bs->nwbx_nettype);
	chanflag = ndis_nettype_chan(bs->nwbx_nettype);
	IEEE80211_ADDR_COPY(ni->ni_bssid, bs->nwbx_macaddr);

	/* Get SSID from current association info. */
	bcopy(bs->nwbx_ssid.ns_ssid, ni->ni_essid,
	    bs->nwbx_ssid.ns_ssidlen);
	ni->ni_esslen = bs->nwbx_ssid.ns_ssidlen;

	if (ic->ic_caps & IEEE80211_C_PMGT) {
		len = sizeof(arg);
		rval = ndis_get_info(sc, OID_802_11_POWER_MODE, &arg, &len);

		if (rval)
			device_printf(sc->ndis_dev,
			    "get power mode failed: %d\n", rval);
		if (arg == NDIS_80211_POWERMODE_CAM)
			vap->iv_flags &= ~IEEE80211_F_PMGTON;
		else
			vap->iv_flags |= IEEE80211_F_PMGTON;
	}

	/* Get TX power */
	if (ic->ic_caps & IEEE80211_C_TXPMGT) {
		len = sizeof(arg);
		ndis_get_info(sc, OID_802_11_TX_POWER_LEVEL, &arg, &len);
		for (i = 0; i < nitems(dBm2mW); i++)
			if (dBm2mW[i] >= arg)
				break;
		ic->ic_txpowlimit = i;
	}

	/*
	 * Use the current association information to reflect
	 * what channel we're on.
	 */
	ic->ic_curchan = ieee80211_find_channel(ic,
	    bs->nwbx_config.nc_dsconfig / 1000, chanflag);
	if (ic->ic_curchan == NULL)
		ic->ic_curchan = &ic->ic_channels[0];
	ni->ni_chan = ic->ic_curchan;
	ic->ic_bsschan = ic->ic_curchan;

	free(bs, M_TEMP);

	/*
	 * Determine current authentication mode.
	 */
	len = sizeof(arg);
	rval = ndis_get_info(sc, OID_802_11_AUTHENTICATION_MODE, &arg, &len);
	if (rval)
		device_printf(sc->ndis_dev,
		    "get authmode status failed: %d\n", rval);
	else {
		vap->iv_flags &= ~IEEE80211_F_WPA;
		switch (arg) {
		case NDIS_80211_AUTHMODE_OPEN:
			ni->ni_authmode = IEEE80211_AUTH_OPEN;
			break;
		case NDIS_80211_AUTHMODE_SHARED:
			ni->ni_authmode = IEEE80211_AUTH_SHARED;
			break;
		case NDIS_80211_AUTHMODE_AUTO:
			ni->ni_authmode = IEEE80211_AUTH_AUTO;
			break;
		case NDIS_80211_AUTHMODE_WPA:
		case NDIS_80211_AUTHMODE_WPAPSK:
		case NDIS_80211_AUTHMODE_WPANONE:
			ni->ni_authmode = IEEE80211_AUTH_WPA;
			vap->iv_flags |= IEEE80211_F_WPA1;
			break;
		case NDIS_80211_AUTHMODE_WPA2:
		case NDIS_80211_AUTHMODE_WPA2PSK:
			ni->ni_authmode = IEEE80211_AUTH_WPA;
			vap->iv_flags |= IEEE80211_F_WPA2;
			break;
		default:
			ni->ni_authmode = IEEE80211_AUTH_NONE;
			break;
		}
	}

	len = sizeof(arg);
	rval = ndis_get_info(sc, OID_802_11_WEP_STATUS, &arg, &len);

	if (rval)
		device_printf(sc->ndis_dev,
		    "get wep status failed: %d\n", rval);

	if (arg == NDIS_80211_WEPSTAT_ENABLED)
		vap->iv_flags |= IEEE80211_F_PRIVACY|IEEE80211_F_DROPUNENC;
	else
		vap->iv_flags &= ~(IEEE80211_F_PRIVACY|IEEE80211_F_DROPUNENC);
}