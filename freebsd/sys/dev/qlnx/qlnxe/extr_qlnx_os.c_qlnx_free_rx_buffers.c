#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sw_rx_data {int /*<<< orphan*/ * data; int /*<<< orphan*/ * map; } ;
struct qlnx_rx_queue {int num_rx_buffers; struct sw_rx_data* sw_rx_ring; } ;
struct TYPE_3__ {int /*<<< orphan*/  rx_tag; } ;
typedef  TYPE_1__ qlnx_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
qlnx_free_rx_buffers(qlnx_host_t *ha, struct qlnx_rx_queue *rxq)
{
        int			i;
	struct sw_rx_data	*rx_buf;

        for (i = 0; i < rxq->num_rx_buffers; i++) {

                rx_buf = &rxq->sw_rx_ring[i];

		if (rx_buf->data != NULL) {
			if (rx_buf->map != NULL) {
				bus_dmamap_unload(ha->rx_tag, rx_buf->map);
				bus_dmamap_destroy(ha->rx_tag, rx_buf->map);
				rx_buf->map = NULL;
			}
			m_freem(rx_buf->data);
			rx_buf->data = NULL;
		}
        }
	return;
}