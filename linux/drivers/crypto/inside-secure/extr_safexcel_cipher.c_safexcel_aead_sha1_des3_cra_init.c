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
struct safexcel_cipher_ctx {int /*<<< orphan*/  alg; } ;
struct crypto_tfm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAFEXCEL_3DES ; 
 struct safexcel_cipher_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  safexcel_aead_sha1_cra_init (struct crypto_tfm*) ; 

__attribute__((used)) static int safexcel_aead_sha1_des3_cra_init(struct crypto_tfm *tfm)
{
	struct safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);

	safexcel_aead_sha1_cra_init(tfm);
	ctx->alg = SAFEXCEL_3DES; /* override default */
	return 0;
}