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
struct http_ctx {scalar_t__ curl_buf_len; int /*<<< orphan*/ * curl_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_curl_buf(struct http_ctx *ctx)
{
	os_free(ctx->curl_buf);
	ctx->curl_buf = NULL;
	ctx->curl_buf_len = 0;
}