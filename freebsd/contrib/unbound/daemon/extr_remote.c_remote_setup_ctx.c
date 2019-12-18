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
struct daemon_remote {int /*<<< orphan*/  ctx; } ;
struct config_file {int /*<<< orphan*/  server_key_file; int /*<<< orphan*/  server_cert_file; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_CTX_check_private_key (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_load_verify_locations (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_set_client_CA_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_set_verify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_use_PrivateKey_file (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_use_certificate_chain_file (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SSL_FILETYPE_PEM ; 
 int /*<<< orphan*/  SSL_VERIFY_PEER ; 
 int /*<<< orphan*/  SSL_load_client_CA_file (char*) ; 
 int /*<<< orphan*/  SSLv23_server_method () ; 
 int /*<<< orphan*/  VERB_ALGO ; 
 char* fname_after_chroot (int /*<<< orphan*/ ,struct config_file*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  listen_sslctx_setup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  listen_sslctx_setup_2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_crypto_err (char*) ; 
 int /*<<< orphan*/  log_err (char*,...) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
remote_setup_ctx(struct daemon_remote* rc, struct config_file* cfg)
{
	char* s_cert;
	char* s_key;
	rc->ctx = SSL_CTX_new(SSLv23_server_method());
	if(!rc->ctx) {
		log_crypto_err("could not SSL_CTX_new");
		return 0;
	}
	if(!listen_sslctx_setup(rc->ctx)) {
		return 0;
	}

	s_cert = fname_after_chroot(cfg->server_cert_file, cfg, 1);
	s_key = fname_after_chroot(cfg->server_key_file, cfg, 1);
	if(!s_cert || !s_key) {
		log_err("out of memory in remote control fname");
		goto setup_error;
	}
	verbose(VERB_ALGO, "setup SSL certificates");
	if (!SSL_CTX_use_certificate_chain_file(rc->ctx,s_cert)) {
		log_err("Error for server-cert-file: %s", s_cert);
		log_crypto_err("Error in SSL_CTX use_certificate_chain_file");
		goto setup_error;
	}
	if(!SSL_CTX_use_PrivateKey_file(rc->ctx,s_key,SSL_FILETYPE_PEM)) {
		log_err("Error for server-key-file: %s", s_key);
		log_crypto_err("Error in SSL_CTX use_PrivateKey_file");
		goto setup_error;
	}
	if(!SSL_CTX_check_private_key(rc->ctx)) {
		log_err("Error for server-key-file: %s", s_key);
		log_crypto_err("Error in SSL_CTX check_private_key");
		goto setup_error;
	}
	listen_sslctx_setup_2(rc->ctx);
	if(!SSL_CTX_load_verify_locations(rc->ctx, s_cert, NULL)) {
		log_crypto_err("Error setting up SSL_CTX verify locations");
	setup_error:
		free(s_cert);
		free(s_key);
		return 0;
	}
	SSL_CTX_set_client_CA_list(rc->ctx, SSL_load_client_CA_file(s_cert));
	SSL_CTX_set_verify(rc->ctx, SSL_VERIFY_PEER, NULL);
	free(s_cert);
	free(s_key);
	return 1;
}