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
struct outside_network {int /*<<< orphan*/  sslctx; } ;
struct comm_point {int /*<<< orphan*/  ssl; int /*<<< orphan*/  ssl_shake_state; } ;
typedef  int /*<<< orphan*/  X509_VERIFY_PARAM ;

/* Variables and functions */
 int SSL_CTX_get_verify_mode (int /*<<< orphan*/ ) ; 
 int SSL_VERIFY_PEER ; 
 int /*<<< orphan*/ * SSL_get0_param (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_set1_host (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  X509_CHECK_FLAG_NO_PARTIAL_WILDCARDS ; 
 int /*<<< orphan*/  X509_VERIFY_PARAM_set1_host (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_VERIFY_PARAM_set_hostflags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  comm_point_tcp_win_bio_cb (struct comm_point*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  comm_ssl_shake_write ; 
 int /*<<< orphan*/  log_err (char*) ; 
 int /*<<< orphan*/  outgoing_ssl_fd (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static int
setup_comm_ssl(struct comm_point* cp, struct outside_network* outnet,
	int fd, char* host)
{
	cp->ssl = outgoing_ssl_fd(outnet->sslctx, fd);
	if(!cp->ssl) {
		log_err("cannot create SSL object");
		return 0;
	}
#ifdef USE_WINSOCK
	comm_point_tcp_win_bio_cb(cp, cp->ssl);
#endif
	cp->ssl_shake_state = comm_ssl_shake_write;
	/* https verification */
#ifdef HAVE_SSL_SET1_HOST
	if((SSL_CTX_get_verify_mode(outnet->sslctx)&SSL_VERIFY_PEER)) {
		/* because we set SSL_VERIFY_PEER, in netevent in
		 * ssl_handshake, it'll check if the certificate
		 * verification has succeeded */
		/* SSL_VERIFY_PEER is set on the sslctx */
		/* and the certificates to verify with are loaded into
		 * it with SSL_load_verify_locations or
		 * SSL_CTX_set_default_verify_paths */
		/* setting the hostname makes openssl verify the
		 * host name in the x509 certificate in the
		 * SSL connection*/
		if(!SSL_set1_host(cp->ssl, host)) {
			log_err("SSL_set1_host failed");
			return 0;
		}
	}
#elif defined(HAVE_X509_VERIFY_PARAM_SET1_HOST)
	/* openssl 1.0.2 has this function that can be used for
	 * set1_host like verification */
	if((SSL_CTX_get_verify_mode(outnet->sslctx)&SSL_VERIFY_PEER)) {
		X509_VERIFY_PARAM* param = SSL_get0_param(cp->ssl);
		X509_VERIFY_PARAM_set_hostflags(param, X509_CHECK_FLAG_NO_PARTIAL_WILDCARDS);
		if(!X509_VERIFY_PARAM_set1_host(param, host, strlen(host))) {
			log_err("X509_VERIFY_PARAM_set1_host failed");
			return 0;
		}
	}
#else
	(void)host;
#endif /* HAVE_SSL_SET1_HOST */
	return 1;
}