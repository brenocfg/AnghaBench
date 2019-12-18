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

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  SSL_CTX_get0_certificate (int /*<<< orphan*/ *) ; 
 int SSL_CTX_get0_chain_certs (int /*<<< orphan*/ *,int*) ; 
 int STACK_OF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509 ; 
 int certs ; 
 int /*<<< orphan*/  openssl_debug_dump_certificate (int,int /*<<< orphan*/ ) ; 
 int sk_X509_num (int) ; 
 int /*<<< orphan*/  sk_X509_value (int,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void openssl_debug_dump_certificates(SSL_CTX *ssl_ctx)
{
	STACK_OF(X509) *certs;

	wpa_printf(MSG_DEBUG, "OpenSSL: Configured certificate chain");
	if (SSL_CTX_get0_chain_certs(ssl_ctx, &certs) == 1) {
		int i;

		for (i = sk_X509_num(certs); i > 0; i--)
			openssl_debug_dump_certificate(i, sk_X509_value(certs,
									i - 1));
	}
	openssl_debug_dump_certificate(0, SSL_CTX_get0_certificate(ssl_ctx));
}