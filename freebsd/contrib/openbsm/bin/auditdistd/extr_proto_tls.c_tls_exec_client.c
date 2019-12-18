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
typedef  int uint8_t ;
struct proto_conn {int dummy; } ;
typedef  int /*<<< orphan*/  connected ;
typedef  int /*<<< orphan*/  SSL_CTX ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  EINTR ; 
 int /*<<< orphan*/  ENOBUFS ; 
 int /*<<< orphan*/  EX_CONFIG ; 
 int /*<<< orphan*/  EX_TEMPFAIL ; 
 int /*<<< orphan*/ * SSL_CTX_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_set_options (int /*<<< orphan*/ *,int) ; 
 int SSL_OP_NO_SSLv2 ; 
 int SSL_OP_NO_SSLv3 ; 
 long SSL_connect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_library_init () ; 
 int /*<<< orphan*/  SSL_load_error_strings () ; 
 int /*<<< orphan*/ * SSL_new (int /*<<< orphan*/ *) ; 
 int SSL_set_fd (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TLS_client_method () ; 
 int /*<<< orphan*/  bcopy (char*,char*,int) ; 
 int /*<<< orphan*/  block (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nonblock (int) ; 
 int /*<<< orphan*/  pjdlog_debug (int,char*) ; 
 int /*<<< orphan*/  pjdlog_debug_set (int) ; 
 int /*<<< orphan*/  pjdlog_exit (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pjdlog_exitx (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pjdlog_prefix_set (char*) ; 
 int proto_connect (char*,char*,int,struct proto_conn**) ; 
 int proto_descriptor (struct proto_conn*) ; 
 int /*<<< orphan*/  proto_set (char*,char const*) ; 
 scalar_t__ sandbox (char const*,int,char*,char const*) ; 
 int send (int,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setproctitle (char*) ; 
 int /*<<< orphan*/  ssl_check_error (int /*<<< orphan*/ *,int) ; 
 char* strdup (char const*) ; 
 int /*<<< orphan*/  tls_certificate_verify (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  tls_loop (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_fd (int,int) ; 

__attribute__((used)) static void
tls_exec_client(const char *user, int startfd, const char *srcaddr,
    const char *dstaddr, const char *fingerprint, const char *defport,
    int timeout, int debuglevel)
{
	struct proto_conn *tcp;
	char *saddr, *daddr;
	SSL_CTX *sslctx;
	SSL *ssl;
	long ret;
	int sockfd, tcpfd;
	uint8_t connected;

	pjdlog_debug_set(debuglevel);
	pjdlog_prefix_set("[TLS sandbox] (client) ");
#ifdef HAVE_SETPROCTITLE
	setproctitle("[TLS sandbox] (client) ");
#endif
	proto_set("tcp:port", defport);

	sockfd = startfd;

	/* Change tls:// to tcp://. */
	if (srcaddr == NULL) {
		saddr = NULL;
	} else {
		saddr = strdup(srcaddr);
		if (saddr == NULL)
			pjdlog_exitx(EX_TEMPFAIL, "Unable to allocate memory.");
		bcopy("tcp://", saddr, 6);
	}
	daddr = strdup(dstaddr);
	if (daddr == NULL)
		pjdlog_exitx(EX_TEMPFAIL, "Unable to allocate memory.");
	bcopy("tcp://", daddr, 6);

	/* Establish TCP connection. */
	if (proto_connect(saddr, daddr, timeout, &tcp) == -1)
		exit(EX_TEMPFAIL);

	SSL_load_error_strings();
	SSL_library_init();

	/*
	 * TODO: On FreeBSD we could move this below sandbox() once libc and
	 *       libcrypto use sysctl kern.arandom to obtain random data
	 *       instead of /dev/urandom and friends.
	 */
	sslctx = SSL_CTX_new(TLS_client_method());
	if (sslctx == NULL)
		pjdlog_exitx(EX_TEMPFAIL, "SSL_CTX_new() failed.");

	if (sandbox(user, true, "proto_tls client: %s", dstaddr) != 0)
		pjdlog_exitx(EX_CONFIG, "Unable to sandbox TLS client.");
	pjdlog_debug(1, "Privileges successfully dropped.");

	SSL_CTX_set_options(sslctx, SSL_OP_NO_SSLv2 | SSL_OP_NO_SSLv3);

	/* Load CA certs. */
	/* TODO */
	//SSL_CTX_load_verify_locations(sslctx, cacerts_file, NULL);

	ssl = SSL_new(sslctx);
	if (ssl == NULL)
		pjdlog_exitx(EX_TEMPFAIL, "SSL_new() failed.");

	tcpfd = proto_descriptor(tcp);

	block(tcpfd);

	if (SSL_set_fd(ssl, tcpfd) != 1)
		pjdlog_exitx(EX_TEMPFAIL, "SSL_set_fd() failed.");

	ret = SSL_connect(ssl);
	ssl_check_error(ssl, (int)ret);

	nonblock(sockfd);
	nonblock(tcpfd);

	tls_certificate_verify(ssl, fingerprint);

	/*
	 * The following byte is send to make proto_connect_wait() to work.
	 */
	connected = 1;
	for (;;) {
		switch (send(sockfd, &connected, sizeof(connected), 0)) {
		case -1:
			if (errno == EINTR || errno == ENOBUFS)
				continue;
			if (errno == EAGAIN) {
				(void)wait_for_fd(sockfd, -1);
				continue;
			}
			pjdlog_exit(EX_TEMPFAIL, "send() failed");
		case 0:
			pjdlog_debug(1, "Connection terminated.");
			exit(0);
		case 1:
			break;
		}
		break;
	}

	tls_loop(sockfd, ssl);
}