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
struct owl_dma_vchan {int /*<<< orphan*/  cfg; } ;
struct dma_slave_config {scalar_t__ src_addr_width; scalar_t__ dst_addr_width; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 scalar_t__ DMA_SLAVE_BUSWIDTH_8_BYTES ; 
 int EINVAL ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct dma_slave_config*,int) ; 
 struct owl_dma_vchan* to_owl_vchan (struct dma_chan*) ; 

__attribute__((used)) static int owl_dma_config(struct dma_chan *chan,
			  struct dma_slave_config *config)
{
	struct owl_dma_vchan *vchan = to_owl_vchan(chan);

	/* Reject definitely invalid configurations */
	if (config->src_addr_width == DMA_SLAVE_BUSWIDTH_8_BYTES ||
	    config->dst_addr_width == DMA_SLAVE_BUSWIDTH_8_BYTES)
		return -EINVAL;

	memcpy(&vchan->cfg, config, sizeof(struct dma_slave_config));

	return 0;
}