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
typedef  int /*<<< orphan*/  EVP_CIPHER_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_error_string (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_get_error () ; 
 int EVP_EncryptUpdate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

int aes_encrypt(void *ctx, const u8 *plain, u8 *crypt)
{
	EVP_CIPHER_CTX *c = ctx;
	int clen = 16;
	if (EVP_EncryptUpdate(c, crypt, &clen, plain, 16) != 1) {
		wpa_printf(MSG_ERROR, "OpenSSL: EVP_EncryptUpdate failed: %s",
			   ERR_error_string(ERR_get_error(), NULL));
		return -1;
	}
	return 0;
}