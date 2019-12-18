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
struct evrpc_hook_ctx {int /*<<< orphan*/  output_hooks; int /*<<< orphan*/  input_hooks; int /*<<< orphan*/  paused_requests; int /*<<< orphan*/  registered_rpcs; } ;
struct evrpc_hook {int dummy; } ;
struct evrpc_base {int /*<<< orphan*/  output_hooks; int /*<<< orphan*/  input_hooks; int /*<<< orphan*/  paused_requests; int /*<<< orphan*/  registered_rpcs; } ;
struct evrpc {int /*<<< orphan*/  uri; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVRPC_INPUT ; 
 int /*<<< orphan*/  EVRPC_OUTPUT ; 
 int /*<<< orphan*/  EVUTIL_ASSERT (int) ; 
 void* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct evrpc_hook_ctx*,int /*<<< orphan*/ ) ; 
 int evrpc_remove_hook (struct evrpc_hook_ctx*,int /*<<< orphan*/ ,struct evrpc_hook*) ; 
 int evrpc_unregister_rpc (struct evrpc_hook_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mm_free (struct evrpc_hook_ctx*) ; 
 int /*<<< orphan*/  next ; 

void
evrpc_free(struct evrpc_base *base)
{
	struct evrpc *rpc;
	struct evrpc_hook *hook;
	struct evrpc_hook_ctx *pause;
	int r;

	while ((rpc = TAILQ_FIRST(&base->registered_rpcs)) != NULL) {
		r = evrpc_unregister_rpc(base, rpc->uri);
		EVUTIL_ASSERT(r == 0);
	}
	while ((pause = TAILQ_FIRST(&base->paused_requests)) != NULL) {
		TAILQ_REMOVE(&base->paused_requests, pause, next);
		mm_free(pause);
	}
	while ((hook = TAILQ_FIRST(&base->input_hooks)) != NULL) {
		r = evrpc_remove_hook(base, EVRPC_INPUT, hook);
		EVUTIL_ASSERT(r);
	}
	while ((hook = TAILQ_FIRST(&base->output_hooks)) != NULL) {
		r = evrpc_remove_hook(base, EVRPC_OUTPUT, hook);
		EVUTIL_ASSERT(r);
	}
	mm_free(base);
}