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
struct TYPE_8__ {TYPE_2__* tx_ring; } ;
typedef  TYPE_3__ qla_host_t ;
struct TYPE_6__ {scalar_t__ privb_dma; scalar_t__ wq_dma; } ;
struct TYPE_7__ {TYPE_1__ flags; int /*<<< orphan*/  privb_dma; int /*<<< orphan*/  wq_dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  qls_free_dmabuf (TYPE_3__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
qls_free_tx_ring_dma(qla_host_t *ha, int r_idx)
{
	if (ha->tx_ring[r_idx].flags.wq_dma) {
		qls_free_dmabuf(ha, &ha->tx_ring[r_idx].wq_dma);
		ha->tx_ring[r_idx].flags.wq_dma = 0;
	}

	if (ha->tx_ring[r_idx].flags.privb_dma) {
		qls_free_dmabuf(ha, &ha->tx_ring[r_idx].privb_dma);
		ha->tx_ring[r_idx].flags.privb_dma = 0;
	}
	return;
}