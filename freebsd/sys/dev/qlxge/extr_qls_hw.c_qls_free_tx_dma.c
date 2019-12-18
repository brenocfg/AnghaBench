#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ map; } ;
typedef  TYPE_2__ qla_tx_buf_t ;
struct TYPE_8__ {int num_tx_rings; int /*<<< orphan*/ * tx_tag; TYPE_1__* tx_ring; } ;
typedef  TYPE_3__ qla_host_t ;
struct TYPE_6__ {TYPE_2__* tx_buf; } ;

/* Variables and functions */
 int NUM_TX_DESCRIPTORS ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  qls_free_tx_ring_dma (TYPE_3__*,int) ; 

__attribute__((used)) static void
qls_free_tx_dma(qla_host_t *ha)
{
	int i, j;
	qla_tx_buf_t *txb;

	for (i = 0; i < ha->num_tx_rings; i++) {

		qls_free_tx_ring_dma(ha, i);

		for (j = 0; j < NUM_TX_DESCRIPTORS; j++) {

			txb = &ha->tx_ring[i].tx_buf[j];

			if (txb->map) {
				bus_dmamap_destroy(ha->tx_tag, txb->map);
			}
		}
	}

        if (ha->tx_tag != NULL) {
                bus_dma_tag_destroy(ha->tx_tag);
                ha->tx_tag = NULL;
        }

	return;
}