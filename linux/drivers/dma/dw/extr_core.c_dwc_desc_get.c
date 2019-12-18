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
struct TYPE_4__ {int /*<<< orphan*/  device; } ;
struct dw_dma_chan {TYPE_2__ chan; int /*<<< orphan*/  descs_allocated; } ;
struct dw_dma {int /*<<< orphan*/  desc_pool; } ;
struct TYPE_3__ {int /*<<< orphan*/  phys; int /*<<< orphan*/  flags; int /*<<< orphan*/  tx_submit; } ;
struct dw_desc {TYPE_1__ txd; int /*<<< orphan*/  tx_list; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_CTRL_ACK ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_async_tx_descriptor_init (TYPE_1__*,TYPE_2__*) ; 
 struct dw_desc* dma_pool_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwc_tx_submit ; 
 struct dw_dma* to_dw_dma (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dw_desc *dwc_desc_get(struct dw_dma_chan *dwc)
{
	struct dw_dma *dw = to_dw_dma(dwc->chan.device);
	struct dw_desc *desc;
	dma_addr_t phys;

	desc = dma_pool_zalloc(dw->desc_pool, GFP_ATOMIC, &phys);
	if (!desc)
		return NULL;

	dwc->descs_allocated++;
	INIT_LIST_HEAD(&desc->tx_list);
	dma_async_tx_descriptor_init(&desc->txd, &dwc->chan);
	desc->txd.tx_submit = dwc_tx_submit;
	desc->txd.flags = DMA_CTRL_ACK;
	desc->txd.phys = phys;
	return desc;
}