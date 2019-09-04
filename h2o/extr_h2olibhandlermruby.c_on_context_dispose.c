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
struct TYPE_2__ {int /*<<< orphan*/  super; } ;
typedef  TYPE_1__ h2o_mruby_handler_t ;
typedef  int /*<<< orphan*/  h2o_mruby_context_t ;
typedef  int /*<<< orphan*/  h2o_handler_t ;
typedef  int /*<<< orphan*/  h2o_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * h2o_context_get_handler_context (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void on_context_dispose(h2o_handler_t *_handler, h2o_context_t *ctx)
{
    h2o_mruby_handler_t *handler = (void *)_handler;
    h2o_mruby_context_t *handler_ctx = h2o_context_get_handler_context(ctx, &handler->super);

    if (handler_ctx == NULL)
        return;

    free(handler_ctx);
}