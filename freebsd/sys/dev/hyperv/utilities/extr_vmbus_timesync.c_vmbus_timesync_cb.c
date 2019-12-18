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
struct vmbus_icmsg_timesync4 {int /*<<< orphan*/  ic_tsflags; int /*<<< orphan*/  ic_sent_tc; int /*<<< orphan*/  ic_hvtime; } ;
struct vmbus_icmsg_timesync {int /*<<< orphan*/  ic_tsflags; int /*<<< orphan*/  ic_hvtime; } ;
struct vmbus_icmsg_hdr {int ic_type; } ;
struct vmbus_ic_softc {int ic_buflen; int /*<<< orphan*/  ic_dev; void* ic_buf; } ;
struct vmbus_channel {int dummy; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
#define  VMBUS_ICMSG_TYPE_NEGOTIATE 129 
#define  VMBUS_ICMSG_TYPE_TIMESYNC 128 
 int /*<<< orphan*/  VMBUS_TIMESYNC_DORTT (struct vmbus_ic_softc*) ; 
 int /*<<< orphan*/  VMBUS_TIMESYNC_FWVER ; 
 int /*<<< orphan*/  VMBUS_TIMESYNC_MSGVER ; 
 int /*<<< orphan*/  VMBUS_TIMESYNC_MSGVER4 (struct vmbus_ic_softc*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int vmbus_chan_recv (struct vmbus_channel*,void*,int*,int /*<<< orphan*/ *) ; 
 int vmbus_ic_negomsg (struct vmbus_ic_softc*,void*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmbus_ic_sendresp (struct vmbus_ic_softc*,struct vmbus_channel*,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmbus_timesync (struct vmbus_ic_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vmbus_timesync_cb(struct vmbus_channel *chan, void *xsc)
{
	struct vmbus_ic_softc *sc = xsc;
	struct vmbus_icmsg_hdr *hdr;
	int dlen, error;
	uint64_t xactid;
	void *data;

	/*
	 * Receive request.
	 */
	data = sc->ic_buf;
	dlen = sc->ic_buflen;
	error = vmbus_chan_recv(chan, data, &dlen, &xactid);
	KASSERT(error != ENOBUFS, ("icbuf is not large enough"));
	if (error)
		return;

	if (dlen < sizeof(*hdr)) {
		device_printf(sc->ic_dev, "invalid data len %d\n", dlen);
		return;
	}
	hdr = data;

	/*
	 * Update request, which will be echoed back as response.
	 */
	switch (hdr->ic_type) {
	case VMBUS_ICMSG_TYPE_NEGOTIATE:
		error = vmbus_ic_negomsg(sc, data, &dlen,
		    VMBUS_TIMESYNC_FWVER, VMBUS_TIMESYNC_MSGVER);
		if (error)
			return;
		if (VMBUS_TIMESYNC_DORTT(sc))
			device_printf(sc->ic_dev, "RTT\n");
		break;

	case VMBUS_ICMSG_TYPE_TIMESYNC:
		if (VMBUS_TIMESYNC_MSGVER4(sc)) {
			const struct vmbus_icmsg_timesync4 *msg4;

			if (dlen < sizeof(*msg4)) {
				device_printf(sc->ic_dev, "invalid timesync4 "
				    "len %d\n", dlen);
				return;
			}
			msg4 = data;
			vmbus_timesync(sc, msg4->ic_hvtime, msg4->ic_sent_tc,
			    msg4->ic_tsflags);
		} else {
			const struct vmbus_icmsg_timesync *msg;

			if (dlen < sizeof(*msg)) {
				device_printf(sc->ic_dev, "invalid timesync "
				    "len %d\n", dlen);
				return;
			}
			msg = data;
			vmbus_timesync(sc, msg->ic_hvtime, 0, msg->ic_tsflags);
		}
		break;

	default:
		device_printf(sc->ic_dev, "got 0x%08x icmsg\n", hdr->ic_type);
		break;
	}

	/*
	 * Send response by echoing the request back.
	 */
	vmbus_ic_sendresp(sc, chan, data, dlen, xactid);
}