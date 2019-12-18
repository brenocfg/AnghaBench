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
struct ieee80211com {int /*<<< orphan*/  ic_vaps; } ;
struct iwi_softc {int sc_state_timer; int /*<<< orphan*/  sc_disassoctask; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  fw_state; int /*<<< orphan*/  flags; int /*<<< orphan*/  sc_monitortask; struct ieee80211com sc_ic; } ;
struct iwi_notif_scan_complete {int /*<<< orphan*/  status; int /*<<< orphan*/  nchan; } ;
struct iwi_notif_scan_channel {int /*<<< orphan*/  nchan; } ;
struct iwi_notif_beacon_state {int /*<<< orphan*/  number; int /*<<< orphan*/  state; } ;
struct iwi_notif_authentication {int /*<<< orphan*/  state; } ;
struct iwi_notif_association {int /*<<< orphan*/  state; } ;
struct iwi_notif {int type; int /*<<< orphan*/  len; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  is_beacon_miss; int /*<<< orphan*/  is_rx_disassoc; int /*<<< orphan*/  is_rx_auth_fail; int /*<<< orphan*/  is_rx_deauth; } ;
struct ieee80211vap {TYPE_1__ iv_stats; int /*<<< orphan*/  iv_bmissthreshold; int /*<<< orphan*/  iv_state; int /*<<< orphan*/  iv_opmode; } ;
struct ieee80211_frame {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  DPRINTFN (int,char*) ; 
 int /*<<< orphan*/  IEEE80211_M_MONITOR ; 
 int /*<<< orphan*/  IEEE80211_S_ASSOC ; 
 int /*<<< orphan*/  IEEE80211_S_RUN ; 
 int /*<<< orphan*/  IEEE80211_S_SCAN ; 
#define  IWI_ASSOC_INIT 145 
#define  IWI_ASSOC_SUCCESS 144 
#define  IWI_AUTH_FAIL 143 
#define  IWI_AUTH_RECV_2 142 
#define  IWI_AUTH_SENT_1 141 
#define  IWI_AUTH_SEQ1_FAIL 140 
#define  IWI_AUTH_SEQ1_PASS 139 
#define  IWI_AUTH_SUCCESS 138 
 int /*<<< orphan*/  IWI_BEACON_MISS ; 
 int /*<<< orphan*/  IWI_FLAG_ASSOCIATED ; 
#define  IWI_FW_ASSOCIATING 137 
#define  IWI_FW_DISASSOCIATING 136 
 int const IWI_FW_SCANNING ; 
#define  IWI_NOTIF_TYPE_ASSOCIATION 135 
#define  IWI_NOTIF_TYPE_AUTHENTICATION 134 
#define  IWI_NOTIF_TYPE_BEACON 133 
#define  IWI_NOTIF_TYPE_CALIBRATION 132 
#define  IWI_NOTIF_TYPE_LINK_QUALITY 131 
#define  IWI_NOTIF_TYPE_NOISE 130 
#define  IWI_NOTIF_TYPE_SCAN_CHANNEL 129 
#define  IWI_NOTIF_TYPE_SCAN_COMPLETE 128 
 int /*<<< orphan*/  IWI_SCAN_COMPLETED ; 
 int /*<<< orphan*/  IWI_STATE_END (struct iwi_softc*,int const) ; 
 struct ieee80211vap* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_ieee2mhz (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_new_state (struct ieee80211vap*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ieee80211_runtask (struct ieee80211com*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_scan_next (struct ieee80211vap*) ; 
 int /*<<< orphan*/  iwi_checkforqos (struct ieee80211vap*,struct ieee80211_frame const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwi_notif_link_quality (struct iwi_softc*,struct iwi_notif*) ; 
 int /*<<< orphan*/  le16toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32toh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
iwi_notification_intr(struct iwi_softc *sc, struct iwi_notif *notif)
{
	struct ieee80211com *ic = &sc->sc_ic;
	struct ieee80211vap *vap = TAILQ_FIRST(&ic->ic_vaps);
	struct iwi_notif_scan_channel *chan;
	struct iwi_notif_scan_complete *scan;
	struct iwi_notif_authentication *auth;
	struct iwi_notif_association *assoc;
	struct iwi_notif_beacon_state *beacon;

	switch (notif->type) {
	case IWI_NOTIF_TYPE_SCAN_CHANNEL:
		chan = (struct iwi_notif_scan_channel *)(notif + 1);

		DPRINTFN(3, ("Scan of channel %u complete (%u)\n",
		    ieee80211_ieee2mhz(chan->nchan, 0), chan->nchan));

		/* Reset the timer, the scan is still going */
		sc->sc_state_timer = 3;
		break;

	case IWI_NOTIF_TYPE_SCAN_COMPLETE:
		scan = (struct iwi_notif_scan_complete *)(notif + 1);

		DPRINTFN(2, ("Scan completed (%u, %u)\n", scan->nchan,
		    scan->status));

		IWI_STATE_END(sc, IWI_FW_SCANNING);

		/*
		 * Monitor mode works by doing a passive scan to set
		 * the channel and enable rx.  Because we don't want
		 * to abort a scan lest the firmware crash we scan
		 * for a short period of time and automatically restart
		 * the scan when notified the sweep has completed.
		 */
		if (vap->iv_opmode == IEEE80211_M_MONITOR) {
			ieee80211_runtask(ic, &sc->sc_monitortask);
			break;
		}

		if (scan->status == IWI_SCAN_COMPLETED) {
			/* NB: don't need to defer, net80211 does it for us */
			ieee80211_scan_next(vap);
		}
		break;

	case IWI_NOTIF_TYPE_AUTHENTICATION:
		auth = (struct iwi_notif_authentication *)(notif + 1);
		switch (auth->state) {
		case IWI_AUTH_SUCCESS:
			DPRINTFN(2, ("Authentication succeeeded\n"));
			ieee80211_new_state(vap, IEEE80211_S_ASSOC, -1);
			break;
		case IWI_AUTH_FAIL:
			/*
			 * These are delivered as an unsolicited deauth
			 * (e.g. due to inactivity) or in response to an
			 * associate request.
			 */
			sc->flags &= ~IWI_FLAG_ASSOCIATED;
			if (vap->iv_state != IEEE80211_S_RUN) {
				DPRINTFN(2, ("Authentication failed\n"));
				vap->iv_stats.is_rx_auth_fail++;
				IWI_STATE_END(sc, IWI_FW_ASSOCIATING);
			} else {
				DPRINTFN(2, ("Deauthenticated\n"));
				vap->iv_stats.is_rx_deauth++;
			}
			ieee80211_new_state(vap, IEEE80211_S_SCAN, -1);
			break;
		case IWI_AUTH_SENT_1:
		case IWI_AUTH_RECV_2:
		case IWI_AUTH_SEQ1_PASS:
			break;
		case IWI_AUTH_SEQ1_FAIL:
			DPRINTFN(2, ("Initial authentication handshake failed; "
				"you probably need shared key\n"));
			vap->iv_stats.is_rx_auth_fail++;
			IWI_STATE_END(sc, IWI_FW_ASSOCIATING);
			/* XXX retry shared key when in auto */
			break;
		default:
			device_printf(sc->sc_dev,
			    "unknown authentication state %u\n", auth->state);
			break;
		}
		break;

	case IWI_NOTIF_TYPE_ASSOCIATION:
		assoc = (struct iwi_notif_association *)(notif + 1);
		switch (assoc->state) {
		case IWI_AUTH_SUCCESS:
			/* re-association, do nothing */
			break;
		case IWI_ASSOC_SUCCESS:
			DPRINTFN(2, ("Association succeeded\n"));
			sc->flags |= IWI_FLAG_ASSOCIATED;
			IWI_STATE_END(sc, IWI_FW_ASSOCIATING);
			iwi_checkforqos(vap,
			    (const struct ieee80211_frame *)(assoc+1),
			    le16toh(notif->len) - sizeof(*assoc) - 1);
			ieee80211_new_state(vap, IEEE80211_S_RUN, -1);
			break;
		case IWI_ASSOC_INIT:
			sc->flags &= ~IWI_FLAG_ASSOCIATED;
			switch (sc->fw_state) {
			case IWI_FW_ASSOCIATING:
				DPRINTFN(2, ("Association failed\n"));
				IWI_STATE_END(sc, IWI_FW_ASSOCIATING);
				ieee80211_new_state(vap, IEEE80211_S_SCAN, -1);
				break;

			case IWI_FW_DISASSOCIATING:
				DPRINTFN(2, ("Dissassociated\n"));
				IWI_STATE_END(sc, IWI_FW_DISASSOCIATING);
				vap->iv_stats.is_rx_disassoc++;
				ieee80211_new_state(vap, IEEE80211_S_SCAN, -1);
				break;
			}
			break;
		default:
			device_printf(sc->sc_dev,
			    "unknown association state %u\n", assoc->state);
			break;
		}
		break;

	case IWI_NOTIF_TYPE_BEACON:
		/* XXX check struct length */
		beacon = (struct iwi_notif_beacon_state *)(notif + 1);

		DPRINTFN(5, ("Beacon state (%u, %u)\n",
		    beacon->state, le32toh(beacon->number)));

		if (beacon->state == IWI_BEACON_MISS) {
			/*
			 * The firmware notifies us of every beacon miss
			 * so we need to track the count against the
			 * configured threshold before notifying the
			 * 802.11 layer.
			 * XXX try to roam, drop assoc only on much higher count
			 */
			if (le32toh(beacon->number) >= vap->iv_bmissthreshold) {
				DPRINTF(("Beacon miss: %u >= %u\n",
				    le32toh(beacon->number),
				    vap->iv_bmissthreshold));
				vap->iv_stats.is_beacon_miss++;
				/*
				 * It's pointless to notify the 802.11 layer
				 * as it'll try to send a probe request (which
				 * we'll discard) and then timeout and drop us
				 * into scan state.  Instead tell the firmware
				 * to disassociate and then on completion we'll
				 * kick the state machine to scan.
				 */
				ieee80211_runtask(ic, &sc->sc_disassoctask);
			}
		}
		break;

	case IWI_NOTIF_TYPE_CALIBRATION:
	case IWI_NOTIF_TYPE_NOISE:
		/* XXX handle? */
		DPRINTFN(5, ("Notification (%u)\n", notif->type));
		break;
	case IWI_NOTIF_TYPE_LINK_QUALITY:
		iwi_notif_link_quality(sc, notif);
		break;

	default:
		DPRINTF(("unknown notification type %u flags 0x%x len %u\n",
		    notif->type, notif->flags, le16toh(notif->len)));
		break;
	}
}