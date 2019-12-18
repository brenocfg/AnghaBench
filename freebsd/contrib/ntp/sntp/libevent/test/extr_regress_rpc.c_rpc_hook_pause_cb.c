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
struct rpc_hook_ctx_ {int /*<<< orphan*/  ctx; int /*<<< orphan*/  vbase; } ;
typedef  int /*<<< orphan*/  evutil_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVRPC_CONTINUE ; 
 int /*<<< orphan*/  evrpc_resume_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  hook_pause_cb_called ; 

__attribute__((used)) static void
rpc_hook_pause_cb(evutil_socket_t fd, short what, void *arg)
{
	struct rpc_hook_ctx_ *ctx = arg;
	++hook_pause_cb_called;
	evrpc_resume_request(ctx->vbase, ctx->ctx, EVRPC_CONTINUE);
	free(arg);
}