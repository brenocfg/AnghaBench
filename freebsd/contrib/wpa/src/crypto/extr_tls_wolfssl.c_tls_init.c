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
struct tls_context {int dummy; } ;
struct tls_config {char* openssl_ciphers; int /*<<< orphan*/  tls_session_lifetime; } ;
typedef  void WOLFSSL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  SSL_SESS_CACHE_CLIENT ; 
 int /*<<< orphan*/  SSL_SESS_CACHE_SERVER ; 
 int /*<<< orphan*/  os_free (struct tls_context*) ; 
 int /*<<< orphan*/  remove_session_cb ; 
 struct tls_context* tls_context_new (struct tls_config const*) ; 
 int /*<<< orphan*/  tls_deinit (void*) ; 
 struct tls_context* tls_global ; 
 scalar_t__ tls_ref_count ; 
 void* wolfSSL_CTX_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wolfSSL_CTX_sess_set_remove_cb (void*,int /*<<< orphan*/ ) ; 
 int wolfSSL_CTX_set_cipher_list (void*,char const*) ; 
 int /*<<< orphan*/  wolfSSL_CTX_set_ex_data (void*,int /*<<< orphan*/ ,struct tls_context*) ; 
 int /*<<< orphan*/  wolfSSL_CTX_set_quiet_shutdown (void*,int) ; 
 int /*<<< orphan*/  wolfSSL_CTX_set_session_cache_mode (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wolfSSL_CTX_set_timeout (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wolfSSL_Debugging_ON () ; 
 scalar_t__ wolfSSL_Init () ; 
 int /*<<< orphan*/  wolfSSL_SetIORecv (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wolfSSL_SetIOSend (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wolfSSLv23_client_method () ; 
 int /*<<< orphan*/  wolfssl_receive_cb ; 
 int /*<<< orphan*/  wolfssl_send_cb ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,char const*) ; 

void * tls_init(const struct tls_config *conf)
{
	WOLFSSL_CTX *ssl_ctx;
	struct tls_context *context;
	const char *ciphers;

#ifdef DEBUG_WOLFSSL
	wolfSSL_Debugging_ON();
#endif /* DEBUG_WOLFSSL */

	context = tls_context_new(conf);
	if (!context)
		return NULL;

	if (tls_ref_count == 0) {
		tls_global = context;

		if (wolfSSL_Init() < 0)
			return NULL;
		/* wolfSSL_Debugging_ON(); */
	}

	tls_ref_count++;

	/* start as client */
	ssl_ctx = wolfSSL_CTX_new(wolfSSLv23_client_method());
	if (!ssl_ctx) {
		tls_ref_count--;
		if (context != tls_global)
			os_free(context);
		if (tls_ref_count == 0) {
			os_free(tls_global);
			tls_global = NULL;
		}
	}
	wolfSSL_SetIORecv(ssl_ctx, wolfssl_receive_cb);
	wolfSSL_SetIOSend(ssl_ctx, wolfssl_send_cb);
	wolfSSL_CTX_set_ex_data(ssl_ctx, 0, context);

	if (conf->tls_session_lifetime > 0) {
		wolfSSL_CTX_set_quiet_shutdown(ssl_ctx, 1);
		wolfSSL_CTX_set_session_cache_mode(ssl_ctx,
						   SSL_SESS_CACHE_SERVER);
		wolfSSL_CTX_set_timeout(ssl_ctx, conf->tls_session_lifetime);
		wolfSSL_CTX_sess_set_remove_cb(ssl_ctx, remove_session_cb);
	} else {
		wolfSSL_CTX_set_session_cache_mode(ssl_ctx,
						   SSL_SESS_CACHE_CLIENT);
	}

	if (conf && conf->openssl_ciphers)
		ciphers = conf->openssl_ciphers;
	else
		ciphers = "ALL";
	if (wolfSSL_CTX_set_cipher_list(ssl_ctx, ciphers) != 1) {
		wpa_printf(MSG_ERROR,
			   "wolfSSL: Failed to set cipher string '%s'",
			   ciphers);
		tls_deinit(ssl_ctx);
		return NULL;
	}

	return ssl_ctx;
}