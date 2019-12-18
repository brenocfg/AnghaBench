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
struct TYPE_2__ {int /*<<< orphan*/  phys; } ;
struct xgene_dma_desc_sw {TYPE_1__ tx; int /*<<< orphan*/  node; } ;
struct xgene_dma_chan {int /*<<< orphan*/  desc_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  chan_dbg (struct xgene_dma_chan*,char*,struct xgene_dma_desc_sw*) ; 
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,struct xgene_dma_desc_sw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void xgene_dma_clean_descriptor(struct xgene_dma_chan *chan,
				       struct xgene_dma_desc_sw *desc)
{
	list_del(&desc->node);
	chan_dbg(chan, "LD %p free\n", desc);
	dma_pool_free(chan->desc_pool, desc, desc->tx.phys);
}