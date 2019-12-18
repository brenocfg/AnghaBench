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
typedef  int /*<<< orphan*/  ucl_object_t ;
struct ucl_emitter_functions {int /*<<< orphan*/  ud; int /*<<< orphan*/  (* ucl_emitter_append_character ) (char,int,int /*<<< orphan*/ ) ;} ;
struct ucl_emitter_context {scalar_t__ id; int /*<<< orphan*/  indent; struct ucl_emitter_functions* func; } ;

/* Variables and functions */
 scalar_t__ UCL_EMIT_CONFIG ; 
 scalar_t__ UCL_EMIT_IDENT_TOP_OBJ (struct ucl_emitter_context*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  stub1 (char,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (char,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (char,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ucl_add_tabs (struct ucl_emitter_functions const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ucl_emitter_finish_object (struct ucl_emitter_context*,int /*<<< orphan*/  const*,int,int) ; 

__attribute__((used)) static void
ucl_emitter_common_end_object (struct ucl_emitter_context *ctx,
		const ucl_object_t *obj, bool compact)
{
	const struct ucl_emitter_functions *func = ctx->func;

	if (UCL_EMIT_IDENT_TOP_OBJ(ctx, obj)) {
		ctx->indent --;
		if (compact) {
			func->ucl_emitter_append_character ('}', 1, func->ud);
		}
		else {
			if (ctx->id != UCL_EMIT_CONFIG) {
				/* newline is already added for this format */
				func->ucl_emitter_append_character ('\n', 1, func->ud);
			}
			ucl_add_tabs (func, ctx->indent, compact);
			func->ucl_emitter_append_character ('}', 1, func->ud);
		}
	}

	ucl_emitter_finish_object (ctx, obj, compact, false);
}