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
struct vmbus_channel {int dummy; } ;
struct hn_softc {int /*<<< orphan*/  hn_prichan; } ;

/* Variables and functions */
 int /*<<< orphan*/  pause (char*,int) ; 
 int /*<<< orphan*/  vmbus_chan_intr_drain (struct vmbus_channel*) ; 
 int /*<<< orphan*/  vmbus_chan_is_revoked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmbus_chan_rx_empty (struct vmbus_channel*) ; 
 int /*<<< orphan*/  vmbus_chan_tx_empty (struct vmbus_channel*) ; 

__attribute__((used)) static void
hn_chan_drain(struct hn_softc *sc, struct vmbus_channel *chan)
{

	/*
	 * NOTE:
	 * The TX bufring will not be drained by the hypervisor,
	 * if the primary channel is revoked.
	 */
	while (!vmbus_chan_rx_empty(chan) ||
	    (!vmbus_chan_is_revoked(sc->hn_prichan) &&
	     !vmbus_chan_tx_empty(chan)))
		pause("waitch", 1);
	vmbus_chan_intr_drain(chan);
}