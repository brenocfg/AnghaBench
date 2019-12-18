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
typedef  scalar_t__ u_int ;
struct TYPE_2__ {scalar_t__ nr_flags; } ;
struct nm_desc {scalar_t__ first_rx_ring; scalar_t__ first_tx_ring; scalar_t__ last_rx_ring; scalar_t__ last_tx_ring; int /*<<< orphan*/  nifp; TYPE_1__ req; } ;
struct netmap_ring {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ND (char*,struct netmap_ring*,struct netmap_ring*) ; 
 struct netmap_ring* NETMAP_RXRING (int /*<<< orphan*/ ,scalar_t__) ; 
 struct netmap_ring* NETMAP_TXRING (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ NR_REG_SW ; 
 scalar_t__ nm_ring_empty (struct netmap_ring*) ; 
 scalar_t__ process_rings (struct netmap_ring*,struct netmap_ring*,scalar_t__,char const*) ; 

__attribute__((used)) static int
move(struct nm_desc *src, struct nm_desc *dst, u_int limit)
{
	struct netmap_ring *txring, *rxring;
	u_int m = 0, si = src->first_rx_ring, di = dst->first_tx_ring;
	const char *msg = (src->req.nr_flags == NR_REG_SW) ?
		"host->net" : "net->host";

	while (si <= src->last_rx_ring && di <= dst->last_tx_ring) {
		rxring = NETMAP_RXRING(src->nifp, si);
		txring = NETMAP_TXRING(dst->nifp, di);
		ND("txring %p rxring %p", txring, rxring);
		if (nm_ring_empty(rxring)) {
			si++;
			continue;
		}
		if (nm_ring_empty(txring)) {
			di++;
			continue;
		}
		m += process_rings(rxring, txring, limit, msg);
	}

	return (m);
}