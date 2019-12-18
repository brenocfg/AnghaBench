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
struct http_ctx {int (* cert_cb ) (void*,struct http_cert*) ;void* cert_cb_ctx; } ;

/* Variables and functions */

void http_set_cert_cb(struct http_ctx *ctx,
		      int (*cb)(void *ctx, struct http_cert *cert),
		      void *cb_ctx)
{
	ctx->cert_cb = cb;
	ctx->cert_cb_ctx = cb_ctx;
}