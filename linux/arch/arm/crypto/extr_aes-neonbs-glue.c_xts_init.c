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
struct crypto_tfm {int dummy; } ;
struct aesbs_xts_ctx {void* tweak_tfm; void* cts_tfm; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int PTR_ERR_OR_ZERO (void*) ; 
 void* crypto_alloc_cipher (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_free_cipher (void*) ; 
 struct aesbs_xts_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 

__attribute__((used)) static int xts_init(struct crypto_tfm *tfm)
{
	struct aesbs_xts_ctx *ctx = crypto_tfm_ctx(tfm);

	ctx->cts_tfm = crypto_alloc_cipher("aes", 0, 0);
	if (IS_ERR(ctx->cts_tfm))
		return PTR_ERR(ctx->cts_tfm);

	ctx->tweak_tfm = crypto_alloc_cipher("aes", 0, 0);
	if (IS_ERR(ctx->tweak_tfm))
		crypto_free_cipher(ctx->cts_tfm);

	return PTR_ERR_OR_ZERO(ctx->tweak_tfm);
}