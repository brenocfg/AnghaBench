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
typedef  int /*<<< orphan*/  SSL_CTX ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  SSL_free (int /*<<< orphan*/ *) ; 
 char* SSL_get_cipher_list (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * SSL_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void openssl_debug_dump_cipher_list(SSL_CTX *ssl_ctx)
{
	SSL *ssl;
	int i;

	ssl = SSL_new(ssl_ctx);
	if (!ssl)
		return;

	wpa_printf(MSG_DEBUG,
		   "OpenSSL: Enabled cipher suites in priority order");
	for (i = 0; ; i++) {
		const char *cipher;

		cipher = SSL_get_cipher_list(ssl, i);
		if (!cipher)
			break;
		wpa_printf(MSG_DEBUG, "Cipher %d: %s", i, cipher);
	}

	SSL_free(ssl);
}