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
struct serpent_xts_ctx {int /*<<< orphan*/  crypt_ctx; int /*<<< orphan*/  tweak_ctx; } ;
struct crypto_skcipher {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XTS_TWEAK_CAST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __serpent_encrypt ; 
 struct serpent_xts_ctx* crypto_skcipher_ctx (struct crypto_skcipher*) ; 
 struct crypto_skcipher* crypto_skcipher_reqtfm (struct skcipher_request*) ; 
 int glue_xts_req_128bit (int /*<<< orphan*/ *,struct skcipher_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  serpent_dec_xts ; 

__attribute__((used)) static int xts_decrypt(struct skcipher_request *req)
{
	struct crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	struct serpent_xts_ctx *ctx = crypto_skcipher_ctx(tfm);

	return glue_xts_req_128bit(&serpent_dec_xts, req,
				   XTS_TWEAK_CAST(__serpent_encrypt),
				   &ctx->tweak_ctx, &ctx->crypt_ctx, true);
}