#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct xgene_dma_desc_sw {int dummy; } ;
struct xgene_dma_chan {scalar_t__ desc_pool; int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  chan_dbg (struct xgene_dma_chan*,char*) ; 
 int /*<<< orphan*/  chan_err (struct xgene_dma_chan*,char*) ; 
 scalar_t__ dma_pool_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct xgene_dma_chan* to_dma_chan (struct dma_chan*) ; 

__attribute__((used)) static int xgene_dma_alloc_chan_resources(struct dma_chan *dchan)
{
	struct xgene_dma_chan *chan = to_dma_chan(dchan);

	/* Has this channel already been allocated? */
	if (chan->desc_pool)
		return 1;

	chan->desc_pool = dma_pool_create(chan->name, chan->dev,
					  sizeof(struct xgene_dma_desc_sw),
					  0, 0);
	if (!chan->desc_pool) {
		chan_err(chan, "Failed to allocate descriptor pool\n");
		return -ENOMEM;
	}

	chan_dbg(chan, "Allocate descriptor pool\n");

	return 1;
}