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
struct ucl_emitter_context_streamline {int /*<<< orphan*/ * containers; } ;
struct ucl_emitter_context {int dummy; } ;

/* Variables and functions */
 struct ucl_emitter_context_streamline* TO_STREAMLINE (struct ucl_emitter_context*) ; 
 int /*<<< orphan*/  free (struct ucl_emitter_context_streamline*) ; 
 int /*<<< orphan*/  ucl_object_emit_streamline_end_container (struct ucl_emitter_context*) ; 

void
ucl_object_emit_streamline_finish (struct ucl_emitter_context *ctx)
{
	struct ucl_emitter_context_streamline *sctx = TO_STREAMLINE(ctx);

	while (sctx->containers != NULL) {
		ucl_object_emit_streamline_end_container (ctx);
	}

	free (sctx);
}