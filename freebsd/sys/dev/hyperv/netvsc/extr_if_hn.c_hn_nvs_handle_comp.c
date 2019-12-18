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
struct vmbus_chanpkt_hdr {scalar_t__ cph_xactid; } ;
struct vmbus_channel {int dummy; } ;
struct hn_softc {int dummy; } ;
struct hn_nvs_sendctx {int /*<<< orphan*/  (* hn_cb ) (struct hn_nvs_sendctx*,struct hn_softc*,struct vmbus_channel*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  VMBUS_CHANPKT_CONST_DATA (struct vmbus_chanpkt_hdr const*) ; 
 int /*<<< orphan*/  VMBUS_CHANPKT_DATALEN (struct vmbus_chanpkt_hdr const*) ; 
 int /*<<< orphan*/  stub1 (struct hn_nvs_sendctx*,struct hn_softc*,struct vmbus_channel*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
hn_nvs_handle_comp(struct hn_softc *sc, struct vmbus_channel *chan,
    const struct vmbus_chanpkt_hdr *pkt)
{
	struct hn_nvs_sendctx *sndc;

	sndc = (struct hn_nvs_sendctx *)(uintptr_t)pkt->cph_xactid;
	sndc->hn_cb(sndc, sc, chan, VMBUS_CHANPKT_CONST_DATA(pkt),
	    VMBUS_CHANPKT_DATALEN(pkt));
	/*
	 * NOTE:
	 * 'sndc' CAN NOT be accessed anymore, since it can be freed by
	 * its callback.
	 */
}