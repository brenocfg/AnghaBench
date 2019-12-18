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
 int ERR_error_string (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_get_error () ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_CIPHER_CTX_new () ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_set_padding (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int EVP_CipherFinal_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int EVP_CipherInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 
 int EVP_CipherUpdate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  errx (int,char*,int /*<<< orphan*/ ,size_t,int) ; 

__attribute__((used)) static void
openssl_cipher(struct alg *alg, const EVP_CIPHER *cipher, const char *key,
    const char *iv, const char *input, char *output, size_t size, int enc)
{
	EVP_CIPHER_CTX *ctx;
	int outl, total;

	ctx = EVP_CIPHER_CTX_new();
	if (ctx == NULL)
		errx(1, "OpenSSL %s (%zu) ctx new failed: %s", alg->name,
		    size, ERR_error_string(ERR_get_error(), NULL));
	if (EVP_CipherInit_ex(ctx, cipher, NULL, (const u_char *)key,
	    (const u_char *)iv, enc) != 1)
		errx(1, "OpenSSL %s (%zu) ctx init failed: %s", alg->name,
		    size, ERR_error_string(ERR_get_error(), NULL));
	EVP_CIPHER_CTX_set_padding(ctx, 0);
	if (EVP_CipherUpdate(ctx, (u_char *)output, &outl,
	    (const u_char *)input, size) != 1)
		errx(1, "OpenSSL %s (%zu) cipher update failed: %s", alg->name,
		    size, ERR_error_string(ERR_get_error(), NULL));
	total = outl;
	if (EVP_CipherFinal_ex(ctx, (u_char *)output + outl, &outl) != 1)
		errx(1, "OpenSSL %s (%zu) cipher final failed: %s", alg->name,
		    size, ERR_error_string(ERR_get_error(), NULL));
	total += outl;
	if (total != size)
		errx(1, "OpenSSL %s (%zu) cipher size mismatch: %d", alg->name,
		    size, total);
	EVP_CIPHER_CTX_free(ctx);
}