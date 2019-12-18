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
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  EC_POINT ;
typedef  int /*<<< orphan*/  EC_KEY ;
typedef  int /*<<< orphan*/  EC_GROUP ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 size_t BIO_ctrl_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new (int /*<<< orphan*/ ) ; 
 int BIO_read (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  BIO_s_mem () ; 
 int /*<<< orphan*/  EC_KEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_KEY_get0_group (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_KEY_get0_public_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_get1_EC_KEY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_print_private (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 int /*<<< orphan*/  dpp_debug_print_point (char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int i2d_ECPrivateKey (int /*<<< orphan*/ *,unsigned char**) ; 
 int i2d_EC_PUBKEY (int /*<<< orphan*/ *,unsigned char**) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 char* os_malloc (size_t) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,unsigned char*,int) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,unsigned char*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,char const*,char*) ; 

__attribute__((used)) static void dpp_debug_print_key(const char *title, EVP_PKEY *key)
{
	EC_KEY *eckey;
	BIO *out;
	size_t rlen;
	char *txt;
	int res;
	unsigned char *der = NULL;
	int der_len;
	const EC_GROUP *group;
	const EC_POINT *point;

	out = BIO_new(BIO_s_mem());
	if (!out)
		return;

	EVP_PKEY_print_private(out, key, 0, NULL);
	rlen = BIO_ctrl_pending(out);
	txt = os_malloc(rlen + 1);
	if (txt) {
		res = BIO_read(out, txt, rlen);
		if (res > 0) {
			txt[res] = '\0';
			wpa_printf(MSG_DEBUG, "%s: %s", title, txt);
		}
		os_free(txt);
	}
	BIO_free(out);

	eckey = EVP_PKEY_get1_EC_KEY(key);
	if (!eckey)
		return;

	group = EC_KEY_get0_group(eckey);
	point = EC_KEY_get0_public_key(eckey);
	if (group && point)
		dpp_debug_print_point(title, group, point);

	der_len = i2d_ECPrivateKey(eckey, &der);
	if (der_len > 0)
		wpa_hexdump_key(MSG_DEBUG, "DPP: ECPrivateKey", der, der_len);
	OPENSSL_free(der);
	if (der_len <= 0) {
		der = NULL;
		der_len = i2d_EC_PUBKEY(eckey, &der);
		if (der_len > 0)
			wpa_hexdump(MSG_DEBUG, "DPP: EC_PUBKEY", der, der_len);
		OPENSSL_free(der);
	}

	EC_KEY_free(eckey);
}