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
struct vmbus_icmsg_hdr {int ic_flags; } ;
struct vmbus_ic_softc {int /*<<< orphan*/  ic_dev; } ;
struct vmbus_channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  VMBUS_CHANPKT_TYPE_INBAND ; 
 int VMBUS_ICMSG_FLAG_RESP ; 
 int VMBUS_ICMSG_FLAG_XACT ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int vmbus_chan_send (struct vmbus_channel*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ) ; 

int
vmbus_ic_sendresp(struct vmbus_ic_softc *sc, struct vmbus_channel *chan,
    void *data, int dlen, uint64_t xactid)
{
	struct vmbus_icmsg_hdr *hdr;
	int error;

	KASSERT(dlen >= sizeof(*hdr), ("invalid data length %d", dlen));
	hdr = data;

	hdr->ic_flags = VMBUS_ICMSG_FLAG_XACT | VMBUS_ICMSG_FLAG_RESP;
	error = vmbus_chan_send(chan, VMBUS_CHANPKT_TYPE_INBAND, 0,
	    data, dlen, xactid);
	if (error)
		device_printf(sc->ic_dev, "resp send failed: %d\n", error);
	return (error);
}