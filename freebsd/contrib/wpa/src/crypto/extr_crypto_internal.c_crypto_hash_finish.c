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
typedef  int u8 ;
struct TYPE_2__ {int /*<<< orphan*/  sha256; int /*<<< orphan*/  sha1; int /*<<< orphan*/  md5; int /*<<< orphan*/  sha512; int /*<<< orphan*/  sha384; } ;
struct crypto_hash {int alg; TYPE_1__ u; int /*<<< orphan*/  key_len; int /*<<< orphan*/  key; } ;
typedef  int /*<<< orphan*/  k_pad ;

/* Variables and functions */
#define  CRYPTO_HASH_ALG_HMAC_MD5 135 
#define  CRYPTO_HASH_ALG_HMAC_SHA1 134 
#define  CRYPTO_HASH_ALG_HMAC_SHA256 133 
#define  CRYPTO_HASH_ALG_MD5 132 
#define  CRYPTO_HASH_ALG_SHA1 131 
#define  CRYPTO_HASH_ALG_SHA256 130 
#define  CRYPTO_HASH_ALG_SHA384 129 
#define  CRYPTO_HASH_ALG_SHA512 128 
 int /*<<< orphan*/  MD5Final (int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5Update (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  SHA1Final (int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA1Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA1Update (int /*<<< orphan*/ *,int*,int) ; 
 scalar_t__ TEST_FAIL () ; 
 int /*<<< orphan*/  os_free (struct crypto_hash*) ; 
 int /*<<< orphan*/  os_memcpy (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_memset (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sha256_done (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  sha256_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sha256_process (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  sha384_done (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  sha512_done (int /*<<< orphan*/ *,int*) ; 

int crypto_hash_finish(struct crypto_hash *ctx, u8 *mac, size_t *len)
{
	u8 k_pad[64];
	size_t i;

	if (ctx == NULL)
		return -2;

	if (mac == NULL || len == NULL) {
		os_free(ctx);
		return 0;
	}

	switch (ctx->alg) {
	case CRYPTO_HASH_ALG_MD5:
		if (*len < 16) {
			*len = 16;
			os_free(ctx);
			return -1;
		}
		*len = 16;
		MD5Final(mac, &ctx->u.md5);
		break;
	case CRYPTO_HASH_ALG_SHA1:
		if (*len < 20) {
			*len = 20;
			os_free(ctx);
			return -1;
		}
		*len = 20;
		SHA1Final(mac, &ctx->u.sha1);
		break;
#ifdef CONFIG_SHA256
	case CRYPTO_HASH_ALG_SHA256:
		if (*len < 32) {
			*len = 32;
			os_free(ctx);
			return -1;
		}
		*len = 32;
		sha256_done(&ctx->u.sha256, mac);
		break;
#endif /* CONFIG_SHA256 */
#ifdef CONFIG_INTERNAL_SHA384
	case CRYPTO_HASH_ALG_SHA384:
		if (*len < 48) {
			*len = 48;
			os_free(ctx);
			return -1;
		}
		*len = 48;
		sha384_done(&ctx->u.sha384, mac);
		break;
#endif /* CONFIG_INTERNAL_SHA384 */
#ifdef CONFIG_INTERNAL_SHA512
	case CRYPTO_HASH_ALG_SHA512:
		if (*len < 64) {
			*len = 64;
			os_free(ctx);
			return -1;
		}
		*len = 64;
		sha512_done(&ctx->u.sha512, mac);
		break;
#endif /* CONFIG_INTERNAL_SHA512 */
	case CRYPTO_HASH_ALG_HMAC_MD5:
		if (*len < 16) {
			*len = 16;
			os_free(ctx);
			return -1;
		}
		*len = 16;

		MD5Final(mac, &ctx->u.md5);

		os_memcpy(k_pad, ctx->key, ctx->key_len);
		os_memset(k_pad + ctx->key_len, 0,
			  sizeof(k_pad) - ctx->key_len);
		for (i = 0; i < sizeof(k_pad); i++)
			k_pad[i] ^= 0x5c;
		MD5Init(&ctx->u.md5);
		MD5Update(&ctx->u.md5, k_pad, sizeof(k_pad));
		MD5Update(&ctx->u.md5, mac, 16);
		MD5Final(mac, &ctx->u.md5);
		break;
	case CRYPTO_HASH_ALG_HMAC_SHA1:
		if (*len < 20) {
			*len = 20;
			os_free(ctx);
			return -1;
		}
		*len = 20;

		SHA1Final(mac, &ctx->u.sha1);

		os_memcpy(k_pad, ctx->key, ctx->key_len);
		os_memset(k_pad + ctx->key_len, 0,
			  sizeof(k_pad) - ctx->key_len);
		for (i = 0; i < sizeof(k_pad); i++)
			k_pad[i] ^= 0x5c;
		SHA1Init(&ctx->u.sha1);
		SHA1Update(&ctx->u.sha1, k_pad, sizeof(k_pad));
		SHA1Update(&ctx->u.sha1, mac, 20);
		SHA1Final(mac, &ctx->u.sha1);
		break;
#ifdef CONFIG_SHA256
	case CRYPTO_HASH_ALG_HMAC_SHA256:
		if (*len < 32) {
			*len = 32;
			os_free(ctx);
			return -1;
		}
		*len = 32;

		sha256_done(&ctx->u.sha256, mac);

		os_memcpy(k_pad, ctx->key, ctx->key_len);
		os_memset(k_pad + ctx->key_len, 0,
			  sizeof(k_pad) - ctx->key_len);
		for (i = 0; i < sizeof(k_pad); i++)
			k_pad[i] ^= 0x5c;
		sha256_init(&ctx->u.sha256);
		sha256_process(&ctx->u.sha256, k_pad, sizeof(k_pad));
		sha256_process(&ctx->u.sha256, mac, 32);
		sha256_done(&ctx->u.sha256, mac);
		break;
#endif /* CONFIG_SHA256 */
	default:
		os_free(ctx);
		return -1;
	}

	os_free(ctx);

	if (TEST_FAIL())
		return -1;

	return 0;
}