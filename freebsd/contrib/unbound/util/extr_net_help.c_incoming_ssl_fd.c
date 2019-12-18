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
typedef  void SSL ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_MODE_AUTO_RETRY ; 
 int /*<<< orphan*/  SSL_free (void*) ; 
 void* SSL_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_set_accept_state (void*) ; 
 int /*<<< orphan*/  SSL_set_fd (void*,int) ; 
 int /*<<< orphan*/  SSL_set_mode (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_crypto_err (char*) ; 

void* incoming_ssl_fd(void* sslctx, int fd)
{
#ifdef HAVE_SSL
	SSL* ssl = SSL_new((SSL_CTX*)sslctx);
	if(!ssl) {
		log_crypto_err("could not SSL_new");
		return NULL;
	}
	SSL_set_accept_state(ssl);
	(void)SSL_set_mode(ssl, SSL_MODE_AUTO_RETRY);
	if(!SSL_set_fd(ssl, fd)) {
		log_crypto_err("could not SSL_set_fd");
		SSL_free(ssl);
		return NULL;
	}
	return ssl;
#else
	(void)sslctx; (void)fd;
	return NULL;
#endif
}