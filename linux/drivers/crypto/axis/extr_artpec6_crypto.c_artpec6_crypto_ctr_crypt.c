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
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;
struct skcipher_request {size_t iv; int /*<<< orphan*/  cryptlen; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; TYPE_1__ base; } ;
struct crypto_skcipher {int dummy; } ;
struct artpec6_cryptotfm_context {int /*<<< orphan*/  fallback; int /*<<< orphan*/  key_length; int /*<<< orphan*/  aes_key; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 unsigned int AES_BLOCK_SIZE ; 
 unsigned int ALIGN (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  SYNC_SKCIPHER_REQUEST_ON_STACK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int artpec6_crypto_decrypt (struct skcipher_request*) ; 
 int artpec6_crypto_encrypt (struct skcipher_request*) ; 
 unsigned int be32_to_cpup (int /*<<< orphan*/ *) ; 
 struct artpec6_cryptotfm_context* crypto_skcipher_ctx (struct crypto_skcipher*) ; 
 int crypto_skcipher_decrypt (int /*<<< orphan*/ ) ; 
 int crypto_skcipher_encrypt (int /*<<< orphan*/ ) ; 
 size_t crypto_skcipher_ivsize (struct crypto_skcipher*) ; 
 struct crypto_skcipher* crypto_skcipher_reqtfm (struct skcipher_request*) ; 
 int crypto_sync_skcipher_setkey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  skcipher_request_set_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skcipher_request_set_crypt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  skcipher_request_set_sync_tfm (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skcipher_request_zero (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  subreq ; 

__attribute__((used)) static int
artpec6_crypto_ctr_crypt(struct skcipher_request *req, bool encrypt)
{
	struct crypto_skcipher *cipher = crypto_skcipher_reqtfm(req);
	struct artpec6_cryptotfm_context *ctx = crypto_skcipher_ctx(cipher);
	size_t iv_len = crypto_skcipher_ivsize(cipher);
	unsigned int counter = be32_to_cpup((__be32 *)
					    (req->iv + iv_len - 4));
	unsigned int nblks = ALIGN(req->cryptlen, AES_BLOCK_SIZE) /
			     AES_BLOCK_SIZE;

	/*
	 * The hardware uses only the last 32-bits as the counter while the
	 * kernel tests (aes_ctr_enc_tv_template[4] for example) expect that
	 * the whole IV is a counter.  So fallback if the counter is going to
	 * overlow.
	 */
	if (counter + nblks < counter) {
		int ret;

		pr_debug("counter %x will overflow (nblks %u), falling back\n",
			 counter, counter + nblks);

		ret = crypto_sync_skcipher_setkey(ctx->fallback, ctx->aes_key,
						  ctx->key_length);
		if (ret)
			return ret;

		{
			SYNC_SKCIPHER_REQUEST_ON_STACK(subreq, ctx->fallback);

			skcipher_request_set_sync_tfm(subreq, ctx->fallback);
			skcipher_request_set_callback(subreq, req->base.flags,
						      NULL, NULL);
			skcipher_request_set_crypt(subreq, req->src, req->dst,
						   req->cryptlen, req->iv);
			ret = encrypt ? crypto_skcipher_encrypt(subreq)
				      : crypto_skcipher_decrypt(subreq);
			skcipher_request_zero(subreq);
		}
		return ret;
	}

	return encrypt ? artpec6_crypto_encrypt(req)
		       : artpec6_crypto_decrypt(req);
}