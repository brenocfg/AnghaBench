#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * m_head; int /*<<< orphan*/  map; } ;
typedef  TYPE_3__ qla_rx_buf_t ;
struct TYPE_7__ {int num_rds_rings; } ;
struct TYPE_9__ {int /*<<< orphan*/  rx_tag; TYPE_1__* rx_ring; TYPE_2__ hw; } ;
typedef  TYPE_4__ qla_host_t ;
struct TYPE_6__ {TYPE_3__* rx_buf; } ;

/* Variables and functions */
 int NUM_RX_DESCRIPTORS ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
qla_free_rcv_std(qla_host_t *ha)
{
	int		i, r;
	qla_rx_buf_t	*rxb;

	for (r = 0; r < ha->hw.num_rds_rings; r++) {
		for (i = 0; i < NUM_RX_DESCRIPTORS; i++) {
			rxb = &ha->rx_ring[r].rx_buf[i];
			if (rxb->m_head != NULL) {
				bus_dmamap_unload(ha->rx_tag, rxb->map);
				bus_dmamap_destroy(ha->rx_tag, rxb->map);
				m_freem(rxb->m_head);
				rxb->m_head = NULL;
			}
		}
	}
	return;
}