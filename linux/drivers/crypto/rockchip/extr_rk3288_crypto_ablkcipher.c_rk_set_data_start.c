#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct rk_crypto_info {int total; int (* load_data ) (struct rk_crypto_info*,TYPE_1__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  sg_dst; TYPE_1__* sg_src; int /*<<< orphan*/  src_nents; int /*<<< orphan*/  first; int /*<<< orphan*/  async_req; } ;
struct rk_cipher_ctx {int mode; int /*<<< orphan*/  iv; } ;
struct crypto_ablkcipher {int dummy; } ;
struct ablkcipher_request {int /*<<< orphan*/  info; } ;
struct TYPE_3__ {int offset; int length; } ;

/* Variables and functions */
 int RK_CRYPTO_DEC ; 
 struct ablkcipher_request* ablkcipher_request_cast (int /*<<< orphan*/ ) ; 
 struct rk_cipher_ctx* crypto_ablkcipher_ctx (struct crypto_ablkcipher*) ; 
 int /*<<< orphan*/  crypto_ablkcipher_ivsize (struct crypto_ablkcipher*) ; 
 struct crypto_ablkcipher* crypto_ablkcipher_reqtfm (struct ablkcipher_request*) ; 
 int /*<<< orphan*/  crypto_dma_start (struct rk_crypto_info*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_page (TYPE_1__*) ; 
 int /*<<< orphan*/  sg_pcopy_to_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct rk_crypto_info*,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rk_set_data_start(struct rk_crypto_info *dev)
{
	int err;
	struct ablkcipher_request *req =
		ablkcipher_request_cast(dev->async_req);
	struct crypto_ablkcipher *tfm = crypto_ablkcipher_reqtfm(req);
	struct rk_cipher_ctx *ctx = crypto_ablkcipher_ctx(tfm);
	u32 ivsize = crypto_ablkcipher_ivsize(tfm);
	u8 *src_last_blk = page_address(sg_page(dev->sg_src)) +
		dev->sg_src->offset + dev->sg_src->length - ivsize;

	/* Store the iv that need to be updated in chain mode.
	 * And update the IV buffer to contain the next IV for decryption mode.
	 */
	if (ctx->mode & RK_CRYPTO_DEC) {
		memcpy(ctx->iv, src_last_blk, ivsize);
		sg_pcopy_to_buffer(dev->first, dev->src_nents, req->info,
				   ivsize, dev->total - ivsize);
	}

	err = dev->load_data(dev, dev->sg_src, dev->sg_dst);
	if (!err)
		crypto_dma_start(dev);
	return err;
}