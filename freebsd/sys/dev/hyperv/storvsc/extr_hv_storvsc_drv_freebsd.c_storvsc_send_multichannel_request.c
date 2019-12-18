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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_2__ {int multi_channels_cnt; } ;
struct vstor_packet {scalar_t__ operation; scalar_t__ status; TYPE_1__ u; int /*<<< orphan*/  flags; } ;
struct vmbus_channel {int dummy; } ;
struct hv_storvsc_request {int /*<<< orphan*/  synch_sema; struct vstor_packet vstor_packet; } ;
struct storvsc_softc {int hs_nchan; int /*<<< orphan*/  hs_chan; struct hv_storvsc_request hs_init_req; } ;

/* Variables and functions */
 int MIN (int,scalar_t__) ; 
 int /*<<< orphan*/  REQUEST_COMPLETION_FLAG ; 
 int /*<<< orphan*/  VMBUS_CHANPKT_FLAG_RC ; 
 int /*<<< orphan*/  VMBUS_CHANPKT_TYPE_INBAND ; 
 scalar_t__ VSTOR_OPERATION_COMPLETEIO ; 
 scalar_t__ VSTOR_OPERATION_CREATE_MULTI_CHANNELS ; 
 int /*<<< orphan*/  VSTOR_PKT_SIZE ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  memset (struct hv_storvsc_request*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mp_ncpus ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sema_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sema_wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  storvsc_subchan_attach (struct storvsc_softc*,struct vmbus_channel*) ; 
 int vmbus_chan_send (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vstor_packet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vmbus_channel** vmbus_subchan_get (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vmbus_subchan_rel (struct vmbus_channel**,int) ; 

__attribute__((used)) static void
storvsc_send_multichannel_request(struct storvsc_softc *sc, int max_subch)
{
	struct vmbus_channel **subchan;
	struct hv_storvsc_request *request;
	struct vstor_packet *vstor_packet;	
	int request_subch;
	int ret, i;

	/* get sub-channel count that need to create */
	request_subch = MIN(max_subch, mp_ncpus - 1);

	request = &sc->hs_init_req;

	/* request the host to create multi-channel */
	memset(request, 0, sizeof(struct hv_storvsc_request));
	
	sema_init(&request->synch_sema, 0, ("stor_synch_sema"));

	vstor_packet = &request->vstor_packet;
	
	vstor_packet->operation = VSTOR_OPERATION_CREATE_MULTI_CHANNELS;
	vstor_packet->flags = REQUEST_COMPLETION_FLAG;
	vstor_packet->u.multi_channels_cnt = request_subch;

	ret = vmbus_chan_send(sc->hs_chan,
	    VMBUS_CHANPKT_TYPE_INBAND, VMBUS_CHANPKT_FLAG_RC,
	    vstor_packet, VSTOR_PKT_SIZE, (uint64_t)(uintptr_t)request);

	sema_wait(&request->synch_sema);

	if (vstor_packet->operation != VSTOR_OPERATION_COMPLETEIO ||
	    vstor_packet->status != 0) {		
		printf("Storvsc_error: create multi-channel invalid operation "
		    "(%d) or statue (%u)\n",
		    vstor_packet->operation, vstor_packet->status);
		return;
	}

	/* Update channel count */
	sc->hs_nchan = request_subch + 1;

	/* Wait for sub-channels setup to complete. */
	subchan = vmbus_subchan_get(sc->hs_chan, request_subch);

	/* Attach the sub-channels. */
	for (i = 0; i < request_subch; ++i)
		storvsc_subchan_attach(sc, subchan[i]);

	/* Release the sub-channels. */
	vmbus_subchan_rel(subchan, request_subch);

	if (bootverbose)
		printf("Storvsc create multi-channel success!\n");
}