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
 int EVP_DecryptFinal_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int EVP_DecryptInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int EVP_DecryptUpdate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  EVP_aes_128_cbc () ; 
 scalar_t__ TEST_FAIL () ; 

int aes_128_cbc_decrypt(const u8 *key, const u8 *iv, u8 *data, size_t data_len)
{
	EVP_CIPHER_CTX *ctx;
	int plen, len;
	u8 buf[16];
	int res = -1;

	if (TEST_FAIL())
		return -1;

	ctx = EVP_CIPHER_CTX_new();
	if (!ctx)
		return -1;
	plen = data_len;
	len = sizeof(buf);
	if (EVP_DecryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv) == 1 &&
	    EVP_CIPHER_CTX_set_padding(ctx, 0) == 1 &&
	    EVP_DecryptUpdate(ctx, data, &plen, data, data_len) == 1 &&
	    plen == (int) data_len &&
	    EVP_DecryptFinal_ex(ctx, buf, &len) == 1 && len == 0)
		res = 0;
	EVP_CIPHER_CTX_free(ctx);

	return res;

}