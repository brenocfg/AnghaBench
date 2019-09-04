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
typedef  int /*<<< orphan*/  yoml_t ;
struct reproxy_configurator_t {TYPE_1__* vars; } ;
typedef  int /*<<< orphan*/  h2o_configurator_t ;
struct TYPE_5__ {int /*<<< orphan*/ * pathconf; } ;
typedef  TYPE_2__ h2o_configurator_context_t ;
struct TYPE_4__ {scalar_t__ enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  h2o_reproxy_register (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int on_config_exit(h2o_configurator_t *_self, h2o_configurator_context_t *ctx, yoml_t *node)
{
    struct reproxy_configurator_t *self = (void *)_self;

    if (ctx->pathconf != NULL && self->vars->enabled != 0)
        h2o_reproxy_register(ctx->pathconf);

    --self->vars;
    return 0;
}