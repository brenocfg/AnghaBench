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
typedef  int /*<<< orphan*/  WOLFSSL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  SSL_FILETYPE_ASN1 ; 
 int /*<<< orphan*/  SSL_FILETYPE_PEM ; 
 int /*<<< orphan*/  os_free (char*) ; 
 char* os_strdup (char const*) ; 
 int /*<<< orphan*/ * tls_passwd_cb ; 
 int /*<<< orphan*/  wolfSSL_CTX_set_default_passwd_cb (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wolfSSL_CTX_set_default_passwd_cb_userdata (int /*<<< orphan*/ *,char*) ; 
 int wolfSSL_CTX_use_PrivateKey_file (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int tls_global_private_key(void *ssl_ctx, const char *private_key,
				  const char *private_key_passwd)
{
	WOLFSSL_CTX *ctx = ssl_ctx;
	char *passwd = NULL;
	int ret = 0;

	if (!private_key)
		return 0;

	if (private_key_passwd) {
		passwd = os_strdup(private_key_passwd);
		if (!passwd)
			return -1;
	}

	wolfSSL_CTX_set_default_passwd_cb(ctx, tls_passwd_cb);
	wolfSSL_CTX_set_default_passwd_cb_userdata(ctx, passwd);

	if (wolfSSL_CTX_use_PrivateKey_file(ctx, private_key,
					    SSL_FILETYPE_ASN1) != 1 &&
	    wolfSSL_CTX_use_PrivateKey_file(ctx, private_key,
					    SSL_FILETYPE_PEM) != 1) {
		wpa_printf(MSG_INFO, "Failed to load private key");
		ret = -1;
	}

	wpa_printf(MSG_DEBUG, "SSL: Loaded global private key");

	os_free(passwd);
	wolfSSL_CTX_set_default_passwd_cb(ctx, NULL);

	return ret;
}