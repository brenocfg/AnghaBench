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
struct talitos_ctx {struct device* dev; } ;
struct talitos_ahash_req_ctx {int first; unsigned int hw_context_size; int /*<<< orphan*/  hw_context; scalar_t__ swinit; scalar_t__ nbuf; scalar_t__ buf_idx; } ;
struct device {int dummy; } ;
struct crypto_ahash {int dummy; } ;
struct ahash_request {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 scalar_t__ SHA256_DIGEST_SIZE ; 
 unsigned int TALITOS_MDEU_CONTEXT_SIZE_MD5_SHA1_SHA256 ; 
 unsigned int TALITOS_MDEU_CONTEXT_SIZE_SHA384_SHA512 ; 
 struct talitos_ahash_req_ctx* ahash_request_ctx (struct ahash_request*) ; 
 struct talitos_ctx* crypto_ahash_ctx (struct crypto_ahash*) ; 
 scalar_t__ crypto_ahash_digestsize (struct crypto_ahash*) ; 
 struct crypto_ahash* crypto_ahash_reqtfm (struct ahash_request*) ; 
 int /*<<< orphan*/  dma_map_single (struct device*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ahash_init(struct ahash_request *areq)
{
	struct crypto_ahash *tfm = crypto_ahash_reqtfm(areq);
	struct talitos_ctx *ctx = crypto_ahash_ctx(tfm);
	struct device *dev = ctx->dev;
	struct talitos_ahash_req_ctx *req_ctx = ahash_request_ctx(areq);
	unsigned int size;
	dma_addr_t dma;

	/* Initialize the context */
	req_ctx->buf_idx = 0;
	req_ctx->nbuf = 0;
	req_ctx->first = 1; /* first indicates h/w must init its context */
	req_ctx->swinit = 0; /* assume h/w init of context */
	size =	(crypto_ahash_digestsize(tfm) <= SHA256_DIGEST_SIZE)
			? TALITOS_MDEU_CONTEXT_SIZE_MD5_SHA1_SHA256
			: TALITOS_MDEU_CONTEXT_SIZE_SHA384_SHA512;
	req_ctx->hw_context_size = size;

	dma = dma_map_single(dev, req_ctx->hw_context, req_ctx->hw_context_size,
			     DMA_TO_DEVICE);
	dma_unmap_single(dev, dma, req_ctx->hw_context_size, DMA_TO_DEVICE);

	return 0;
}