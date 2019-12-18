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
struct http_ctx {int /*<<< orphan*/  svc_client_key; int /*<<< orphan*/  svc_client_cert; int /*<<< orphan*/  svc_password; int /*<<< orphan*/  svc_username; int /*<<< orphan*/  svc_ca_fname; int /*<<< orphan*/  svc_address; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_curl (struct http_ctx*) ; 
 int /*<<< orphan*/  clone_str (char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 int soap_init_client (struct http_ctx*,char*,char*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  str_clear_free (char*) ; 

int soap_reinit_client(struct http_ctx *ctx)
{
	char *address = NULL;
	char *ca_fname = NULL;
	char *username = NULL;
	char *password = NULL;
	char *client_cert = NULL;
	char *client_key = NULL;
	int ret;

	clear_curl(ctx);

	clone_str(&address, ctx->svc_address);
	clone_str(&ca_fname, ctx->svc_ca_fname);
	clone_str(&username, ctx->svc_username);
	clone_str(&password, ctx->svc_password);
	clone_str(&client_cert, ctx->svc_client_cert);
	clone_str(&client_key, ctx->svc_client_key);

	ret = soap_init_client(ctx, address, ca_fname, username, password,
			       client_cert, client_key);
	os_free(address);
	os_free(ca_fname);
	str_clear_free(username);
	str_clear_free(password);
	os_free(client_cert);
	os_free(client_key);
	return ret;
}