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
typedef  unsigned char u8 ;
typedef  int /*<<< orphan*/  skip_buf ;
typedef  int /*<<< orphan*/  EVP_CIPHER_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_CIPHER_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_CIPHER_CTX_new () ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_set_key_length (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_set_padding (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_CipherInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned char const*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ EVP_CipherUpdate (int /*<<< orphan*/ *,unsigned char*,int*,unsigned char*,size_t) ; 
 int /*<<< orphan*/ * EVP_rc4 () ; 

int rc4_skip(const u8 *key, size_t keylen, size_t skip,
	     u8 *data, size_t data_len)
{
#ifdef OPENSSL_NO_RC4
	return -1;
#else /* OPENSSL_NO_RC4 */
	EVP_CIPHER_CTX *ctx;
	int outl;
	int res = -1;
	unsigned char skip_buf[16];

	ctx = EVP_CIPHER_CTX_new();
	if (!ctx ||
	    !EVP_CIPHER_CTX_set_padding(ctx, 0) ||
	    !EVP_CipherInit_ex(ctx, EVP_rc4(), NULL, NULL, NULL, 1) ||
	    !EVP_CIPHER_CTX_set_key_length(ctx, keylen) ||
	    !EVP_CipherInit_ex(ctx, NULL, NULL, key, NULL, 1))
		goto out;

	while (skip >= sizeof(skip_buf)) {
		size_t len = skip;
		if (len > sizeof(skip_buf))
			len = sizeof(skip_buf);
		if (!EVP_CipherUpdate(ctx, skip_buf, &outl, skip_buf, len))
			goto out;
		skip -= len;
	}

	if (EVP_CipherUpdate(ctx, data, &outl, data, data_len))
		res = 0;

out:
	if (ctx)
		EVP_CIPHER_CTX_free(ctx);
	return res;
#endif /* OPENSSL_NO_RC4 */
}