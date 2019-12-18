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
typedef  int /*<<< orphan*/  val ;
typedef  int u_int16_t ;
struct wi_softc {scalar_t__ sc_firmware_type; scalar_t__ sc_enabled; } ;
struct ifnet {struct ieee80211vap* if_softc; } ;
struct ifmediareq {int dummy; } ;
struct ieee80211vap {TYPE_1__* iv_bss; struct ieee80211com* iv_ic; } ;
struct ieee80211com {struct wi_softc* ic_softc; } ;
struct TYPE_2__ {int ni_txrate; } ;

/* Variables and functions */
 scalar_t__ WI_LUCENT ; 
 int /*<<< orphan*/  WI_RID_CUR_TX_RATE ; 
 int /*<<< orphan*/  ieee80211_media_status (struct ifnet*,struct ifmediareq*) ; 
 int le16toh (int) ; 
 scalar_t__ wi_read_rid (struct wi_softc*,int /*<<< orphan*/ ,int*,int*) ; 

__attribute__((used)) static void
wi_media_status(struct ifnet *ifp, struct ifmediareq *imr)
{
	struct ieee80211vap *vap = ifp->if_softc;
	struct ieee80211com *ic = vap->iv_ic;
	struct wi_softc *sc = ic->ic_softc;
	u_int16_t val;
	int rate, len;

	len = sizeof(val);
	if (sc->sc_enabled &&
	    wi_read_rid(sc, WI_RID_CUR_TX_RATE, &val, &len) == 0 &&
	    len == sizeof(val)) {
		/* convert to 802.11 rate */
		val = le16toh(val);
		rate = val * 2;
		if (sc->sc_firmware_type == WI_LUCENT) {
			if (rate == 10)
				rate = 11;	/* 5.5Mbps */
		} else {
			if (rate == 4*2)
				rate = 11;	/* 5.5Mbps */
			else if (rate == 8*2)
				rate = 22;	/* 11Mbps */
		}
		vap->iv_bss->ni_txrate = rate;
	}
	ieee80211_media_status(ifp, imr);
}