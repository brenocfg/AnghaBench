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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  hmac; int /*<<< orphan*/  md; } ;
struct crypto_hash {int alg; TYPE_1__ u; } ;
typedef  enum crypto_hash_alg { ____Placeholder_crypto_hash_alg } crypto_hash_alg ;

/* Variables and functions */
#define  CRYPTO_HASH_ALG_HMAC_MD5 131 
#define  CRYPTO_HASH_ALG_HMAC_SHA1 130 
#define  CRYPTO_HASH_ALG_MD5 129 
#define  CRYPTO_HASH_ALG_SHA1 128 
 int /*<<< orphan*/  CRYPT_OK ; 
 int /*<<< orphan*/  find_hash (char*) ; 
 int /*<<< orphan*/  hmac_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  md5_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (struct crypto_hash*) ; 
 struct crypto_hash* os_zalloc (int) ; 
 int /*<<< orphan*/  sha1_init (int /*<<< orphan*/ *) ; 

struct crypto_hash * crypto_hash_init(enum crypto_hash_alg alg, const u8 *key,
				      size_t key_len)
{
	struct crypto_hash *ctx;

	ctx = os_zalloc(sizeof(*ctx));
	if (ctx == NULL)
		return NULL;

	ctx->alg = alg;

	switch (alg) {
	case CRYPTO_HASH_ALG_MD5:
		if (md5_init(&ctx->u.md) != CRYPT_OK)
			goto fail;
		break;
	case CRYPTO_HASH_ALG_SHA1:
		if (sha1_init(&ctx->u.md) != CRYPT_OK)
			goto fail;
		break;
	case CRYPTO_HASH_ALG_HMAC_MD5:
		if (hmac_init(&ctx->u.hmac, find_hash("md5"), key, key_len) !=
		    CRYPT_OK)
			goto fail;
		break;
	case CRYPTO_HASH_ALG_HMAC_SHA1:
		if (hmac_init(&ctx->u.hmac, find_hash("sha1"), key, key_len) !=
		    CRYPT_OK)
			goto fail;
		break;
	default:
		goto fail;
	}

	return ctx;

fail:
	os_free(ctx);
	return NULL;
}