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
struct dmaengine_result {unsigned int residue; int /*<<< orphan*/  result; } ;
struct axi_dmac_sg {unsigned int partial_len; } ;
struct TYPE_2__ {struct dmaengine_result tx_result; } ;
struct axi_dmac_desc {int num_completed; unsigned int num_sgs; struct axi_dmac_sg* sg; TYPE_1__ vdesc; } ;
struct axi_dmac_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TRANS_NOERROR ; 
 unsigned int axi_dmac_total_sg_bytes (struct axi_dmac_chan*,struct axi_dmac_sg*) ; 

__attribute__((used)) static void axi_dmac_compute_residue(struct axi_dmac_chan *chan,
	struct axi_dmac_desc *active)
{
	struct dmaengine_result *rslt = &active->vdesc.tx_result;
	unsigned int start = active->num_completed - 1;
	struct axi_dmac_sg *sg;
	unsigned int i, total;

	rslt->result = DMA_TRANS_NOERROR;
	rslt->residue = 0;

	/*
	 * We get here if the last completed segment is partial, which
	 * means we can compute the residue from that segment onwards
	 */
	for (i = start; i < active->num_sgs; i++) {
		sg = &active->sg[i];
		total = axi_dmac_total_sg_bytes(chan, sg);
		rslt->residue += (total - sg->partial_len);
	}
}