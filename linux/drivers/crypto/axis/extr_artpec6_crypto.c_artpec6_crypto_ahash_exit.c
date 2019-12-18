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
struct artpec6_hashalg_context {scalar_t__ hmac_key_length; int /*<<< orphan*/  hmac_key; scalar_t__ child_hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_free_shash (scalar_t__) ; 
 struct artpec6_hashalg_context* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void artpec6_crypto_ahash_exit(struct crypto_tfm *tfm)
{
	struct artpec6_hashalg_context *tfm_ctx = crypto_tfm_ctx(tfm);

	if (tfm_ctx->child_hash)
		crypto_free_shash(tfm_ctx->child_hash);

	memset(tfm_ctx->hmac_key, 0, sizeof(tfm_ctx->hmac_key));
	tfm_ctx->hmac_key_length = 0;
}