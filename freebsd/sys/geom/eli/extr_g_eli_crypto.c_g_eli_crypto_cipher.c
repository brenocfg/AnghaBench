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
typedef  int u_int ;
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  iv ;
typedef  int /*<<< orphan*/  EVP_CIPHER_CTX ;
typedef  int /*<<< orphan*/  EVP_CIPHER ;

/* Variables and functions */
#define  CRYPTO_3DES_CBC 132 
#define  CRYPTO_AES_CBC 131 
 int CRYPTO_AES_XTS ; 
#define  CRYPTO_BLF_CBC 130 
#define  CRYPTO_CAMELLIA_CBC 129 
#define  CRYPTO_NULL_CBC 128 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_CIPHER_CTX_new () ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_set_key_length (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_set_padding (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ EVP_CipherFinal_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  EVP_CipherInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ EVP_CipherUpdate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/ * EVP_aes_128_cbc () ; 
 int /*<<< orphan*/ * EVP_aes_192_cbc () ; 
 int /*<<< orphan*/ * EVP_aes_256_cbc () ; 
 int /*<<< orphan*/ * EVP_bf_cbc () ; 
 int /*<<< orphan*/ * EVP_camellia_128_cbc () ; 
 int /*<<< orphan*/ * EVP_camellia_192_cbc () ; 
 int /*<<< orphan*/ * EVP_camellia_256_cbc () ; 
 int /*<<< orphan*/ * EVP_des_ede3_cbc () ; 
 int /*<<< orphan*/ * EVP_enc_null () ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
g_eli_crypto_cipher(u_int algo, int enc, u_char *data, size_t datasize,
    const u_char *key, size_t keysize)
{
	EVP_CIPHER_CTX *ctx;
	const EVP_CIPHER *type;
	u_char iv[keysize];
	int outsize;

	assert(algo != CRYPTO_AES_XTS);

	switch (algo) {
	case CRYPTO_NULL_CBC:
		type = EVP_enc_null();
		break;
	case CRYPTO_AES_CBC:
		switch (keysize) {
		case 128:
			type = EVP_aes_128_cbc();
			break;
		case 192:
			type = EVP_aes_192_cbc();
			break;
		case 256:
			type = EVP_aes_256_cbc();
			break;
		default:
			return (EINVAL);
		}
		break;
	case CRYPTO_BLF_CBC:
		type = EVP_bf_cbc();
		break;
#ifndef OPENSSL_NO_CAMELLIA
	case CRYPTO_CAMELLIA_CBC:
		switch (keysize) {
		case 128:
			type = EVP_camellia_128_cbc();
			break;
		case 192:
			type = EVP_camellia_192_cbc();
			break;
		case 256:
			type = EVP_camellia_256_cbc();
			break;
		default:
			return (EINVAL);
		}
		break;
#endif
	case CRYPTO_3DES_CBC:
		type = EVP_des_ede3_cbc();
		break;
	default:
		return (EINVAL);
	}

	ctx = EVP_CIPHER_CTX_new();
	if (ctx == NULL)
		return (ENOMEM);

	EVP_CipherInit_ex(ctx, type, NULL, NULL, NULL, enc);
	EVP_CIPHER_CTX_set_key_length(ctx, keysize / 8);
	EVP_CIPHER_CTX_set_padding(ctx, 0);
	bzero(iv, sizeof(iv));
	EVP_CipherInit_ex(ctx, NULL, NULL, key, iv, enc);

	if (EVP_CipherUpdate(ctx, data, &outsize, data, datasize) == 0) {
		EVP_CIPHER_CTX_free(ctx);
		return (EINVAL);
	}
	assert(outsize == (int)datasize);

	if (EVP_CipherFinal_ex(ctx, data + outsize, &outsize) == 0) {
		EVP_CIPHER_CTX_free(ctx);
		return (EINVAL);
	}
	assert(outsize == 0);

	EVP_CIPHER_CTX_free(ctx);
	return (0);
}