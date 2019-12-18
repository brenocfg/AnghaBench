#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pdc_host_priv {unsigned int hdma_cons; unsigned int hdma_prod; TYPE_1__* hdma; scalar_t__ doing_hdma; } ;
struct ata_queued_cmd {struct ata_port* ap; } ;
struct ata_port {TYPE_2__* host; } ;
struct TYPE_4__ {struct pdc_host_priv* private_data; } ;
struct TYPE_3__ {int /*<<< orphan*/  pkt_ofs; int /*<<< orphan*/  seq; int /*<<< orphan*/  qc; } ;

/* Variables and functions */
 unsigned int PDC_HDMA_Q_MASK ; 
 int /*<<< orphan*/  __pdc20621_push_hdma (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pdc20621_pop_hdma(struct ata_queued_cmd *qc)
{
	struct ata_port *ap = qc->ap;
	struct pdc_host_priv *pp = ap->host->private_data;
	unsigned int idx = pp->hdma_cons & PDC_HDMA_Q_MASK;

	/* if nothing on queue, we're done */
	if (pp->hdma_prod == pp->hdma_cons) {
		pp->doing_hdma = 0;
		return;
	}

	__pdc20621_push_hdma(pp->hdma[idx].qc, pp->hdma[idx].seq,
			     pp->hdma[idx].pkt_ofs);
	pp->hdma_cons++;
}