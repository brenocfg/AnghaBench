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
struct tls_data {scalar_t__ tls_session_lifetime; struct tls_data* check_cert_subject; struct tls_data* ocsp_stapling_response; struct tls_data* ca_cert; int /*<<< orphan*/ * ssl; } ;
struct tls_context {scalar_t__ tls_session_lifetime; struct tls_context* check_cert_subject; struct tls_context* ocsp_stapling_response; struct tls_context* ca_cert; int /*<<< orphan*/ * ssl; } ;
typedef  int /*<<< orphan*/  SSL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_cleanup_all_ex_data () ; 
 int /*<<< orphan*/  ENGINE_cleanup () ; 
 int /*<<< orphan*/  ERR_free_strings () ; 
 int /*<<< orphan*/  ERR_remove_thread_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_cleanup () ; 
 int /*<<< orphan*/  SSL_CTX_flush_sessions (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_free (int /*<<< orphan*/ *) ; 
 struct tls_data* SSL_CTX_get_app_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (struct tls_data*) ; 
 struct tls_data* tls_global ; 
 scalar_t__ tls_openssl_ref_count ; 

void tls_deinit(void *ssl_ctx)
{
	struct tls_data *data = ssl_ctx;
	SSL_CTX *ssl = data->ssl;
	struct tls_context *context = SSL_CTX_get_app_data(ssl);
	if (context != tls_global)
		os_free(context);
	if (data->tls_session_lifetime > 0)
		SSL_CTX_flush_sessions(ssl, 0);
	os_free(data->ca_cert);
	SSL_CTX_free(ssl);

	tls_openssl_ref_count--;
	if (tls_openssl_ref_count == 0) {
#if OPENSSL_VERSION_NUMBER < 0x10100000L || \
	(defined(LIBRESSL_VERSION_NUMBER) && \
	 LIBRESSL_VERSION_NUMBER < 0x20700000L)
#ifndef OPENSSL_NO_ENGINE
		ENGINE_cleanup();
#endif /* OPENSSL_NO_ENGINE */
		CRYPTO_cleanup_all_ex_data();
		ERR_remove_thread_state(NULL);
		ERR_free_strings();
		EVP_cleanup();
#endif /* < 1.1.0 */
		os_free(tls_global->ocsp_stapling_response);
		tls_global->ocsp_stapling_response = NULL;
		os_free(tls_global);
		tls_global = NULL;
	}

	os_free(data->check_cert_subject);
	os_free(data);
}