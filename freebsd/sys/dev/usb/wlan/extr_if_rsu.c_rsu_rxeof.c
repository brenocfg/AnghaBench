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
struct usb_xfer {int dummy; } ;
struct ieee80211com {int /*<<< orphan*/  ic_ierrors; } ;
struct rsu_softc {struct ieee80211com sc_ic; } ;
struct rsu_data {scalar_t__ buf; struct rsu_softc* sc; } ;
struct r92s_rx_stat {int /*<<< orphan*/  rxdw1; } ;
struct mbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RSU_DEBUG_RX ; 
 int /*<<< orphan*/  RSU_DPRINTF (struct rsu_softc*,int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ __predict_false (int) ; 
 int /*<<< orphan*/  counter_u64_add (int /*<<< orphan*/ ,int) ; 
 int le32toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsu_rx_multi_event (struct rsu_softc*,scalar_t__,int) ; 
 struct mbuf* rsu_rx_multi_frame (struct rsu_softc*,scalar_t__,int) ; 
 int /*<<< orphan*/  usbd_xfer_status (struct usb_xfer*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct mbuf *
rsu_rxeof(struct usb_xfer *xfer, struct rsu_data *data)
{
	struct rsu_softc *sc = data->sc;
	struct ieee80211com *ic = &sc->sc_ic;
	struct r92s_rx_stat *stat;
	int len;

	usbd_xfer_status(xfer, &len, NULL, NULL, NULL);

	if (__predict_false(len < sizeof(*stat))) {
		RSU_DPRINTF(sc, RSU_DEBUG_RX, "xfer too short %d\n", len);
		counter_u64_add(ic->ic_ierrors, 1);
		return (NULL);
	}
	/* Determine if it is a firmware C2H event or an 802.11 frame. */
	stat = (struct r92s_rx_stat *)data->buf;
	if ((le32toh(stat->rxdw1) & 0x1ff) == 0x1ff) {
		rsu_rx_multi_event(sc, data->buf, len);
		/* No packets to process. */
		return (NULL);
	} else
		return (rsu_rx_multi_frame(sc, data->buf, len));
}