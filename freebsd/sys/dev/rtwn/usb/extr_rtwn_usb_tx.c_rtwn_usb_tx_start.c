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
typedef  int uint8_t ;
typedef  size_t uint16_t ;
struct usb_xfer {int dummy; } ;
struct rtwn_usb_softc {int /*<<< orphan*/  uc_tx_inactive; int /*<<< orphan*/  uc_tx_pending; struct usb_xfer** uc_xfer; } ;
struct rtwn_tx_desc_common {scalar_t__ offset; int /*<<< orphan*/  flags0; int /*<<< orphan*/  pktlen; } ;
struct rtwn_softc {scalar_t__ txdesc_len; int sc_tx_timer; int qfullmsk; } ;
struct rtwn_data {scalar_t__ buf; scalar_t__ buflen; int id; struct mbuf* m; struct ieee80211_node* ni; } ;
struct TYPE_2__ {scalar_t__ len; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;
struct ieee80211_node {int dummy; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOBUFS ; 
#define  IEEE80211_FC0_TYPE_CTL 129 
#define  IEEE80211_FC0_TYPE_MGT 128 
 size_t M_WME_GETAC (struct mbuf*) ; 
 int /*<<< orphan*/  RTWN_ASSERT_LOCKED (struct rtwn_softc*) ; 
 size_t RTWN_BULK_TX_VO ; 
 int /*<<< orphan*/  RTWN_FLAGS0_OWN ; 
 struct rtwn_usb_softc* RTWN_USB_SOFTC (struct rtwn_softc*) ; 
 scalar_t__ RTWN_USB_TXBUFSZ ; 
 scalar_t__ STAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct rtwn_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htole16 (scalar_t__) ; 
 int /*<<< orphan*/  m_copydata (struct mbuf*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int*,scalar_t__) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  rtwn_dump_tx_desc (struct rtwn_softc*,int*) ; 
 struct rtwn_data* rtwn_usb_getbuf (struct rtwn_usb_softc*) ; 
 int /*<<< orphan*/  rtwn_usb_tx_checksum (struct rtwn_tx_desc_common*) ; 
 int /*<<< orphan*/  usbd_transfer_start (struct usb_xfer*) ; 
 size_t* wme2qid ; 

int
rtwn_usb_tx_start(struct rtwn_softc *sc, struct ieee80211_node *ni,
    struct mbuf *m, uint8_t *tx_desc, uint8_t type, int id)
{
	struct rtwn_usb_softc *uc = RTWN_USB_SOFTC(sc);
	struct rtwn_tx_desc_common *txd;
	struct rtwn_data *data;
	struct usb_xfer *xfer;
	uint16_t ac;

	RTWN_ASSERT_LOCKED(sc);

	if (m->m_pkthdr.len + sc->txdesc_len > RTWN_USB_TXBUFSZ)
		return (EINVAL);

	data = rtwn_usb_getbuf(uc);
	if (data == NULL)
		return (ENOBUFS);

	ac = M_WME_GETAC(m);

	switch (type) {
	case IEEE80211_FC0_TYPE_CTL:
	case IEEE80211_FC0_TYPE_MGT:
		xfer = uc->uc_xfer[RTWN_BULK_TX_VO];
		break;
	default:
		xfer = uc->uc_xfer[wme2qid[ac]];
		break;
	}

	txd = (struct rtwn_tx_desc_common *)tx_desc;
	txd->pktlen = htole16(m->m_pkthdr.len);
	txd->offset = sc->txdesc_len;
	txd->flags0 |= RTWN_FLAGS0_OWN;
	rtwn_usb_tx_checksum(txd);

	/* Dump Tx descriptor. */
	rtwn_dump_tx_desc(sc, tx_desc);

	memcpy(data->buf, tx_desc, sc->txdesc_len);
	m_copydata(m, 0, m->m_pkthdr.len,
	    (caddr_t)(data->buf + sc->txdesc_len));

	data->buflen = m->m_pkthdr.len + sc->txdesc_len;
	data->id = id;
	data->ni = ni;
	if (data->ni != NULL) {
		data->m = m;
#ifndef D4054
		sc->sc_tx_timer = 5;
#endif
	}

	STAILQ_INSERT_TAIL(&uc->uc_tx_pending, data, next);
	if (STAILQ_EMPTY(&uc->uc_tx_inactive))
		sc->qfullmsk = 1;

	usbd_transfer_start(xfer);

	return (0);
}