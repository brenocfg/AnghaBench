#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  addr; } ;
struct TYPE_8__ {TYPE_3__ virt; } ;
struct TYPE_5__ {int /*<<< orphan*/  addr; } ;
struct TYPE_6__ {TYPE_1__ virt; } ;
struct skcipher_walk {unsigned int nbytes; int /*<<< orphan*/  iv; TYPE_4__ dst; TYPE_2__ src; } ;
struct skcipher_request {int dummy; } ;
struct p8_aes_ctr_ctx {int /*<<< orphan*/  enc_key; int /*<<< orphan*/  fallback; } ;
struct crypto_skcipher {int dummy; } ;

/* Variables and functions */
 unsigned int AES_BLOCK_SIZE ; 
 int /*<<< orphan*/  aes_p8_ctr32_encrypt_blocks (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_inc (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  crypto_simd_usable () ; 
 struct p8_aes_ctr_ctx* crypto_skcipher_ctx (struct crypto_skcipher*) ; 
 int crypto_skcipher_encrypt (struct skcipher_request*) ; 
 struct crypto_skcipher* crypto_skcipher_reqtfm (struct skcipher_request*) ; 
 int /*<<< orphan*/  disable_kernel_vsx () ; 
 int /*<<< orphan*/  enable_kernel_vsx () ; 
 int /*<<< orphan*/  p8_aes_ctr_final (struct p8_aes_ctr_ctx const*,struct skcipher_walk*) ; 
 int /*<<< orphan*/  pagefault_disable () ; 
 int /*<<< orphan*/  pagefault_enable () ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 struct skcipher_request* skcipher_request_ctx (struct skcipher_request*) ; 
 int /*<<< orphan*/  skcipher_request_set_tfm (struct skcipher_request*,int /*<<< orphan*/ ) ; 
 int skcipher_walk_done (struct skcipher_walk*,unsigned int) ; 
 int skcipher_walk_virt (struct skcipher_walk*,struct skcipher_request*,int) ; 

__attribute__((used)) static int p8_aes_ctr_crypt(struct skcipher_request *req)
{
	struct crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	const struct p8_aes_ctr_ctx *ctx = crypto_skcipher_ctx(tfm);
	struct skcipher_walk walk;
	unsigned int nbytes;
	int ret;

	if (!crypto_simd_usable()) {
		struct skcipher_request *subreq = skcipher_request_ctx(req);

		*subreq = *req;
		skcipher_request_set_tfm(subreq, ctx->fallback);
		return crypto_skcipher_encrypt(subreq);
	}

	ret = skcipher_walk_virt(&walk, req, false);
	while ((nbytes = walk.nbytes) >= AES_BLOCK_SIZE) {
		preempt_disable();
		pagefault_disable();
		enable_kernel_vsx();
		aes_p8_ctr32_encrypt_blocks(walk.src.virt.addr,
					    walk.dst.virt.addr,
					    nbytes / AES_BLOCK_SIZE,
					    &ctx->enc_key, walk.iv);
		disable_kernel_vsx();
		pagefault_enable();
		preempt_enable();

		do {
			crypto_inc(walk.iv, AES_BLOCK_SIZE);
		} while ((nbytes -= AES_BLOCK_SIZE) >= AES_BLOCK_SIZE);

		ret = skcipher_walk_done(&walk, nbytes);
	}
	if (nbytes) {
		p8_aes_ctr_final(ctx, &walk);
		ret = skcipher_walk_done(&walk, 0);
	}
	return ret;
}