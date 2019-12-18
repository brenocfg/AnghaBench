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
struct ena_rx_buffer {int /*<<< orphan*/ * mbuf; int /*<<< orphan*/  map; } ;
struct ena_ring {int dummy; } ;
struct ena_adapter {int /*<<< orphan*/  rx_buf_tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int /*<<< orphan*/  ENA_WARNING ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ena_trace (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ena_free_rx_mbuf(struct ena_adapter *adapter, struct ena_ring *rx_ring,
    struct ena_rx_buffer *rx_info)
{

	if (rx_info->mbuf == NULL) {
		ena_trace(ENA_WARNING, "Trying to free unallocated buffer\n");
		return;
	}

	bus_dmamap_sync(adapter->rx_buf_tag, rx_info->map,
	    BUS_DMASYNC_POSTREAD);
	bus_dmamap_unload(adapter->rx_buf_tag, rx_info->map);
	m_freem(rx_info->mbuf);
	rx_info->mbuf = NULL;
}