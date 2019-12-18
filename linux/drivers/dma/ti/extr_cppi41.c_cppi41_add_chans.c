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
typedef  int u32 ;
struct device {int dummy; } ;
struct cppi41_desc {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  channels; } ;
struct cppi41_dd {int n_chans; int descs_phys; int first_td_desc; TYPE_2__ ddev; int /*<<< orphan*/ * cd; scalar_t__ ctrl_mem; } ;
struct TYPE_3__ {int /*<<< orphan*/  device_node; TYPE_2__* device; } ;
struct cppi41_channel {int is_tx; int port_num; int desc_phys; TYPE_1__ chan; int /*<<< orphan*/ * desc; scalar_t__ gcr_reg; struct cppi41_dd* cdd; } ;

/* Variables and functions */
 scalar_t__ DMA_RXGCR (int) ; 
 scalar_t__ DMA_TXGCR (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct cppi41_channel* devm_kcalloc (struct device*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cppi41_add_chans(struct device *dev, struct cppi41_dd *cdd)
{
	struct cppi41_channel *cchan, *chans;
	int i;
	u32 n_chans = cdd->n_chans;

	/*
	 * The channels can only be used as TX or as RX. So we add twice
	 * that much dma channels because USB can only do RX or TX.
	 */
	n_chans *= 2;

	chans = devm_kcalloc(dev, n_chans, sizeof(*chans), GFP_KERNEL);
	if (!chans)
		return -ENOMEM;

	for (i = 0; i < n_chans; i++) {
		cchan = &chans[i];

		cchan->cdd = cdd;
		if (i & 1) {
			cchan->gcr_reg = cdd->ctrl_mem + DMA_TXGCR(i >> 1);
			cchan->is_tx = 1;
		} else {
			cchan->gcr_reg = cdd->ctrl_mem + DMA_RXGCR(i >> 1);
			cchan->is_tx = 0;
		}
		cchan->port_num = i >> 1;
		cchan->desc = &cdd->cd[i];
		cchan->desc_phys = cdd->descs_phys;
		cchan->desc_phys += i * sizeof(struct cppi41_desc);
		cchan->chan.device = &cdd->ddev;
		list_add_tail(&cchan->chan.device_node, &cdd->ddev.channels);
	}
	cdd->first_td_desc = n_chans;

	return 0;
}