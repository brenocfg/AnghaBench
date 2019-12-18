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
struct crypto_tfm {int dummy; } ;
struct crypto_aead {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  aead; } ;
struct crypto4xx_ctx {TYPE_1__ sw_cipher; } ;

/* Variables and functions */
 int crypto_aead_setauthsize (int /*<<< orphan*/ ,unsigned int) ; 
 struct crypto_tfm* crypto_aead_tfm (struct crypto_aead*) ; 
 struct crypto4xx_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 

int crypto4xx_setauthsize_aead(struct crypto_aead *cipher,
			       unsigned int authsize)
{
	struct crypto_tfm *tfm = crypto_aead_tfm(cipher);
	struct crypto4xx_ctx *ctx = crypto_tfm_ctx(tfm);

	return crypto_aead_setauthsize(ctx->sw_cipher.aead, authsize);
}