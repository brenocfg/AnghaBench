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
struct ena_rx_buffer {scalar_t__ netmap_buf_idx; int /*<<< orphan*/ * mbuf; } ;
struct ena_ring {unsigned int ring_size; struct ena_rx_buffer* rx_buffer_info; } ;
struct ena_adapter {TYPE_1__* ifp; struct ena_ring* rx_ring; } ;
struct TYPE_2__ {int if_capenable; } ;

/* Variables and functions */
 int IFCAP_NETMAP ; 
 int IFF_DYING ; 
 int /*<<< orphan*/  ena_free_rx_mbuf (struct ena_adapter*,struct ena_ring*,struct ena_rx_buffer*) ; 
 int /*<<< orphan*/  ena_netmap_free_rx_slot (struct ena_adapter*,struct ena_ring*,struct ena_rx_buffer*) ; 
 int if_getflags (TYPE_1__*) ; 

__attribute__((used)) static void
ena_free_rx_bufs(struct ena_adapter *adapter, unsigned int qid)
{
	struct ena_ring *rx_ring = &adapter->rx_ring[qid];
	unsigned int i;

	for (i = 0; i < rx_ring->ring_size; i++) {
		struct ena_rx_buffer *rx_info = &rx_ring->rx_buffer_info[i];

		if (rx_info->mbuf != NULL)
			ena_free_rx_mbuf(adapter, rx_ring, rx_info);
#ifdef DEV_NETMAP
		if (((if_getflags(adapter->ifp) & IFF_DYING) == 0) &&
		    (adapter->ifp->if_capenable & IFCAP_NETMAP)) {
			if (rx_info->netmap_buf_idx != 0)
				ena_netmap_free_rx_slot(adapter, rx_ring,
				    rx_info);
		}
#endif /* DEV_NETMAP */
	}
}