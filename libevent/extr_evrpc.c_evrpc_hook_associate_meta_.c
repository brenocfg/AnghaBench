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
struct evrpc_hook_meta {struct evhttp_connection* evcon; } ;
struct evhttp_connection {int dummy; } ;

/* Variables and functions */
 struct evrpc_hook_meta* evrpc_hook_meta_new_ () ; 

__attribute__((used)) static void
evrpc_hook_associate_meta_(struct evrpc_hook_meta **pctx,
    struct evhttp_connection *evcon)
{
	struct evrpc_hook_meta *ctx = *pctx;
	if (ctx == NULL)
		*pctx = ctx = evrpc_hook_meta_new_();
	ctx->evcon = evcon;
}