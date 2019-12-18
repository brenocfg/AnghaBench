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
struct TYPE_8__ {TYPE_2__* rx_ring; } ;
typedef  TYPE_3__ qla_host_t ;
struct TYPE_6__ {scalar_t__ lb_dma; scalar_t__ sbq_dma; scalar_t__ lbq_dma; scalar_t__ cq_dma; } ;
struct TYPE_7__ {TYPE_1__ flags; int /*<<< orphan*/  lb_dma; int /*<<< orphan*/  sbq_dma; int /*<<< orphan*/  lbq_dma; int /*<<< orphan*/  cq_dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  qls_free_dmabuf (TYPE_3__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
qls_free_rx_ring_dma(qla_host_t *ha, int ridx)
{
	if (ha->rx_ring[ridx].flags.cq_dma) {
		qls_free_dmabuf(ha, &ha->rx_ring[ridx].cq_dma);
		ha->rx_ring[ridx].flags.cq_dma = 0;
	}

	if (ha->rx_ring[ridx].flags.lbq_dma) {
		qls_free_dmabuf(ha, &ha->rx_ring[ridx].lbq_dma);
		ha->rx_ring[ridx].flags.lbq_dma = 0;
	}

	if (ha->rx_ring[ridx].flags.sbq_dma) {
		qls_free_dmabuf(ha, &ha->rx_ring[ridx].sbq_dma);
		ha->rx_ring[ridx].flags.sbq_dma = 0;
	}

	if (ha->rx_ring[ridx].flags.lb_dma) {
		qls_free_dmabuf(ha, &ha->rx_ring[ridx].lb_dma);
		ha->rx_ring[ridx].flags.lb_dma = 0;
	}
	return;
}