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
struct device {int dummy; } ;
struct cc_hash_ctx {int /*<<< orphan*/  inter_digestsize; } ;
struct ahash_req_ctx {scalar_t__ opad_digest_dma_addr; scalar_t__ digest_bytes_len_dma_addr; scalar_t__ digest_buff_dma_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  HASH_MAX_LEN_SIZE ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,scalar_t__*) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cc_unmap_req(struct device *dev, struct ahash_req_ctx *state,
			 struct cc_hash_ctx *ctx)
{
	if (state->digest_buff_dma_addr) {
		dma_unmap_single(dev, state->digest_buff_dma_addr,
				 ctx->inter_digestsize, DMA_BIDIRECTIONAL);
		dev_dbg(dev, "Unmapped digest-buffer: digest_buff_dma_addr=%pad\n",
			&state->digest_buff_dma_addr);
		state->digest_buff_dma_addr = 0;
	}
	if (state->digest_bytes_len_dma_addr) {
		dma_unmap_single(dev, state->digest_bytes_len_dma_addr,
				 HASH_MAX_LEN_SIZE, DMA_BIDIRECTIONAL);
		dev_dbg(dev, "Unmapped digest-bytes-len buffer: digest_bytes_len_dma_addr=%pad\n",
			&state->digest_bytes_len_dma_addr);
		state->digest_bytes_len_dma_addr = 0;
	}
	if (state->opad_digest_dma_addr) {
		dma_unmap_single(dev, state->opad_digest_dma_addr,
				 ctx->inter_digestsize, DMA_BIDIRECTIONAL);
		dev_dbg(dev, "Unmapped opad-digest: opad_digest_dma_addr=%pad\n",
			&state->opad_digest_dma_addr);
		state->opad_digest_dma_addr = 0;
	}
}