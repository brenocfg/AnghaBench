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
struct ub_ctx {struct ub_ctx* env; int /*<<< orphan*/  mods; int /*<<< orphan*/  cfg; int /*<<< orphan*/  seed_rnd; int /*<<< orphan*/ * qq_pipe; int /*<<< orphan*/ * rr_pipe; } ;

/* Variables and functions */
 int /*<<< orphan*/  config_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edns_known_options_delete (struct ub_ctx*) ; 
 int errno ; 
 int /*<<< orphan*/  free (struct ub_ctx*) ; 
 int /*<<< orphan*/  modstack_desetup (int /*<<< orphan*/ *,struct ub_ctx*) ; 
 void* tube_create () ; 
 int /*<<< orphan*/  tube_delete (int /*<<< orphan*/ *) ; 
 struct ub_ctx* ub_ctx_create_nopipe () ; 
 int /*<<< orphan*/  ub_randfree (int /*<<< orphan*/ ) ; 

struct ub_ctx* 
ub_ctx_create(void)
{
	struct ub_ctx* ctx = ub_ctx_create_nopipe();
	if(!ctx)
		return NULL;
	if((ctx->qq_pipe = tube_create()) == NULL) {
		int e = errno;
		ub_randfree(ctx->seed_rnd);
		config_delete(ctx->env->cfg);
		modstack_desetup(&ctx->mods, ctx->env);
		edns_known_options_delete(ctx->env);
		free(ctx->env);
		free(ctx);
		errno = e;
		return NULL;
	}
	if((ctx->rr_pipe = tube_create()) == NULL) {
		int e = errno;
		tube_delete(ctx->qq_pipe);
		ub_randfree(ctx->seed_rnd);
		config_delete(ctx->env->cfg);
		modstack_desetup(&ctx->mods, ctx->env);
		edns_known_options_delete(ctx->env);
		free(ctx->env);
		free(ctx);
		errno = e;
		return NULL;
	}
	return ctx;
}