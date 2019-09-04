#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * env; TYPE_1__* parent; } ;
typedef  TYPE_2__ h2o_configurator_context_t ;
struct TYPE_4__ {int /*<<< orphan*/ * env; } ;

/* Variables and functions */
 int /*<<< orphan*/ * h2o_config_create_envconf (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void inherit_env_if_necessary(h2o_configurator_context_t *ctx)
{
    if (ctx->env == (ctx->parent != NULL ? ctx->parent->env : NULL))
        ctx->env = h2o_config_create_envconf(ctx->env);
}