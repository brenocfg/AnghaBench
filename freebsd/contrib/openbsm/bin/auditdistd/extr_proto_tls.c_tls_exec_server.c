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
 int /*<<< orphan*/  EX_CONFIG ; 
 int /*<<< orphan*/  EX_TEMPFAIL ; 
 int /*<<< orphan*/ * SSL_CTX_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_set_options (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SSL_FILETYPE_PEM ; 
 int SSL_OP_NO_SSLv2 ; 
 int SSL_OP_NO_SSLv3 ; 
 int SSL_accept (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_library_init () ; 
 int /*<<< orphan*/  SSL_load_error_strings () ; 
 int /*<<< orphan*/ * SSL_new (int /*<<< orphan*/ *) ; 
 int SSL_set_fd (int /*<<< orphan*/ *,int) ; 
 int SSL_use_RSAPrivateKey_file (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int SSL_use_certificate_file (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLS_server_method () ; 
 int /*<<< orphan*/  nonblock (int) ; 
 int /*<<< orphan*/  pjdlog_debug (int,char*) ; 
 int /*<<< orphan*/  pjdlog_debug_set (int) ; 
 int /*<<< orphan*/  pjdlog_exitx (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  pjdlog_prefix_set (char*) ; 
 scalar_t__ sandbox (char const*,int,char*) ; 
 int /*<<< orphan*/  setproctitle (char*) ; 
 int /*<<< orphan*/  ssl_check_error (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ssl_log_errors () ; 
 int /*<<< orphan*/  tls_loop (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
tls_exec_server(const char *user, int startfd, const char *privkey,
    const char *cert, int debuglevel)
{
	SSL_CTX *sslctx;
	SSL *ssl;
	int sockfd, tcpfd, ret;

	pjdlog_debug_set(debuglevel);
	pjdlog_prefix_set("[TLS sandbox] (server) ");
#ifdef HAVE_SETPROCTITLE
	setproctitle("[TLS sandbox] (server) ");
#endif

	sockfd = startfd;
	tcpfd = startfd + 1;

	SSL_load_error_strings();
	SSL_library_init();

	sslctx = SSL_CTX_new(TLS_server_method());
	if (sslctx == NULL)
		pjdlog_exitx(EX_TEMPFAIL, "SSL_CTX_new() failed.");

	SSL_CTX_set_options(sslctx, SSL_OP_NO_SSLv2 | SSL_OP_NO_SSLv3);

	ssl = SSL_new(sslctx);
	if (ssl == NULL)
		pjdlog_exitx(EX_TEMPFAIL, "SSL_new() failed.");

	if (SSL_use_RSAPrivateKey_file(ssl, privkey, SSL_FILETYPE_PEM) != 1) {
		ssl_log_errors();
		pjdlog_exitx(EX_CONFIG,
		    "SSL_use_RSAPrivateKey_file(%s) failed.", privkey);
	}

	if (SSL_use_certificate_file(ssl, cert, SSL_FILETYPE_PEM) != 1) {
		ssl_log_errors();
		pjdlog_exitx(EX_CONFIG, "SSL_use_certificate_file(%s) failed.",
		    cert);
	}

	if (sandbox(user, true, "proto_tls server") != 0)
		pjdlog_exitx(EX_CONFIG, "Unable to sandbox TLS server.");
	pjdlog_debug(1, "Privileges successfully dropped.");

	nonblock(sockfd);
	nonblock(tcpfd);

	if (SSL_set_fd(ssl, tcpfd) != 1)
		pjdlog_exitx(EX_TEMPFAIL, "SSL_set_fd() failed.");

	ret = SSL_accept(ssl);
	ssl_check_error(ssl, ret);

	tls_loop(sockfd, ssl);
}