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
struct TYPE_2__ {int /*<<< orphan*/  phys; int /*<<< orphan*/  tx_submit; } ;
struct mmp_pdma_desc_sw {TYPE_1__ async_tx; int /*<<< orphan*/  tx_list; } ;
struct mmp_pdma_chan {int /*<<< orphan*/  chan; int /*<<< orphan*/  dev; int /*<<< orphan*/  desc_pool; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dma_async_tx_descriptor_init (TYPE_1__*,int /*<<< orphan*/ *) ; 
 struct mmp_pdma_desc_sw* dma_pool_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmp_pdma_tx_submit ; 

__attribute__((used)) static struct mmp_pdma_desc_sw *
mmp_pdma_alloc_descriptor(struct mmp_pdma_chan *chan)
{
	struct mmp_pdma_desc_sw *desc;
	dma_addr_t pdesc;

	desc = dma_pool_zalloc(chan->desc_pool, GFP_ATOMIC, &pdesc);
	if (!desc) {
		dev_err(chan->dev, "out of memory for link descriptor\n");
		return NULL;
	}

	INIT_LIST_HEAD(&desc->tx_list);
	dma_async_tx_descriptor_init(&desc->async_tx, &chan->chan);
	/* each desc has submit */
	desc->async_tx.tx_submit = mmp_pdma_tx_submit;
	desc->async_tx.phys = pdesc;

	return desc;
}