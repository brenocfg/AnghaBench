#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  yoml_t ;
struct mruby_configurator_t {int /*<<< orphan*/ * mrb; TYPE_2__* vars; } ;
typedef  int /*<<< orphan*/  h2o_configurator_t ;
struct TYPE_7__ {int /*<<< orphan*/ * parent; } ;
typedef  TYPE_3__ h2o_configurator_context_t ;
struct TYPE_5__ {scalar_t__ base; } ;
struct TYPE_6__ {TYPE_1__ source; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  mrb_close (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int on_config_exit(h2o_configurator_t *_self, h2o_configurator_context_t *ctx, yoml_t *node)
{
    struct mruby_configurator_t *self = (void *)_self;

    /* free if the to-be-exitted frame level contains a different source */
    if (self->vars[-1].source.base != self->vars[0].source.base)
        free(self->vars->source.base);

    --self->vars;

    /* release mrb only when global configuration exited */
    if (self->mrb != NULL && ctx->parent == NULL) {
        mrb_close(self->mrb);
        self->mrb = NULL;
    }

    return 0;
}