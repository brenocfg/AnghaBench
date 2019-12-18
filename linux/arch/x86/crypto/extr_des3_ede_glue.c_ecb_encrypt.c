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
struct skcipher_request {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  expkey; } ;
struct des3_ede_x86_ctx {TYPE_1__ enc; } ;
struct crypto_skcipher {int dummy; } ;

/* Variables and functions */
 struct des3_ede_x86_ctx* crypto_skcipher_ctx (struct crypto_skcipher*) ; 
 struct crypto_skcipher* crypto_skcipher_reqtfm (struct skcipher_request*) ; 
 int ecb_crypt (struct skcipher_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ecb_encrypt(struct skcipher_request *req)
{
	struct crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	struct des3_ede_x86_ctx *ctx = crypto_skcipher_ctx(tfm);

	return ecb_crypt(req, ctx->enc.expkey);
}