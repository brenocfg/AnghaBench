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
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  SSL_CTX ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_clear_error () ; 
 int SSL_ERROR_WANT_READ ; 
 int SSL_ERROR_WANT_WRITE ; 
 int /*<<< orphan*/  SSL_MODE_AUTO_RETRY ; 
 int SSL_do_handshake (int /*<<< orphan*/ *) ; 
 int SSL_get_error (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * SSL_get_peer_certificate (int /*<<< orphan*/ *) ; 
 scalar_t__ SSL_get_verify_result (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SSL_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_set_connect_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_set_fd (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SSL_set_mode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ X509_V_OK ; 
 int /*<<< orphan*/  X509_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssl_err (char*) ; 

__attribute__((used)) static SSL*
setup_ssl(SSL_CTX* ctx, int fd)
{
	SSL* ssl;
	X509* x;
	int r;

	if(!ctx) return NULL;
	ssl = SSL_new(ctx);
	if(!ssl)
		ssl_err("could not SSL_new");
	SSL_set_connect_state(ssl);
	(void)SSL_set_mode(ssl, SSL_MODE_AUTO_RETRY);
	if(!SSL_set_fd(ssl, fd))
		ssl_err("could not SSL_set_fd");
	while(1) {
		ERR_clear_error();
		if( (r=SSL_do_handshake(ssl)) == 1)
			break;
		r = SSL_get_error(ssl, r);
		if(r != SSL_ERROR_WANT_READ && r != SSL_ERROR_WANT_WRITE)
			ssl_err("SSL handshake failed");
		/* wants to be called again */
	}

	/* check authenticity of server */
	if(SSL_get_verify_result(ssl) != X509_V_OK)
		ssl_err("SSL verification failed");
	x = SSL_get_peer_certificate(ssl);
	if(!x)
		ssl_err("Server presented no peer certificate");
	X509_free(x);

	return ssl;
}