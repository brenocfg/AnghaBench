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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  EVP_CIPHER_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_CIPHER_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_CIPHER_CTX_new () ; 
 int EVP_CIPHER_CTX_set_padding (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int EVP_EncryptFinal_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int EVP_EncryptInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int EVP_EncryptUpdate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  EVP_aes_128_cbc () ; 
 scalar_t__ TEST_FAIL () ; 

int aes_128_cbc_encrypt(const u8 *key, const u8 *iv, u8 *data, size_t data_len)
{
	EVP_CIPHER_CTX *ctx;
	int clen, len;
	u8 buf[16];
	int res = -1;

	if (TEST_FAIL())
		return -1;

	ctx = EVP_CIPHER_CTX_new();
	if (!ctx)
		return -1;
	clen = data_len;
	len = sizeof(buf);
	if (EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv) == 1 &&
	    EVP_CIPHER_CTX_set_padding(ctx, 0) == 1 &&
	    EVP_EncryptUpdate(ctx, data, &clen, data, data_len) == 1 &&
	    clen == (int) data_len &&
	    EVP_EncryptFinal_ex(ctx, buf, &len) == 1 && len == 0)
		res = 0;
	EVP_CIPHER_CTX_free(ctx);

	return res;
}