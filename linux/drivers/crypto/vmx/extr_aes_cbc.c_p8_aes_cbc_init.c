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
struct skcipher_request {int dummy; } ;
struct p8_aes_cbc_ctx {struct crypto_skcipher* fallback; } ;
struct crypto_skcipher {int dummy; } ;

/* Variables and functions */
 int CRYPTO_ALG_ASYNC ; 
 int CRYPTO_ALG_NEED_FALLBACK ; 
 scalar_t__ IS_ERR (struct crypto_skcipher*) ; 
 int PTR_ERR (struct crypto_skcipher*) ; 
 struct crypto_skcipher* crypto_alloc_skcipher (char*,int /*<<< orphan*/ ,int) ; 
 struct p8_aes_cbc_ctx* crypto_skcipher_ctx (struct crypto_skcipher*) ; 
 scalar_t__ crypto_skcipher_reqsize (struct crypto_skcipher*) ; 
 int /*<<< orphan*/  crypto_skcipher_set_reqsize (struct crypto_skcipher*,scalar_t__) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static int p8_aes_cbc_init(struct crypto_skcipher *tfm)
{
	struct p8_aes_cbc_ctx *ctx = crypto_skcipher_ctx(tfm);
	struct crypto_skcipher *fallback;

	fallback = crypto_alloc_skcipher("cbc(aes)", 0,
					 CRYPTO_ALG_NEED_FALLBACK |
					 CRYPTO_ALG_ASYNC);
	if (IS_ERR(fallback)) {
		pr_err("Failed to allocate cbc(aes) fallback: %ld\n",
		       PTR_ERR(fallback));
		return PTR_ERR(fallback);
	}

	crypto_skcipher_set_reqsize(tfm, sizeof(struct skcipher_request) +
				    crypto_skcipher_reqsize(fallback));
	ctx->fallback = fallback;
	return 0;
}