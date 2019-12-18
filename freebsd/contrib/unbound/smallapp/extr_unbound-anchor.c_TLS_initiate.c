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
 int /*<<< orphan*/  SSL_free (int /*<<< orphan*/ *) ; 
 int SSL_get_error (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * SSL_get_peer_certificate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SSL_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_set_connect_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_set_fd (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SSL_set_mode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ verb ; 
 int /*<<< orphan*/  verb_cert (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static SSL*
TLS_initiate(SSL_CTX* sslctx, int fd)
{
	X509* x;
	int r;
	SSL* ssl = SSL_new(sslctx);
	if(!ssl) {
		if(verb) printf("SSL_new error\n");
		return NULL;
	}
	SSL_set_connect_state(ssl);
	(void)SSL_set_mode(ssl, SSL_MODE_AUTO_RETRY);
	if(!SSL_set_fd(ssl, fd)) {
		if(verb) printf("SSL_set_fd error\n");
		SSL_free(ssl);
		return NULL;
	}
	while(1) {
		ERR_clear_error();
		if( (r=SSL_do_handshake(ssl)) == 1)
			break;
		r = SSL_get_error(ssl, r);
		if(r != SSL_ERROR_WANT_READ && r != SSL_ERROR_WANT_WRITE) {
			if(verb) printf("SSL handshake failed\n");
			SSL_free(ssl);
			return NULL;
		}
		/* wants to be called again */
	}
	x = SSL_get_peer_certificate(ssl);
	if(!x) {
		if(verb) printf("Server presented no peer certificate\n");
		SSL_free(ssl);
		return NULL;
	}
	verb_cert("server SSL certificate", x);
	X509_free(x);
	return ssl;
}