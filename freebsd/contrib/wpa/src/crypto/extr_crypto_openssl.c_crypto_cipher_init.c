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
struct crypto_cipher {void* dec; void* enc; } ;
typedef  enum crypto_cipher_alg { ____Placeholder_crypto_cipher_alg } crypto_cipher_alg ;
typedef  int /*<<< orphan*/  EVP_CIPHER ;

/* Variables and functions */
#define  CRYPTO_CIPHER_ALG_3DES 132 
#define  CRYPTO_CIPHER_ALG_AES 131 
#define  CRYPTO_CIPHER_ALG_DES 130 
#define  CRYPTO_CIPHER_ALG_RC2 129 
#define  CRYPTO_CIPHER_ALG_RC4 128 
 int /*<<< orphan*/  EVP_CIPHER_CTX_free (void*) ; 
 void* EVP_CIPHER_CTX_new () ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_set_key_length (void*,size_t) ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_set_padding (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_DecryptInit_ex (void*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EVP_EncryptInit_ex (void*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * EVP_aes_128_cbc () ; 
 int /*<<< orphan*/ * EVP_aes_192_cbc () ; 
 int /*<<< orphan*/ * EVP_aes_256_cbc () ; 
 int /*<<< orphan*/ * EVP_des_cbc () ; 
 int /*<<< orphan*/ * EVP_des_ede3_cbc () ; 
 int /*<<< orphan*/ * EVP_rc2_ecb () ; 
 int /*<<< orphan*/ * EVP_rc4 () ; 
 int /*<<< orphan*/  os_free (struct crypto_cipher*) ; 
 struct crypto_cipher* os_zalloc (int) ; 

struct crypto_cipher * crypto_cipher_init(enum crypto_cipher_alg alg,
					  const u8 *iv, const u8 *key,
					  size_t key_len)
{
	struct crypto_cipher *ctx;
	const EVP_CIPHER *cipher;

	ctx = os_zalloc(sizeof(*ctx));
	if (ctx == NULL)
		return NULL;

	switch (alg) {
#ifndef CONFIG_NO_RC4
#ifndef OPENSSL_NO_RC4
	case CRYPTO_CIPHER_ALG_RC4:
		cipher = EVP_rc4();
		break;
#endif /* OPENSSL_NO_RC4 */
#endif /* CONFIG_NO_RC4 */
#ifndef OPENSSL_NO_AES
	case CRYPTO_CIPHER_ALG_AES:
		switch (key_len) {
		case 16:
			cipher = EVP_aes_128_cbc();
			break;
#ifndef OPENSSL_IS_BORINGSSL
		case 24:
			cipher = EVP_aes_192_cbc();
			break;
#endif /* OPENSSL_IS_BORINGSSL */
		case 32:
			cipher = EVP_aes_256_cbc();
			break;
		default:
			os_free(ctx);
			return NULL;
		}
		break;
#endif /* OPENSSL_NO_AES */
#ifndef OPENSSL_NO_DES
	case CRYPTO_CIPHER_ALG_3DES:
		cipher = EVP_des_ede3_cbc();
		break;
	case CRYPTO_CIPHER_ALG_DES:
		cipher = EVP_des_cbc();
		break;
#endif /* OPENSSL_NO_DES */
#ifndef OPENSSL_NO_RC2
	case CRYPTO_CIPHER_ALG_RC2:
		cipher = EVP_rc2_ecb();
		break;
#endif /* OPENSSL_NO_RC2 */
	default:
		os_free(ctx);
		return NULL;
	}

	if (!(ctx->enc = EVP_CIPHER_CTX_new()) ||
	    !EVP_CIPHER_CTX_set_padding(ctx->enc, 0) ||
	    !EVP_EncryptInit_ex(ctx->enc, cipher, NULL, NULL, NULL) ||
	    !EVP_CIPHER_CTX_set_key_length(ctx->enc, key_len) ||
	    !EVP_EncryptInit_ex(ctx->enc, NULL, NULL, key, iv)) {
		if (ctx->enc)
			EVP_CIPHER_CTX_free(ctx->enc);
		os_free(ctx);
		return NULL;
	}

	if (!(ctx->dec = EVP_CIPHER_CTX_new()) ||
	    !EVP_CIPHER_CTX_set_padding(ctx->dec, 0) ||
	    !EVP_DecryptInit_ex(ctx->dec, cipher, NULL, NULL, NULL) ||
	    !EVP_CIPHER_CTX_set_key_length(ctx->dec, key_len) ||
	    !EVP_DecryptInit_ex(ctx->dec, NULL, NULL, key, iv)) {
		EVP_CIPHER_CTX_free(ctx->enc);
		if (ctx->dec)
			EVP_CIPHER_CTX_free(ctx->dec);
		os_free(ctx);
		return NULL;
	}

	return ctx;
}