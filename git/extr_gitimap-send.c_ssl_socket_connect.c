#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct imap_socket {int /*<<< orphan*/  ssl; int /*<<< orphan*/ * fd; } ;
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_2__ {int /*<<< orphan*/  host; } ;
typedef  int /*<<< orphan*/  SSL_METHOD ;
typedef  int /*<<< orphan*/  SSL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/ * SSL_CTX_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_set_default_verify_paths (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_set_options (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SSL_CTX_set_verify (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int SSL_OP_NO_SSLv2 ; 
 int SSL_OP_NO_SSLv3 ; 
 int /*<<< orphan*/  SSL_VERIFY_PEER ; 
 int SSL_connect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SSL_get_peer_certificate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_library_init () ; 
 int /*<<< orphan*/  SSL_load_error_strings () ; 
 int /*<<< orphan*/  SSL_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_set_rfd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_set_wfd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SSLv23_method () ; 
 int error (char*) ; 
 TYPE_1__ server ; 
 int /*<<< orphan*/  socket_perror (char*,struct imap_socket*,int) ; 
 int /*<<< orphan*/  ssl_socket_perror (char*) ; 
 scalar_t__ verify_hostname (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ssl_socket_connect(struct imap_socket *sock, int use_tls_only, int verify)
{
#if (OPENSSL_VERSION_NUMBER >= 0x10000000L)
	const SSL_METHOD *meth;
#else
	SSL_METHOD *meth;
#endif
	SSL_CTX *ctx;
	int ret;
	X509 *cert;

	SSL_library_init();
	SSL_load_error_strings();

	meth = SSLv23_method();
	if (!meth) {
		ssl_socket_perror("SSLv23_method");
		return -1;
	}

	ctx = SSL_CTX_new(meth);
	if (!ctx) {
		ssl_socket_perror("SSL_CTX_new");
		return -1;
	}

	if (use_tls_only)
		SSL_CTX_set_options(ctx, SSL_OP_NO_SSLv2 | SSL_OP_NO_SSLv3);

	if (verify)
		SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER, NULL);

	if (!SSL_CTX_set_default_verify_paths(ctx)) {
		ssl_socket_perror("SSL_CTX_set_default_verify_paths");
		return -1;
	}
	sock->ssl = SSL_new(ctx);
	if (!sock->ssl) {
		ssl_socket_perror("SSL_new");
		return -1;
	}
	if (!SSL_set_rfd(sock->ssl, sock->fd[0])) {
		ssl_socket_perror("SSL_set_rfd");
		return -1;
	}
	if (!SSL_set_wfd(sock->ssl, sock->fd[1])) {
		ssl_socket_perror("SSL_set_wfd");
		return -1;
	}

#ifdef SSL_CTRL_SET_TLSEXT_HOSTNAME
	/*
	 * SNI (RFC4366)
	 * OpenSSL does not document this function, but the implementation
	 * returns 1 on success, 0 on failure after calling SSLerr().
	 */
	ret = SSL_set_tlsext_host_name(sock->ssl, server.host);
	if (ret != 1)
		warning("SSL_set_tlsext_host_name(%s) failed.", server.host);
#endif

	ret = SSL_connect(sock->ssl);
	if (ret <= 0) {
		socket_perror("SSL_connect", sock, ret);
		return -1;
	}

	if (verify) {
		/* make sure the hostname matches that of the certificate */
		cert = SSL_get_peer_certificate(sock->ssl);
		if (!cert)
			return error("unable to get peer certificate.");
		if (verify_hostname(cert, server.host) < 0)
			return -1;
	}

	return 0;
}