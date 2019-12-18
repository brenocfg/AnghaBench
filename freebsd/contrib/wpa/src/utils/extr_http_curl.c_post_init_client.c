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
struct http_ctx {char* svc_address; char* svc_ca_fname; char* svc_username; char* svc_password; char* svc_client_cert; char* svc_client_key; int /*<<< orphan*/ * curl; } ;

/* Variables and functions */
 int /*<<< orphan*/  clone_str (char**,char const*) ; 
 int /*<<< orphan*/ * setup_curl_post (struct http_ctx*,char*,char const*,char const*,char const*,char const*,char const*) ; 
 char tolower (char) ; 

__attribute__((used)) static int post_init_client(struct http_ctx *ctx, const char *address,
			    const char *ca_fname, const char *username,
			    const char *password, const char *client_cert,
			    const char *client_key)
{
	char *pos;
	int count;

	clone_str(&ctx->svc_address, address);
	clone_str(&ctx->svc_ca_fname, ca_fname);
	clone_str(&ctx->svc_username, username);
	clone_str(&ctx->svc_password, password);
	clone_str(&ctx->svc_client_cert, client_cert);
	clone_str(&ctx->svc_client_key, client_key);

	/*
	 * Workaround for Apache "Hostname 'FOO' provided via SNI and hostname
	 * 'foo' provided via HTTP are different.
	 */
	for (count = 0, pos = ctx->svc_address; count < 3 && pos && *pos;
	     pos++) {
		if (*pos == '/')
			count++;
		*pos = tolower(*pos);
	}

	ctx->curl = setup_curl_post(ctx, ctx->svc_address, ca_fname, username,
				    password, client_cert, client_key);
	if (ctx->curl == NULL)
		return -1;

	return 0;
}