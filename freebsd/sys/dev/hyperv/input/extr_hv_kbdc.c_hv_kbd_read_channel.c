#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct vmbus_chanpkt_hdr {int cph_type; } ;
struct vmbus_channel {int dummy; } ;
struct TYPE_4__ {scalar_t__ buflen; int /*<<< orphan*/  dev; int /*<<< orphan*/ * buf; } ;
typedef  TYPE_1__ hv_kbd_sc ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_HVSC (TYPE_1__*,char*,int) ; 
 int EAGAIN ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
#define  VMBUS_CHANPKT_TYPE_COMP 130 
#define  VMBUS_CHANPKT_TYPE_INBAND 129 
#define  VMBUS_CHANPKT_TYPE_RXBUF 128 
 scalar_t__ __predict_false (int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hv_kbd_on_received (TYPE_1__*,struct vmbus_chanpkt_hdr*) ; 
 int /*<<< orphan*/ * malloc (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int vmbus_chan_recv_pkt (struct vmbus_channel*,struct vmbus_chanpkt_hdr*,scalar_t__*) ; 

void 
hv_kbd_read_channel(struct vmbus_channel *channel, void *context)
{
	uint8_t *buf;
	uint32_t buflen = 0;
	int ret = 0;

	hv_kbd_sc *sc = (hv_kbd_sc*)context;
	buf = sc->buf;
	buflen = sc->buflen;
	for (;;) {
		struct vmbus_chanpkt_hdr *pkt = (struct vmbus_chanpkt_hdr *)buf;
		uint32_t rxed = buflen;

		ret = vmbus_chan_recv_pkt(channel, pkt, &rxed);
		if (__predict_false(ret == ENOBUFS)) {
			buflen = sc->buflen * 2;
			while (buflen < rxed)
				buflen *= 2;
			buf = malloc(buflen, M_DEVBUF, M_WAITOK | M_ZERO);
			device_printf(sc->dev, "expand recvbuf %d -> %d\n",
			    sc->buflen, buflen);
			free(sc->buf, M_DEVBUF);
			sc->buf = buf;
			sc->buflen = buflen;
			continue;
		} else if (__predict_false(ret == EAGAIN)) {
			/* No more channel packets; done! */
			break;
		}
		KASSERT(!ret, ("vmbus_chan_recv_pkt failed: %d", ret));

		DEBUG_HVSC(sc, "event: 0x%x\n", pkt->cph_type);
		switch (pkt->cph_type) {
		case VMBUS_CHANPKT_TYPE_COMP:
		case VMBUS_CHANPKT_TYPE_RXBUF:
			device_printf(sc->dev, "unhandled event: %d\n",
			    pkt->cph_type);
			break;
		case VMBUS_CHANPKT_TYPE_INBAND:
			hv_kbd_on_received(sc, pkt);
			break;
		default:
			device_printf(sc->dev, "unknown event: %d\n",
			    pkt->cph_type);
			break;
		}
	}
}