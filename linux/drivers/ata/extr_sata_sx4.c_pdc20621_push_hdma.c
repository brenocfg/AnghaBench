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
typedef  int /*<<< orphan*/  u32 ;
struct pdc_host_priv {unsigned int hdma_prod; int doing_hdma; TYPE_1__* hdma; } ;
struct ata_queued_cmd {struct ata_port* ap; } ;
struct ata_port {TYPE_2__* host; } ;
struct TYPE_4__ {struct pdc_host_priv* private_data; } ;
struct TYPE_3__ {unsigned int seq; int /*<<< orphan*/  pkt_ofs; struct ata_queued_cmd* qc; } ;

/* Variables and functions */
 unsigned int PDC_HDMA_Q_MASK ; 
 int /*<<< orphan*/  __pdc20621_push_hdma (struct ata_queued_cmd*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pdc20621_push_hdma(struct ata_queued_cmd *qc,
				unsigned int seq,
				u32 pkt_ofs)
{
	struct ata_port *ap = qc->ap;
	struct pdc_host_priv *pp = ap->host->private_data;
	unsigned int idx = pp->hdma_prod & PDC_HDMA_Q_MASK;

	if (!pp->doing_hdma) {
		__pdc20621_push_hdma(qc, seq, pkt_ofs);
		pp->doing_hdma = 1;
		return;
	}

	pp->hdma[idx].qc = qc;
	pp->hdma[idx].seq = seq;
	pp->hdma[idx].pkt_ofs = pkt_ofs;
	pp->hdma_prod++;
}