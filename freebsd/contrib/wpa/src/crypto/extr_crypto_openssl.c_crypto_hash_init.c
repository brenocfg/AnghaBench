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
typedef  int /*<<< orphan*/  u8 ;
struct crypto_hash {int /*<<< orphan*/  ctx; } ;
typedef  enum crypto_hash_alg { ____Placeholder_crypto_hash_alg } crypto_hash_alg ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
#define  CRYPTO_HASH_ALG_HMAC_MD5 130 
#define  CRYPTO_HASH_ALG_HMAC_SHA1 129 
#define  CRYPTO_HASH_ALG_HMAC_SHA256 128 
 int /*<<< orphan*/ * EVP_md5 () ; 
 int /*<<< orphan*/ * EVP_sha1 () ; 
 int /*<<< orphan*/ * EVP_sha256 () ; 
 int /*<<< orphan*/  HMAC_CTX_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HMAC_CTX_new () ; 
 int HMAC_Init_ex (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bin_clear_free (struct crypto_hash*,int) ; 
 int /*<<< orphan*/  os_free (struct crypto_hash*) ; 
 struct crypto_hash* os_zalloc (int) ; 

struct crypto_hash * crypto_hash_init(enum crypto_hash_alg alg, const u8 *key,
				      size_t key_len)
{
	struct crypto_hash *ctx;
	const EVP_MD *md;

	switch (alg) {
#ifndef OPENSSL_NO_MD5
	case CRYPTO_HASH_ALG_HMAC_MD5:
		md = EVP_md5();
		break;
#endif /* OPENSSL_NO_MD5 */
#ifndef OPENSSL_NO_SHA
	case CRYPTO_HASH_ALG_HMAC_SHA1:
		md = EVP_sha1();
		break;
#endif /* OPENSSL_NO_SHA */
#ifndef OPENSSL_NO_SHA256
#ifdef CONFIG_SHA256
	case CRYPTO_HASH_ALG_HMAC_SHA256:
		md = EVP_sha256();
		break;
#endif /* CONFIG_SHA256 */
#endif /* OPENSSL_NO_SHA256 */
	default:
		return NULL;
	}

	ctx = os_zalloc(sizeof(*ctx));
	if (ctx == NULL)
		return NULL;
	ctx->ctx = HMAC_CTX_new();
	if (!ctx->ctx) {
		os_free(ctx);
		return NULL;
	}

	if (HMAC_Init_ex(ctx->ctx, key, key_len, md, NULL) != 1) {
		HMAC_CTX_free(ctx->ctx);
		bin_clear_free(ctx, sizeof(*ctx));
		return NULL;
	}

	return ctx;
}