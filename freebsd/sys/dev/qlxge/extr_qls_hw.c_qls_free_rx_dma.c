#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int num_rx_rings; int /*<<< orphan*/ * rx_tag; } ;
typedef  TYPE_1__ qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qls_free_rx_ring_dma (TYPE_1__*,int) ; 

__attribute__((used)) static void
qls_free_rx_dma(qla_host_t *ha)
{
	int i;

	for (i = 0; i < ha->num_rx_rings; i++) {
		qls_free_rx_ring_dma(ha, i);
	}

        if (ha->rx_tag != NULL) {
                bus_dma_tag_destroy(ha->rx_tag);
                ha->rx_tag = NULL;
        }

	return;
}