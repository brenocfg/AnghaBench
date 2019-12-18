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
typedef  int /*<<< orphan*/  uint8_t ;
struct rtwn_vap {int /*<<< orphan*/  id; } ;
struct rtwn_tx_desc_common {int offset; void* pktlen; } ;
struct ieee80211com {scalar_t__ ic_curmode; } ;
struct rtwn_softc {int txdesc_len; struct ieee80211com sc_ic; } ;
struct ieee80211vap {TYPE_1__* iv_bss; int /*<<< orphan*/  iv_myaddr; } ;
struct ieee80211_qosframe {int* i_qos; int /*<<< orphan*/ * i_fc; } ;
struct ieee80211_frame {int* i_fc; int /*<<< orphan*/  i_addr3; int /*<<< orphan*/  i_addr2; int /*<<< orphan*/  i_addr1; } ;
struct TYPE_2__ {int /*<<< orphan*/  ni_macaddr; int /*<<< orphan*/  ni_bssid; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_ADDR_COPY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IEEE80211_FC0_SUBTYPE_NODATA ; 
 int /*<<< orphan*/  IEEE80211_FC0_SUBTYPE_QOS_NULL ; 
 int IEEE80211_FC0_TYPE_DATA ; 
 int IEEE80211_FC0_VERSION_0 ; 
 int IEEE80211_FC1_DIR_TODS ; 
 scalar_t__ IEEE80211_MODE_11B ; 
 int const IEEE80211_QOS_TID ; 
 struct rtwn_vap* RTWN_VAP (struct ieee80211vap*) ; 
 int /*<<< orphan*/  WME_AC_BE ; 
 int WME_AC_TO_TID (int /*<<< orphan*/ ) ; 
 void* htole16 (int) ; 
 int /*<<< orphan*/  rtwn_fill_tx_desc_null (struct rtwn_softc*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
rtwn_construct_nulldata(struct rtwn_softc *sc, struct ieee80211vap *vap,
    uint8_t *ptr, int qos)
{
	struct rtwn_vap *uvp = RTWN_VAP(vap);
	struct ieee80211com *ic = &sc->sc_ic;
	struct rtwn_tx_desc_common *txd;
	struct ieee80211_frame *wh;
	int pktlen;

	/* XXX obtain from net80211 */
	wh = (struct ieee80211_frame *)(ptr + sc->txdesc_len);
	wh->i_fc[0] = IEEE80211_FC0_VERSION_0 | IEEE80211_FC0_TYPE_DATA;
	wh->i_fc[1] = IEEE80211_FC1_DIR_TODS;
	IEEE80211_ADDR_COPY(wh->i_addr1, vap->iv_bss->ni_bssid);
	IEEE80211_ADDR_COPY(wh->i_addr2, vap->iv_myaddr);
	IEEE80211_ADDR_COPY(wh->i_addr3, vap->iv_bss->ni_macaddr);

	txd = (struct rtwn_tx_desc_common *)ptr;
	txd->offset = sc->txdesc_len;
	pktlen = sc->txdesc_len;
	if (qos) {
		struct ieee80211_qosframe *qwh;
		const int tid = WME_AC_TO_TID(WME_AC_BE);

		qwh = (struct ieee80211_qosframe *)wh;
		qwh->i_fc[0] |= IEEE80211_FC0_SUBTYPE_QOS_NULL;
		qwh->i_qos[0] = tid & IEEE80211_QOS_TID;

		txd->pktlen = htole16(sizeof(struct ieee80211_qosframe));
		pktlen += sizeof(struct ieee80211_qosframe);
	} else {
		wh->i_fc[0] |= IEEE80211_FC0_SUBTYPE_NODATA;

		txd->pktlen = htole16(sizeof(struct ieee80211_frame));
		pktlen += sizeof(struct ieee80211_frame);
	}

	rtwn_fill_tx_desc_null(sc, ptr,
	    ic->ic_curmode == IEEE80211_MODE_11B, qos, uvp->id);

	return (pktlen);
}