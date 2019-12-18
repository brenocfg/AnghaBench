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
struct crypto_cipher {int /*<<< orphan*/  dec; int /*<<< orphan*/  enc; } ;
typedef  scalar_t__ gcry_error_t ;
typedef  enum gcry_cipher_algos { ____Placeholder_gcry_cipher_algos } gcry_cipher_algos ;
typedef  enum crypto_cipher_alg { ____Placeholder_crypto_cipher_alg } crypto_cipher_alg ;

/* Variables and functions */
#define  CRYPTO_CIPHER_ALG_3DES 132 
#define  CRYPTO_CIPHER_ALG_AES 131 
#define  CRYPTO_CIPHER_ALG_DES 130 
#define  CRYPTO_CIPHER_ALG_RC2 129 
#define  CRYPTO_CIPHER_ALG_RC4 128 
 int GCRY_CIPHER_3DES ; 
 int GCRY_CIPHER_AES ; 
 int GCRY_CIPHER_AES192 ; 
 int GCRY_CIPHER_AES256 ; 
 int GCRY_CIPHER_ARCFOUR ; 
 int GCRY_CIPHER_DES ; 
 int /*<<< orphan*/  GCRY_CIPHER_MODE_CBC ; 
 int /*<<< orphan*/  GCRY_CIPHER_MODE_STREAM ; 
 int GCRY_CIPHER_RFC2268_128 ; 
 int GCRY_CIPHER_RFC2268_40 ; 
 scalar_t__ GPG_ERR_NO_ERROR ; 
 int /*<<< orphan*/  gcry_cipher_close (int /*<<< orphan*/ ) ; 
 int gcry_cipher_get_algo_blklen (int) ; 
 scalar_t__ gcry_cipher_open (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ gcry_cipher_setiv (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 scalar_t__ gcry_cipher_setkey (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  os_free (struct crypto_cipher*) ; 
 struct crypto_cipher* os_zalloc (int) ; 

struct crypto_cipher * crypto_cipher_init(enum crypto_cipher_alg alg,
					  const u8 *iv, const u8 *key,
					  size_t key_len)
{
	struct crypto_cipher *ctx;
	gcry_error_t res;
	enum gcry_cipher_algos a;
	int ivlen;

	ctx = os_zalloc(sizeof(*ctx));
	if (ctx == NULL)
		return NULL;

	switch (alg) {
	case CRYPTO_CIPHER_ALG_RC4:
		a = GCRY_CIPHER_ARCFOUR;
		res = gcry_cipher_open(&ctx->enc, a, GCRY_CIPHER_MODE_STREAM,
				       0);
		gcry_cipher_open(&ctx->dec, a, GCRY_CIPHER_MODE_STREAM, 0);
		break;
	case CRYPTO_CIPHER_ALG_AES:
		if (key_len == 24)
			a = GCRY_CIPHER_AES192;
		else if (key_len == 32)
			a = GCRY_CIPHER_AES256;
		else
			a = GCRY_CIPHER_AES;
		res = gcry_cipher_open(&ctx->enc, a, GCRY_CIPHER_MODE_CBC, 0);
		gcry_cipher_open(&ctx->dec, a, GCRY_CIPHER_MODE_CBC, 0);
		break;
	case CRYPTO_CIPHER_ALG_3DES:
		a = GCRY_CIPHER_3DES;
		res = gcry_cipher_open(&ctx->enc, a, GCRY_CIPHER_MODE_CBC, 0);
		gcry_cipher_open(&ctx->dec, a, GCRY_CIPHER_MODE_CBC, 0);
		break;
	case CRYPTO_CIPHER_ALG_DES:
		a = GCRY_CIPHER_DES;
		res = gcry_cipher_open(&ctx->enc, a, GCRY_CIPHER_MODE_CBC, 0);
		gcry_cipher_open(&ctx->dec, a, GCRY_CIPHER_MODE_CBC, 0);
		break;
	case CRYPTO_CIPHER_ALG_RC2:
		if (key_len == 5)
			a = GCRY_CIPHER_RFC2268_40;
		else
			a = GCRY_CIPHER_RFC2268_128;
		res = gcry_cipher_open(&ctx->enc, a, GCRY_CIPHER_MODE_CBC, 0);
		gcry_cipher_open(&ctx->dec, a, GCRY_CIPHER_MODE_CBC, 0);
		break;
	default:
		os_free(ctx);
		return NULL;
	}

	if (res != GPG_ERR_NO_ERROR) {
		os_free(ctx);
		return NULL;
	}

	if (gcry_cipher_setkey(ctx->enc, key, key_len) != GPG_ERR_NO_ERROR ||
	    gcry_cipher_setkey(ctx->dec, key, key_len) != GPG_ERR_NO_ERROR) {
		gcry_cipher_close(ctx->enc);
		gcry_cipher_close(ctx->dec);
		os_free(ctx);
		return NULL;
	}

	ivlen = gcry_cipher_get_algo_blklen(a);
	if (gcry_cipher_setiv(ctx->enc, iv, ivlen) != GPG_ERR_NO_ERROR ||
	    gcry_cipher_setiv(ctx->dec, iv, ivlen) != GPG_ERR_NO_ERROR) {
		gcry_cipher_close(ctx->enc);
		gcry_cipher_close(ctx->dec);
		os_free(ctx);
		return NULL;
	}

	return ctx;
}