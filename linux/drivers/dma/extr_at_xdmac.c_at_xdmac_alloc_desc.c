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
struct dma_chan {int /*<<< orphan*/  device; } ;
struct TYPE_2__ {int /*<<< orphan*/  phys; int /*<<< orphan*/  tx_submit; } ;
struct at_xdmac_desc {TYPE_1__ tx_dma_desc; int /*<<< orphan*/  descs_list; } ;
struct at_xdmac {int /*<<< orphan*/  at_xdmac_desc_pool; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  at_xdmac_tx_submit ; 
 int /*<<< orphan*/  dma_async_tx_descriptor_init (TYPE_1__*,struct dma_chan*) ; 
 struct at_xdmac_desc* dma_pool_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct at_xdmac* to_at_xdmac (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct at_xdmac_desc *at_xdmac_alloc_desc(struct dma_chan *chan,
						 gfp_t gfp_flags)
{
	struct at_xdmac_desc	*desc;
	struct at_xdmac		*atxdmac = to_at_xdmac(chan->device);
	dma_addr_t		phys;

	desc = dma_pool_zalloc(atxdmac->at_xdmac_desc_pool, gfp_flags, &phys);
	if (desc) {
		INIT_LIST_HEAD(&desc->descs_list);
		dma_async_tx_descriptor_init(&desc->tx_dma_desc, chan);
		desc->tx_dma_desc.tx_submit = at_xdmac_tx_submit;
		desc->tx_dma_desc.phys = phys;
	}

	return desc;
}