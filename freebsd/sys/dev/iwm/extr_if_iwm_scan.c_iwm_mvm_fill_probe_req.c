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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint16_t ;
struct ieee80211com {int ic_flags; struct ieee80211_rateset* ic_sup_rates; int /*<<< orphan*/  ic_macaddr; int /*<<< orphan*/  ic_vaps; } ;
struct iwm_softc {TYPE_2__* nvm_data; struct ieee80211com sc_ic; } ;
struct TYPE_8__ {void* len; void* offset; } ;
struct TYPE_5__ {void* len; scalar_t__ offset; } ;
struct iwm_scan_probe_req {TYPE_4__ common_data; TYPE_3__* band_data; TYPE_1__ mac_header; scalar_t__ buf; } ;
struct ieee80211vap {int /*<<< orphan*/  iv_myaddr; } ;
struct ieee80211_rateset {int rs_nrates; } ;
struct ieee80211_frame {int* i_fc; int /*<<< orphan*/ * i_seq; int /*<<< orphan*/ * i_dur; int /*<<< orphan*/  i_addr3; int /*<<< orphan*/  i_addr2; int /*<<< orphan*/  i_addr1; } ;
struct TYPE_7__ {void* len; void* offset; } ;
struct TYPE_6__ {scalar_t__ sku_cap_band_52GHz_enable; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int /*<<< orphan*/  IEEE80211_ADDR_COPY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IEEE80211_ELEMID_DSPARMS ; 
 int IEEE80211_FC0_SUBTYPE_PROBE_REQ ; 
 int IEEE80211_FC0_TYPE_MGT ; 
 int IEEE80211_FC0_VERSION_0 ; 
 int IEEE80211_FC1_DIR_NODS ; 
 int IEEE80211_F_HTON ; 
 size_t IEEE80211_MODE_11A ; 
 size_t IEEE80211_MODE_11G ; 
 int IEEE80211_RATE_SIZE ; 
 struct ieee80211vap* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 void* htole16 (int) ; 
 int /*<<< orphan*/ * ieee80211_add_htcaps (int /*<<< orphan*/ *,struct ieee80211com*) ; 
 int /*<<< orphan*/ * ieee80211_add_rates (int /*<<< orphan*/ *,struct ieee80211_rateset*) ; 
 int /*<<< orphan*/ * ieee80211_add_ssid (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ieee80211_add_xrates (int /*<<< orphan*/ *,struct ieee80211_rateset*) ; 
 int /*<<< orphan*/  ieee80211broadcastaddr ; 
 scalar_t__ iwm_mvm_rrm_scan_needed (struct iwm_softc*) ; 
 int /*<<< orphan*/  memset (struct iwm_scan_probe_req*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
iwm_mvm_fill_probe_req(struct iwm_softc *sc, struct iwm_scan_probe_req *preq)
{
	struct ieee80211com *ic = &sc->sc_ic;
	struct ieee80211vap *vap = TAILQ_FIRST(&ic->ic_vaps);
	struct ieee80211_frame *wh = (struct ieee80211_frame *)preq->buf;
	struct ieee80211_rateset *rs;
	size_t remain = sizeof(preq->buf);
	uint8_t *frm, *pos;

	memset(preq, 0, sizeof(*preq));

	/* Ensure enough space for header and SSID IE. */
	if (remain < sizeof(*wh) + 2)
		return ENOBUFS;

	/*
	 * Build a probe request frame.  Most of the following code is a
	 * copy & paste of what is done in net80211.
	 */
	wh->i_fc[0] = IEEE80211_FC0_VERSION_0 | IEEE80211_FC0_TYPE_MGT |
	    IEEE80211_FC0_SUBTYPE_PROBE_REQ;
	wh->i_fc[1] = IEEE80211_FC1_DIR_NODS;
	IEEE80211_ADDR_COPY(wh->i_addr1, ieee80211broadcastaddr);
	IEEE80211_ADDR_COPY(wh->i_addr2, vap ? vap->iv_myaddr : ic->ic_macaddr);
	IEEE80211_ADDR_COPY(wh->i_addr3, ieee80211broadcastaddr);
	*(uint16_t *)&wh->i_dur[0] = 0; /* filled by HW */
	*(uint16_t *)&wh->i_seq[0] = 0; /* filled by HW */

	frm = (uint8_t *)(wh + 1);
	frm = ieee80211_add_ssid(frm, NULL, 0);

	/* Tell the firmware where the MAC header is. */
	preq->mac_header.offset = 0;
	preq->mac_header.len = htole16(frm - (uint8_t *)wh);
	remain -= frm - (uint8_t *)wh;

	/* Fill in 2GHz IEs and tell firmware where they are. */
	rs = &ic->ic_sup_rates[IEEE80211_MODE_11G];
	if (rs->rs_nrates > IEEE80211_RATE_SIZE) {
		if (remain < 4 + rs->rs_nrates)
			return ENOBUFS;
	} else if (remain < 2 + rs->rs_nrates) {
		return ENOBUFS;
	}
	preq->band_data[0].offset = htole16(frm - (uint8_t *)wh);
	pos = frm;
	frm = ieee80211_add_rates(frm, rs);
	if (rs->rs_nrates > IEEE80211_RATE_SIZE)
		frm = ieee80211_add_xrates(frm, rs);
	preq->band_data[0].len = htole16(frm - pos);
	remain -= frm - pos;

	if (iwm_mvm_rrm_scan_needed(sc)) {
		if (remain < 3)
			return ENOBUFS;
		*frm++ = IEEE80211_ELEMID_DSPARMS;
		*frm++ = 1;
		*frm++ = 0;
		remain -= 3;
	}

	if (sc->nvm_data->sku_cap_band_52GHz_enable) {
		/* Fill in 5GHz IEs. */
		rs = &ic->ic_sup_rates[IEEE80211_MODE_11A];
		if (rs->rs_nrates > IEEE80211_RATE_SIZE) {
			if (remain < 4 + rs->rs_nrates)
				return ENOBUFS;
		} else if (remain < 2 + rs->rs_nrates) {
			return ENOBUFS;
		}
		preq->band_data[1].offset = htole16(frm - (uint8_t *)wh);
		pos = frm;
		frm = ieee80211_add_rates(frm, rs);
		if (rs->rs_nrates > IEEE80211_RATE_SIZE)
			frm = ieee80211_add_xrates(frm, rs);
		preq->band_data[1].len = htole16(frm - pos);
		remain -= frm - pos;
	}

	/* Send 11n IEs on both 2GHz and 5GHz bands. */
	preq->common_data.offset = htole16(frm - (uint8_t *)wh);
	pos = frm;
#if 0
	if (ic->ic_flags & IEEE80211_F_HTON) {
		if (remain < 28)
			return ENOBUFS;
		frm = ieee80211_add_htcaps(frm, ic);
		/* XXX add WME info? */
	}
#endif
	preq->common_data.len = htole16(frm - pos);

	return 0;
}