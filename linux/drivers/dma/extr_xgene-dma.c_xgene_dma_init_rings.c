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
struct xgene_dma {int /*<<< orphan*/ * chan; } ;

/* Variables and functions */
 int XGENE_DMA_MAX_CHANNEL ; 
 int xgene_dma_create_chan_rings (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xgene_dma_delete_chan_rings (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int xgene_dma_init_rings(struct xgene_dma *pdma)
{
	int ret, i, j;

	for (i = 0; i < XGENE_DMA_MAX_CHANNEL; i++) {
		ret = xgene_dma_create_chan_rings(&pdma->chan[i]);
		if (ret) {
			for (j = 0; j < i; j++)
				xgene_dma_delete_chan_rings(&pdma->chan[j]);
			return ret;
		}
	}

	return ret;
}