#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ucl_object_t ;
struct ucl_emitter_context_streamline {TYPE_1__* ops; TYPE_2__* containers; } ;
struct ucl_emitter_context {int dummy; } ;
struct TYPE_4__ {int empty; scalar_t__ is_array; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* ucl_emitter_write_elt ) (struct ucl_emitter_context*,int /*<<< orphan*/  const*,int,int) ;} ;

/* Variables and functions */
 struct ucl_emitter_context_streamline* TO_STREAMLINE (struct ucl_emitter_context*) ; 
 int /*<<< orphan*/  stub1 (struct ucl_emitter_context*,int /*<<< orphan*/  const*,int,int) ; 

void
ucl_object_emit_streamline_add_object (
		struct ucl_emitter_context *ctx, const ucl_object_t *obj)
{
	struct ucl_emitter_context_streamline *sctx = TO_STREAMLINE(ctx);
	bool is_array = false, is_first = false;

	if (sctx->containers != NULL) {
		if (sctx->containers->is_array) {
			is_array = true;
		}
		if (sctx->containers->empty) {
			is_first = true;
			sctx->containers->empty = false;
		}
	}

	sctx->ops->ucl_emitter_write_elt (ctx, obj, is_first, !is_array);
}