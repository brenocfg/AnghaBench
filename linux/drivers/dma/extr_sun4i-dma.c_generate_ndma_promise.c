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
struct sun4i_dma_promise {size_t len; int cfg; void* dst; void* src; } ;
struct dma_slave_config {int /*<<< orphan*/  dst_addr_width; int /*<<< orphan*/  src_addr_width; int /*<<< orphan*/  dst_maxburst; int /*<<< orphan*/  src_maxburst; } ;
struct dma_chan {int dummy; } ;
typedef  enum dma_transfer_direction { ____Placeholder_dma_transfer_direction } dma_transfer_direction ;
typedef  void* dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOWAIT ; 
 int SUN4I_DMA_CFG_DST_BURST_LENGTH (int) ; 
 int SUN4I_DMA_CFG_DST_DATA_WIDTH (int) ; 
 int SUN4I_DMA_CFG_LOADING ; 
 int SUN4I_DMA_CFG_SRC_BURST_LENGTH (int) ; 
 int SUN4I_DMA_CFG_SRC_DATA_WIDTH (int) ; 
 int SUN4I_NDMA_CFG_BYTE_COUNT_MODE_REMAIN ; 
 int /*<<< orphan*/  chan2dev (struct dma_chan*) ; 
 int convert_burst (int /*<<< orphan*/ ) ; 
 int convert_buswidth (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct sun4i_dma_promise*) ; 
 struct sun4i_dma_promise* kzalloc (int,int /*<<< orphan*/ ) ; 
 int sanitize_config (struct dma_slave_config*,int) ; 

__attribute__((used)) static struct sun4i_dma_promise *
generate_ndma_promise(struct dma_chan *chan, dma_addr_t src, dma_addr_t dest,
		      size_t len, struct dma_slave_config *sconfig,
		      enum dma_transfer_direction direction)
{
	struct sun4i_dma_promise *promise;
	int ret;

	ret = sanitize_config(sconfig, direction);
	if (ret)
		return NULL;

	promise = kzalloc(sizeof(*promise), GFP_NOWAIT);
	if (!promise)
		return NULL;

	promise->src = src;
	promise->dst = dest;
	promise->len = len;
	promise->cfg = SUN4I_DMA_CFG_LOADING |
		SUN4I_NDMA_CFG_BYTE_COUNT_MODE_REMAIN;

	dev_dbg(chan2dev(chan),
		"src burst %d, dst burst %d, src buswidth %d, dst buswidth %d",
		sconfig->src_maxburst, sconfig->dst_maxburst,
		sconfig->src_addr_width, sconfig->dst_addr_width);

	/* Source burst */
	ret = convert_burst(sconfig->src_maxburst);
	if (ret < 0)
		goto fail;
	promise->cfg |= SUN4I_DMA_CFG_SRC_BURST_LENGTH(ret);

	/* Destination burst */
	ret = convert_burst(sconfig->dst_maxburst);
	if (ret < 0)
		goto fail;
	promise->cfg |= SUN4I_DMA_CFG_DST_BURST_LENGTH(ret);

	/* Source bus width */
	ret = convert_buswidth(sconfig->src_addr_width);
	if (ret < 0)
		goto fail;
	promise->cfg |= SUN4I_DMA_CFG_SRC_DATA_WIDTH(ret);

	/* Destination bus width */
	ret = convert_buswidth(sconfig->dst_addr_width);
	if (ret < 0)
		goto fail;
	promise->cfg |= SUN4I_DMA_CFG_DST_DATA_WIDTH(ret);

	return promise;

fail:
	kfree(promise);
	return NULL;
}