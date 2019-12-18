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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_7__ {int /*<<< orphan*/  addr; } ;
struct TYPE_8__ {TYPE_3__ virt; } ;
struct TYPE_5__ {int /*<<< orphan*/  addr; } ;
struct TYPE_6__ {TYPE_1__ virt; } ;
struct skcipher_walk {unsigned int nbytes; TYPE_4__ dst; TYPE_2__ src; int /*<<< orphan*/  iv; } ;
struct skcipher_request {int cryptlen; } ;
struct p8_aes_xts_ctx {int /*<<< orphan*/  dec_key; int /*<<< orphan*/  enc_key; int /*<<< orphan*/  tweak_key; int /*<<< orphan*/  fallback; } ;
struct crypto_skcipher {int dummy; } ;

/* Variables and functions */
 int AES_BLOCK_SIZE ; 
 int XTS_BLOCK_SIZE ; 
 int /*<<< orphan*/  aes_p8_encrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aes_p8_xts_decrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aes_p8_xts_encrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_simd_usable () ; 
 struct p8_aes_xts_ctx* crypto_skcipher_ctx (struct crypto_skcipher*) ; 
 int crypto_skcipher_decrypt (struct skcipher_request*) ; 
 int crypto_skcipher_encrypt (struct skcipher_request*) ; 
 struct crypto_skcipher* crypto_skcipher_reqtfm (struct skcipher_request*) ; 
 int /*<<< orphan*/  disable_kernel_vsx () ; 
 int /*<<< orphan*/  enable_kernel_vsx () ; 
 int /*<<< orphan*/  pagefault_disable () ; 
 int /*<<< orphan*/  pagefault_enable () ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  round_down (unsigned int,int) ; 
 struct skcipher_request* skcipher_request_ctx (struct skcipher_request*) ; 
 int /*<<< orphan*/  skcipher_request_set_tfm (struct skcipher_request*,int /*<<< orphan*/ ) ; 
 int skcipher_walk_done (struct skcipher_walk*,unsigned int) ; 
 int skcipher_walk_virt (struct skcipher_walk*,struct skcipher_request*,int) ; 

__attribute__((used)) static int p8_aes_xts_crypt(struct skcipher_request *req, int enc)
{
	struct crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	const struct p8_aes_xts_ctx *ctx = crypto_skcipher_ctx(tfm);
	struct skcipher_walk walk;
	unsigned int nbytes;
	u8 tweak[AES_BLOCK_SIZE];
	int ret;

	if (!crypto_simd_usable() || (req->cryptlen % XTS_BLOCK_SIZE) != 0) {
		struct skcipher_request *subreq = skcipher_request_ctx(req);

		*subreq = *req;
		skcipher_request_set_tfm(subreq, ctx->fallback);
		return enc ? crypto_skcipher_encrypt(subreq) :
			     crypto_skcipher_decrypt(subreq);
	}

	ret = skcipher_walk_virt(&walk, req, false);
	if (ret)
		return ret;

	preempt_disable();
	pagefault_disable();
	enable_kernel_vsx();

	aes_p8_encrypt(walk.iv, tweak, &ctx->tweak_key);

	disable_kernel_vsx();
	pagefault_enable();
	preempt_enable();

	while ((nbytes = walk.nbytes) != 0) {
		preempt_disable();
		pagefault_disable();
		enable_kernel_vsx();
		if (enc)
			aes_p8_xts_encrypt(walk.src.virt.addr,
					   walk.dst.virt.addr,
					   round_down(nbytes, AES_BLOCK_SIZE),
					   &ctx->enc_key, NULL, tweak);
		else
			aes_p8_xts_decrypt(walk.src.virt.addr,
					   walk.dst.virt.addr,
					   round_down(nbytes, AES_BLOCK_SIZE),
					   &ctx->dec_key, NULL, tweak);
		disable_kernel_vsx();
		pagefault_enable();
		preempt_enable();

		ret = skcipher_walk_done(&walk, nbytes % AES_BLOCK_SIZE);
	}
	return ret;
}