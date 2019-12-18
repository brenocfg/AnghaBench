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
typedef  int /*<<< orphan*/  u_char ;
struct alg {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  EVP_CIPHER_CTX ;
typedef  int /*<<< orphan*/  EVP_CIPHER ;

/* Variables and functions */
 size_t AES_CBC_MAC_HASH_LEN ; 
 int ERR_error_string (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_get_error () ; 
 int EVP_CIPHER_CTX_ctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t,char*) ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_CIPHER_CTX_new () ; 
 int /*<<< orphan*/  EVP_CTRL_CCM_GET_TAG ; 
 int /*<<< orphan*/  EVP_CTRL_CCM_SET_IVLEN ; 
 int /*<<< orphan*/  EVP_CTRL_CCM_SET_TAG ; 
 int EVP_EncryptFinal_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int EVP_EncryptInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int EVP_EncryptUpdate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  errx (int,char*,int /*<<< orphan*/ ,size_t,int) ; 

__attribute__((used)) static void
openssl_ccm_encrypt(struct alg *alg, const EVP_CIPHER *cipher, const char *key,
    const char *iv, size_t iv_len, const char *aad, size_t aad_len,
		    const char *input, char *output, size_t size, char *tag)
{
	EVP_CIPHER_CTX *ctx;
	int outl, total;

	ctx = EVP_CIPHER_CTX_new();
	if (ctx == NULL)
		errx(1, "OpenSSL %s (%zu) ctx new failed: %s", alg->name,
		    size, ERR_error_string(ERR_get_error(), NULL));
	if (EVP_EncryptInit_ex(ctx, cipher, NULL, NULL, NULL) != 1)
		errx(1, "OpenSSL %s (%zu) ctx init failed: %s", alg->name,
		    size, ERR_error_string(ERR_get_error(), NULL));
	if (EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_CCM_SET_IVLEN, iv_len, NULL) != 1)
		errx(1, "OpenSSL %s (%zu) setting iv length failed: %s", alg->name,
		    size, ERR_error_string(ERR_get_error(), NULL));
	if (EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_CCM_SET_TAG, AES_CBC_MAC_HASH_LEN, NULL) != 1)
		errx(1, "OpenSSL %s (%zu) setting tag length failed: %s", alg->name,
		     size, ERR_error_string(ERR_get_error(), NULL));
	if (EVP_EncryptInit_ex(ctx, NULL, NULL, (const u_char *)key,
	    (const u_char *)iv) != 1)
		errx(1, "OpenSSL %s (%zu) ctx init failed: %s", alg->name,
		    size, ERR_error_string(ERR_get_error(), NULL));
	if (EVP_EncryptUpdate(ctx, NULL, &outl, NULL, size) != 1)
		errx(1, "OpenSSL %s (%zu) unable to set data length: %s", alg->name,
		     size, ERR_error_string(ERR_get_error(), NULL));

	if (aad != NULL) {
		if (EVP_EncryptUpdate(ctx, NULL, &outl, (const u_char *)aad,
		    aad_len) != 1)
			errx(1, "OpenSSL %s (%zu) aad update failed: %s",
			    alg->name, size,
			    ERR_error_string(ERR_get_error(), NULL));
	}
	if (EVP_EncryptUpdate(ctx, (u_char *)output, &outl,
	    (const u_char *)input, size) != 1)
		errx(1, "OpenSSL %s (%zu) encrypt update failed: %s", alg->name,
		    size, ERR_error_string(ERR_get_error(), NULL));
	total = outl;
	if (EVP_EncryptFinal_ex(ctx, (u_char *)output + outl, &outl) != 1)
		errx(1, "OpenSSL %s (%zu) encrypt final failed: %s", alg->name,
		    size, ERR_error_string(ERR_get_error(), NULL));
	total += outl;
	if (total != size)
		errx(1, "OpenSSL %s (%zu) encrypt size mismatch: %d", alg->name,
		    size, total);
	if (EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_CCM_GET_TAG, AES_CBC_MAC_HASH_LEN,
	    tag) != 1)
		errx(1, "OpenSSL %s (%zu) get tag failed: %s", alg->name,
		    size, ERR_error_string(ERR_get_error(), NULL));
	EVP_CIPHER_CTX_free(ctx);
}