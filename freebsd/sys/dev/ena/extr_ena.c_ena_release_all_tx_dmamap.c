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
struct ena_netmap_tx_info {int /*<<< orphan*/ ** map_seg; } ;
struct ena_tx_buffer {int /*<<< orphan*/ * map_seg; int /*<<< orphan*/ * map_head; struct ena_netmap_tx_info nm_info; } ;
struct ena_ring {int ring_size; struct ena_tx_buffer* tx_buffer_info; struct ena_adapter* adapter; } ;
struct ena_adapter {TYPE_1__* ifp; int /*<<< orphan*/  tx_buf_tag; } ;
typedef  int /*<<< orphan*/  bus_dma_tag_t ;
struct TYPE_2__ {int if_capenable; } ;

/* Variables and functions */
 int ENA_PKT_MAX_BUFS ; 
 int IFCAP_NETMAP ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ena_release_all_tx_dmamap(struct ena_ring *tx_ring)
{
	struct ena_adapter *adapter = tx_ring->adapter;
	struct ena_tx_buffer *tx_info;
	bus_dma_tag_t tx_tag = adapter->tx_buf_tag;;
	int i;
#ifdef DEV_NETMAP
	struct ena_netmap_tx_info *nm_info;
	int j;
#endif /* DEV_NETMAP */

	for (i = 0; i < tx_ring->ring_size; ++i) {
		tx_info = &tx_ring->tx_buffer_info[i];
#ifdef DEV_NETMAP
		if (adapter->ifp->if_capenable & IFCAP_NETMAP) {
			nm_info = &tx_info->nm_info;
			for (j = 0; j < ENA_PKT_MAX_BUFS; ++j) {
				if (nm_info->map_seg[j] != NULL) {
					bus_dmamap_destroy(tx_tag,
					    nm_info->map_seg[j]);
					nm_info->map_seg[j] = NULL;
				}
			}
		}
#endif /* DEV_NETMAP */
		if (tx_info->map_head != NULL) {
			bus_dmamap_destroy(tx_tag, tx_info->map_head);
			tx_info->map_head = NULL;
		}

		if (tx_info->map_seg != NULL) {
			bus_dmamap_destroy(tx_tag, tx_info->map_seg);
			tx_info->map_seg = NULL;
		}
	}
}