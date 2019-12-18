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
typedef  scalar_t__ u32 ;
struct rk_crypto_info {scalar_t__ count; scalar_t__ addr_vir; TYPE_1__* sg_dst; scalar_t__ aligned; int /*<<< orphan*/  async_req; } ;
struct rk_cipher_ctx {int mode; } ;
struct crypto_ablkcipher {int dummy; } ;
struct ablkcipher_request {int /*<<< orphan*/  info; } ;
struct TYPE_2__ {scalar_t__ length; } ;

/* Variables and functions */
 int RK_CRYPTO_DEC ; 
 struct ablkcipher_request* ablkcipher_request_cast (int /*<<< orphan*/ ) ; 
 struct rk_cipher_ctx* crypto_ablkcipher_ctx (struct crypto_ablkcipher*) ; 
 scalar_t__ crypto_ablkcipher_ivsize (struct crypto_ablkcipher*) ; 
 struct crypto_ablkcipher* crypto_ablkcipher_reqtfm (struct ablkcipher_request*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ sg_virt (TYPE_1__*) ; 

__attribute__((used)) static void rk_iv_copyback(struct rk_crypto_info *dev)
{
	struct ablkcipher_request *req =
		ablkcipher_request_cast(dev->async_req);
	struct crypto_ablkcipher *tfm = crypto_ablkcipher_reqtfm(req);
	struct rk_cipher_ctx *ctx = crypto_ablkcipher_ctx(tfm);
	u32 ivsize = crypto_ablkcipher_ivsize(tfm);

	/* Update the IV buffer to contain the next IV for encryption mode. */
	if (!(ctx->mode & RK_CRYPTO_DEC)) {
		if (dev->aligned) {
			memcpy(req->info, sg_virt(dev->sg_dst) +
				dev->sg_dst->length - ivsize, ivsize);
		} else {
			memcpy(req->info, dev->addr_vir +
				dev->count - ivsize, ivsize);
		}
	}
}