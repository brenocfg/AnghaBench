#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * env; TYPE_1__* pathconf; } ;
typedef  TYPE_2__ h2o_configurator_context_t ;
struct TYPE_5__ {int /*<<< orphan*/ * env; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  h2o_mem_release_shared (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void destroy_context(h2o_configurator_context_t *ctx)
{
    if (ctx->env != NULL) {
        if (ctx->pathconf != NULL)
            ctx->pathconf->env = ctx->env;
        else
            h2o_mem_release_shared(ctx->env);
    }
    free(ctx);
}