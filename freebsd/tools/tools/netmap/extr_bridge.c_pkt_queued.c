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
typedef  scalar_t__ u_int ;
struct nm_desc {scalar_t__ first_tx_ring; scalar_t__ last_tx_ring; scalar_t__ first_rx_ring; scalar_t__ last_rx_ring; int /*<<< orphan*/  nifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETMAP_RXRING (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  NETMAP_TXRING (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ nm_ring_space (int /*<<< orphan*/ ) ; 

int
pkt_queued(struct nm_desc *d, int tx)
{
	u_int i, tot = 0;

	if (tx) {
		for (i = d->first_tx_ring; i <= d->last_tx_ring; i++) {
			tot += nm_ring_space(NETMAP_TXRING(d->nifp, i));
		}
	} else {
		for (i = d->first_rx_ring; i <= d->last_rx_ring; i++) {
			tot += nm_ring_space(NETMAP_RXRING(d->nifp, i));
		}
	}
	return tot;
}