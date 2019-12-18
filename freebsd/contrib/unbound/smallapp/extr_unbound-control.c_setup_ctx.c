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
struct config_file {int /*<<< orphan*/  control_cert_file; int /*<<< orphan*/  control_key_file; int /*<<< orphan*/  server_cert_file; scalar_t__ control_use_cert; } ;
typedef  int /*<<< orphan*/  SSL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_CTX_check_private_key (int /*<<< orphan*/ *) ; 
 int SSL_CTX_load_verify_locations (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SSL_CTX_new (int /*<<< orphan*/ ) ; 
 int SSL_CTX_set_options (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SSL_CTX_set_verify (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_use_PrivateKey_file (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_use_certificate_chain_file (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SSL_FILETYPE_PEM ; 
 int SSL_OP_NO_SSLv2 ; 
 int SSL_OP_NO_SSLv3 ; 
 int /*<<< orphan*/  SSL_VERIFY_PEER ; 
 int /*<<< orphan*/  SSLv23_client_method () ; 
 int /*<<< orphan*/  fatal_exit (char*) ; 
 char* fname_after_chroot (int /*<<< orphan*/ ,struct config_file*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ options_remote_is_address (struct config_file*) ; 
 int /*<<< orphan*/  ssl_err (char*) ; 
 int /*<<< orphan*/  ssl_path_err (char*,char*) ; 

__attribute__((used)) static SSL_CTX*
setup_ctx(struct config_file* cfg)
{
	char* s_cert=NULL, *c_key=NULL, *c_cert=NULL;
	SSL_CTX* ctx;

	if(!(options_remote_is_address(cfg) && cfg->control_use_cert))
		return NULL;
	s_cert = fname_after_chroot(cfg->server_cert_file, cfg, 1);
	c_key = fname_after_chroot(cfg->control_key_file, cfg, 1);
	c_cert = fname_after_chroot(cfg->control_cert_file, cfg, 1);
	if(!s_cert || !c_key || !c_cert)
		fatal_exit("out of memory");
	ctx = SSL_CTX_new(SSLv23_client_method());
	if(!ctx)
		ssl_err("could not allocate SSL_CTX pointer");
	if((SSL_CTX_set_options(ctx, SSL_OP_NO_SSLv2) & SSL_OP_NO_SSLv2)
		!= SSL_OP_NO_SSLv2)
		ssl_err("could not set SSL_OP_NO_SSLv2");
	if((SSL_CTX_set_options(ctx, SSL_OP_NO_SSLv3) & SSL_OP_NO_SSLv3)
		!= SSL_OP_NO_SSLv3)
		ssl_err("could not set SSL_OP_NO_SSLv3");
	if(!SSL_CTX_use_certificate_chain_file(ctx,c_cert))
		ssl_path_err("Error setting up SSL_CTX client cert", c_cert);
	if (!SSL_CTX_use_PrivateKey_file(ctx,c_key,SSL_FILETYPE_PEM))
		ssl_path_err("Error setting up SSL_CTX client key", c_key);
	if (!SSL_CTX_check_private_key(ctx))
		ssl_err("Error setting up SSL_CTX client key");
	if (SSL_CTX_load_verify_locations(ctx, s_cert, NULL) != 1)
		ssl_path_err("Error setting up SSL_CTX verify, server cert",
			     s_cert);
	SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER, NULL);

	free(s_cert);
	free(c_key);
	free(c_cert);
	return ctx;
}