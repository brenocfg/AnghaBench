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
struct http_ctx {int /*<<< orphan*/ * curl_hdr; int /*<<< orphan*/ * curl; } ;

/* Variables and functions */
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_slist_free_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void clear_curl(struct http_ctx *ctx)
{
	if (ctx->curl) {
		curl_easy_cleanup(ctx->curl);
		ctx->curl = NULL;
	}
	if (ctx->curl_hdr) {
		curl_slist_free_all(ctx->curl_hdr);
		ctx->curl_hdr = NULL;
	}
}