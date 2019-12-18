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
struct http_ctx {struct http_ctx* svc_client_key; struct http_ctx* svc_client_cert; int /*<<< orphan*/  svc_password; int /*<<< orphan*/  svc_username; struct http_ctx* svc_ca_fname; struct http_ctx* svc_address; struct http_ctx* curl_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_curl (struct http_ctx*) ; 
 int /*<<< orphan*/  curl_global_cleanup () ; 
 int /*<<< orphan*/  os_free (struct http_ctx*) ; 
 int /*<<< orphan*/  str_clear_free (int /*<<< orphan*/ ) ; 

void http_deinit_ctx(struct http_ctx *ctx)
{
	clear_curl(ctx);
	os_free(ctx->curl_buf);
	curl_global_cleanup();

	os_free(ctx->svc_address);
	os_free(ctx->svc_ca_fname);
	str_clear_free(ctx->svc_username);
	str_clear_free(ctx->svc_password);
	os_free(ctx->svc_client_cert);
	os_free(ctx->svc_client_key);

	os_free(ctx);
}