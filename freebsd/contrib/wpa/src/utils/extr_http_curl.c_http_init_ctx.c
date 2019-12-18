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
struct xml_node_ctx {int dummy; } ;
struct http_ctx {int /*<<< orphan*/  ocsp; struct xml_node_ctx* xml; void* ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURL_GLOBAL_ALL ; 
 int /*<<< orphan*/  OPTIONAL_OCSP ; 
 int /*<<< orphan*/  curl_global_init (int /*<<< orphan*/ ) ; 
 struct http_ctx* os_zalloc (int) ; 

struct http_ctx * http_init_ctx(void *upper_ctx, struct xml_node_ctx *xml_ctx)
{
	struct http_ctx *ctx;

	ctx = os_zalloc(sizeof(*ctx));
	if (ctx == NULL)
		return NULL;
	ctx->ctx = upper_ctx;
	ctx->xml = xml_ctx;
	ctx->ocsp = OPTIONAL_OCSP;

	curl_global_init(CURL_GLOBAL_ALL);

	return ctx;
}