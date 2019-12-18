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
struct safexcel_cipher_ctx {int /*<<< orphan*/  mode; int /*<<< orphan*/  alg; } ;
struct crypto_tfm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTEXT_CONTROL_CRYPTO_MODE_CBC ; 
 int /*<<< orphan*/  SAFEXCEL_AES ; 
 struct safexcel_cipher_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  safexcel_skcipher_cra_init (struct crypto_tfm*) ; 

__attribute__((used)) static int safexcel_skcipher_aes_cbc_cra_init(struct crypto_tfm *tfm)
{
	struct safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);

	safexcel_skcipher_cra_init(tfm);
	ctx->alg  = SAFEXCEL_AES;
	ctx->mode = CONTEXT_CONTROL_CRYPTO_MODE_CBC;
	return 0;
}