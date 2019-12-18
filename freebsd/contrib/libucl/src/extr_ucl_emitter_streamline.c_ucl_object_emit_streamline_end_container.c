#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ucl_emitter_streamline_stack {struct ucl_emitter_streamline_stack* next; int /*<<< orphan*/  obj; scalar_t__ is_array; } ;
struct ucl_emitter_context_streamline {struct ucl_emitter_streamline_stack* containers; TYPE_1__* ops; } ;
struct ucl_emitter_context {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* ucl_emitter_end_object ) (struct ucl_emitter_context*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* ucl_emitter_end_array ) (struct ucl_emitter_context*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 struct ucl_emitter_context_streamline* TO_STREAMLINE (struct ucl_emitter_context*) ; 
 int /*<<< orphan*/  free (struct ucl_emitter_streamline_stack*) ; 
 int /*<<< orphan*/  stub1 (struct ucl_emitter_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct ucl_emitter_context*,int /*<<< orphan*/ ) ; 

void
ucl_object_emit_streamline_end_container (struct ucl_emitter_context *ctx)
{
	struct ucl_emitter_context_streamline *sctx = TO_STREAMLINE(ctx);
	struct ucl_emitter_streamline_stack *st;

	if (sctx->containers != NULL) {
		st = sctx->containers;

		if (st->is_array) {
			sctx->ops->ucl_emitter_end_array (ctx, st->obj);
		}
		else {
			sctx->ops->ucl_emitter_end_object (ctx, st->obj);
		}
		sctx->containers = st->next;
		free (st);
	}
}