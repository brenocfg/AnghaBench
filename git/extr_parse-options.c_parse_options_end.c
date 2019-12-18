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
struct parse_opt_ctx_t {int flags; int total; size_t argc; int cpidx; int /*<<< orphan*/ ** out; int /*<<< orphan*/  argv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MOVE_ARRAY (int /*<<< orphan*/ **,int /*<<< orphan*/ ,size_t) ; 
 int PARSE_OPT_ONE_SHOT ; 

int parse_options_end(struct parse_opt_ctx_t *ctx)
{
	if (ctx->flags & PARSE_OPT_ONE_SHOT)
		return ctx->total - ctx->argc;

	MOVE_ARRAY(ctx->out + ctx->cpidx, ctx->argv, ctx->argc);
	ctx->out[ctx->cpidx + ctx->argc] = NULL;
	return ctx->cpidx + ctx->argc;
}