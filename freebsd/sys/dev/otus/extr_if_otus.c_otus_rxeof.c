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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;
struct usb_xfer {int dummy; } ;
struct otus_softc {int dummy; } ;
struct otus_data {scalar_t__ buf; } ;
struct mbufq {int dummy; } ;
struct ar_rx_head {scalar_t__ tag; scalar_t__ len; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  AR_RX_HEAD_TAG ; 
 int /*<<< orphan*/  OTUS_DEBUG_RXDONE ; 
 int /*<<< orphan*/  OTUS_DPRINTF (struct otus_softc*,int /*<<< orphan*/ ,char*,int,...) ; 
 scalar_t__ __predict_false (int) ; 
 scalar_t__ htole16 (int /*<<< orphan*/ ) ; 
 int le16toh (scalar_t__) ; 
 int /*<<< orphan*/  otus_sub_rxeof (struct otus_softc*,int /*<<< orphan*/ *,int,struct mbufq*) ; 
 struct otus_softc* usbd_xfer_softc (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_status (struct usb_xfer*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
otus_rxeof(struct usb_xfer *xfer, struct otus_data *data, struct mbufq *rxq)
{
	struct otus_softc *sc = usbd_xfer_softc(xfer);
	caddr_t buf = data->buf;
	struct ar_rx_head *head;
	uint16_t hlen;
	int len;

	usbd_xfer_status(xfer, &len, NULL, NULL, NULL);

	while (len >= sizeof (*head)) {
		head = (struct ar_rx_head *)buf;
		if (__predict_false(head->tag != htole16(AR_RX_HEAD_TAG))) {
			OTUS_DPRINTF(sc, OTUS_DEBUG_RXDONE,
			    "tag not valid 0x%x\n", le16toh(head->tag));
			break;
		}
		hlen = le16toh(head->len);
		if (__predict_false(sizeof (*head) + hlen > len)) {
			OTUS_DPRINTF(sc, OTUS_DEBUG_RXDONE,
			    "xfer too short %d/%d\n", len, hlen);
			break;
		}
		/* Process sub-xfer. */
		otus_sub_rxeof(sc, (uint8_t *)&head[1], hlen, rxq);

		/* Next sub-xfer is aligned on a 32-bit boundary. */
		hlen = (sizeof (*head) + hlen + 3) & ~3;
		buf += hlen;
		len -= hlen;
	}
}