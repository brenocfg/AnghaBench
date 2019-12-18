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
struct artpec6_crypto_req_common {struct artpec6_crypto_dma_descriptors* dma; } ;
struct artpec6_crypto_dma_descriptors {int in_cnt; int out_cnt; int /*<<< orphan*/  stat_dma_addr; scalar_t__* stat; int /*<<< orphan*/  out_dma_addr; scalar_t__* out; int /*<<< orphan*/  in_dma_addr; scalar_t__* in; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int artpec6_crypto_dma_map_single (struct artpec6_crypto_req_common*,scalar_t__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
artpec6_crypto_dma_map_descs(struct artpec6_crypto_req_common *common)
{
	struct artpec6_crypto_dma_descriptors *dma = common->dma;
	int ret;

	ret = artpec6_crypto_dma_map_single(common, dma->in,
				sizeof(dma->in[0]) * dma->in_cnt,
				DMA_TO_DEVICE, &dma->in_dma_addr);
	if (ret)
		return ret;

	ret = artpec6_crypto_dma_map_single(common, dma->out,
				sizeof(dma->out[0]) * dma->out_cnt,
				DMA_TO_DEVICE, &dma->out_dma_addr);
	if (ret)
		return ret;

	/* We only read one stat descriptor */
	dma->stat[dma->in_cnt - 1] = 0;

	/*
	 * DMA_BIDIRECTIONAL since we need our zeroing of the stat descriptor
	 * to be written.
	 */
	return artpec6_crypto_dma_map_single(common,
				dma->stat,
				sizeof(dma->stat[0]) * dma->in_cnt,
				DMA_BIDIRECTIONAL,
				&dma->stat_dma_addr);
}