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
typedef  int /*<<< orphan*/  EVP_MD_CTX ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_error_string (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_get_error () ; 
 int /*<<< orphan*/  EVP_DigestFinal (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int*) ; 
 int /*<<< orphan*/  EVP_DigestInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestUpdate (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t const) ; 
 int /*<<< orphan*/  EVP_MD_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_new () ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 scalar_t__ TEST_FAIL () ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int openssl_digest_vector(const EVP_MD *type, size_t num_elem,
				 const u8 *addr[], const size_t *len, u8 *mac)
{
	EVP_MD_CTX *ctx;
	size_t i;
	unsigned int mac_len;

	if (TEST_FAIL())
		return -1;

	ctx = EVP_MD_CTX_new();
	if (!ctx)
		return -1;
	if (!EVP_DigestInit_ex(ctx, type, NULL)) {
		wpa_printf(MSG_ERROR, "OpenSSL: EVP_DigestInit_ex failed: %s",
			   ERR_error_string(ERR_get_error(), NULL));
		EVP_MD_CTX_free(ctx);
		return -1;
	}
	for (i = 0; i < num_elem; i++) {
		if (!EVP_DigestUpdate(ctx, addr[i], len[i])) {
			wpa_printf(MSG_ERROR, "OpenSSL: EVP_DigestUpdate "
				   "failed: %s",
				   ERR_error_string(ERR_get_error(), NULL));
			EVP_MD_CTX_free(ctx);
			return -1;
		}
	}
	if (!EVP_DigestFinal(ctx, mac, &mac_len)) {
		wpa_printf(MSG_ERROR, "OpenSSL: EVP_DigestFinal failed: %s",
			   ERR_error_string(ERR_get_error(), NULL));
		EVP_MD_CTX_free(ctx);
		return -1;
	}
	EVP_MD_CTX_free(ctx);

	return 0;
}