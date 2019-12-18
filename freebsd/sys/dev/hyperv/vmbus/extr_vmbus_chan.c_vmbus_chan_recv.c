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
typedef  int /*<<< orphan*/  uint64_t ;
struct vmbus_chanpkt_hdr {scalar_t__ cph_hlen; scalar_t__ cph_tlen; int /*<<< orphan*/  cph_xactid; } ;
struct vmbus_channel {int /*<<< orphan*/  ch_rxbr; } ;
typedef  int /*<<< orphan*/  pkt ;

/* Variables and functions */
 int EIO ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int VMBUS_CHANPKT_GETLEN (scalar_t__) ; 
 scalar_t__ VMBUS_CHANPKT_HLEN_MIN ; 
 scalar_t__ __predict_false (int) ; 
 int /*<<< orphan*/  vmbus_chan_printf (struct vmbus_channel*,char*,scalar_t__,...) ; 
 int vmbus_rxbr_peek (int /*<<< orphan*/ *,struct vmbus_chanpkt_hdr*,int) ; 
 int vmbus_rxbr_read (int /*<<< orphan*/ *,void*,int,int) ; 

int
vmbus_chan_recv(struct vmbus_channel *chan, void *data, int *dlen0,
    uint64_t *xactid)
{
	struct vmbus_chanpkt_hdr pkt;
	int error, dlen, hlen;

	error = vmbus_rxbr_peek(&chan->ch_rxbr, &pkt, sizeof(pkt));
	if (error)
		return (error);

	if (__predict_false(pkt.cph_hlen < VMBUS_CHANPKT_HLEN_MIN)) {
		vmbus_chan_printf(chan, "invalid hlen %u\n", pkt.cph_hlen);
		/* XXX this channel is dead actually. */
		return (EIO);
	}
	if (__predict_false(pkt.cph_hlen > pkt.cph_tlen)) {
		vmbus_chan_printf(chan, "invalid hlen %u and tlen %u\n",
		    pkt.cph_hlen, pkt.cph_tlen);
		/* XXX this channel is dead actually. */
		return (EIO);
	}

	hlen = VMBUS_CHANPKT_GETLEN(pkt.cph_hlen);
	dlen = VMBUS_CHANPKT_GETLEN(pkt.cph_tlen) - hlen;

	if (*dlen0 < dlen) {
		/* Return the size of this packet's data. */
		*dlen0 = dlen;
		return (ENOBUFS);
	}

	*xactid = pkt.cph_xactid;
	*dlen0 = dlen;

	/* Skip packet header */
	error = vmbus_rxbr_read(&chan->ch_rxbr, data, dlen, hlen);
	KASSERT(!error, ("vmbus_rxbr_read failed"));

	return (0);
}