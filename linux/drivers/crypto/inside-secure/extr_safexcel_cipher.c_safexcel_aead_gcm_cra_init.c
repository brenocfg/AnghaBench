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
struct safexcel_cipher_ctx {int /*<<< orphan*/  hkaes; int /*<<< orphan*/  mode; int /*<<< orphan*/  xcm; int /*<<< orphan*/  state_sz; int /*<<< orphan*/  hash_alg; } ;
struct crypto_tfm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTEXT_CONTROL_CRYPTO_ALG_GHASH ; 
 int /*<<< orphan*/  CONTEXT_CONTROL_CRYPTO_MODE_XCM ; 
 int /*<<< orphan*/  EIP197_XCM_MODE_GCM ; 
 int /*<<< orphan*/  GHASH_BLOCK_SIZE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_alloc_cipher (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct safexcel_cipher_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  safexcel_aead_cra_init (struct crypto_tfm*) ; 

__attribute__((used)) static int safexcel_aead_gcm_cra_init(struct crypto_tfm *tfm)
{
	struct safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);

	safexcel_aead_cra_init(tfm);
	ctx->hash_alg = CONTEXT_CONTROL_CRYPTO_ALG_GHASH;
	ctx->state_sz = GHASH_BLOCK_SIZE;
	ctx->xcm = EIP197_XCM_MODE_GCM;
	ctx->mode = CONTEXT_CONTROL_CRYPTO_MODE_XCM; /* override default */

	ctx->hkaes = crypto_alloc_cipher("aes", 0, 0);
	if (IS_ERR(ctx->hkaes))
		return PTR_ERR(ctx->hkaes);

	return 0;
}