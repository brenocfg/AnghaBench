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
struct safexcel_cipher_ctx {int state_sz; int /*<<< orphan*/  mode; int /*<<< orphan*/  xcm; int /*<<< orphan*/  hash_alg; } ;
struct crypto_tfm {int dummy; } ;

/* Variables and functions */
 int AES_BLOCK_SIZE ; 
 int /*<<< orphan*/  CONTEXT_CONTROL_CRYPTO_ALG_XCBC128 ; 
 int /*<<< orphan*/  CONTEXT_CONTROL_CRYPTO_MODE_XCM ; 
 int /*<<< orphan*/  EIP197_XCM_MODE_CCM ; 
 struct safexcel_cipher_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  safexcel_aead_cra_init (struct crypto_tfm*) ; 

__attribute__((used)) static int safexcel_aead_ccm_cra_init(struct crypto_tfm *tfm)
{
	struct safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);

	safexcel_aead_cra_init(tfm);
	ctx->hash_alg = CONTEXT_CONTROL_CRYPTO_ALG_XCBC128;
	ctx->state_sz = 3 * AES_BLOCK_SIZE;
	ctx->xcm = EIP197_XCM_MODE_CCM;
	ctx->mode = CONTEXT_CONTROL_CRYPTO_MODE_XCM; /* override default */
	return 0;
}