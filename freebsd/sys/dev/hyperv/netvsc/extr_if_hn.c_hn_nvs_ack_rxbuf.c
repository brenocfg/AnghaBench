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
struct vmbus_channel {int dummy; } ;
struct hn_rx_ring {scalar_t__ hn_ack_failed; int /*<<< orphan*/  hn_ifp; } ;
struct hn_nvs_rndis_ack {int /*<<< orphan*/  nvs_status; int /*<<< orphan*/  nvs_type; } ;
typedef  int /*<<< orphan*/  ack ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int EAGAIN ; 
 int /*<<< orphan*/  HN_NVS_STATUS_OK ; 
 int /*<<< orphan*/  HN_NVS_TYPE_RNDIS_ACK ; 
 int /*<<< orphan*/  VMBUS_CHANPKT_FLAG_NONE ; 
 int /*<<< orphan*/  VMBUS_CHANPKT_TYPE_COMP ; 
 scalar_t__ __predict_false (int) ; 
 int /*<<< orphan*/  if_printf (int /*<<< orphan*/ ,char*) ; 
 int vmbus_chan_send (struct vmbus_channel*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hn_nvs_rndis_ack*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
hn_nvs_ack_rxbuf(struct hn_rx_ring *rxr, struct vmbus_channel *chan,
    uint64_t tid)
{
	struct hn_nvs_rndis_ack ack;
	int retries, error;
	
	ack.nvs_type = HN_NVS_TYPE_RNDIS_ACK;
	ack.nvs_status = HN_NVS_STATUS_OK;

	retries = 0;
again:
	error = vmbus_chan_send(chan, VMBUS_CHANPKT_TYPE_COMP,
	    VMBUS_CHANPKT_FLAG_NONE, &ack, sizeof(ack), tid);
	if (__predict_false(error == EAGAIN)) {
		/*
		 * NOTE:
		 * This should _not_ happen in real world, since the
		 * consumption of the TX bufring from the TX path is
		 * controlled.
		 */
		if (rxr->hn_ack_failed == 0)
			if_printf(rxr->hn_ifp, "RXBUF ack retry\n");
		rxr->hn_ack_failed++;
		retries++;
		if (retries < 10) {
			DELAY(100);
			goto again;
		}
		/* RXBUF leaks! */
		if_printf(rxr->hn_ifp, "RXBUF ack failed\n");
	}
}