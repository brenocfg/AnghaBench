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
typedef  int /*<<< orphan*/  u8 ;
struct talitos_ctx {int keylen; int /*<<< orphan*/  key; int /*<<< orphan*/  dma_key; struct device* dev; } ;
struct device {int dummy; } ;
struct crypto_ablkcipher {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 struct talitos_ctx* crypto_ablkcipher_ctx (struct crypto_ablkcipher*) ; 
 int /*<<< orphan*/  dma_map_single (struct device*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static int ablkcipher_setkey(struct crypto_ablkcipher *cipher,
			     const u8 *key, unsigned int keylen)
{
	struct talitos_ctx *ctx = crypto_ablkcipher_ctx(cipher);
	struct device *dev = ctx->dev;

	if (ctx->keylen)
		dma_unmap_single(dev, ctx->dma_key, ctx->keylen, DMA_TO_DEVICE);

	memcpy(&ctx->key, key, keylen);
	ctx->keylen = keylen;

	ctx->dma_key = dma_map_single(dev, ctx->key, keylen, DMA_TO_DEVICE);

	return 0;
}