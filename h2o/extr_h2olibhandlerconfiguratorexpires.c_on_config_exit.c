#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  yoml_t ;
struct expires_configurator_t {TYPE_3__** args; } ;
typedef  int /*<<< orphan*/  h2o_configurator_t ;
struct TYPE_5__ {int /*<<< orphan*/ * pathconf; } ;
typedef  TYPE_1__ h2o_configurator_context_t ;
struct TYPE_6__ {scalar_t__ mode; } ;

/* Variables and functions */
 scalar_t__ H2O_EXPIRES_MODE_MAX_AGE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int /*<<< orphan*/  h2o_expires_register (int /*<<< orphan*/ *,TYPE_3__*) ; 

__attribute__((used)) static int on_config_exit(h2o_configurator_t *_self, h2o_configurator_context_t *ctx, yoml_t *node)
{
    struct expires_configurator_t *self = (void *)_self;

    if (*self->args != NULL) {
        /* setup */
        if (ctx->pathconf != NULL) {
            h2o_expires_register(ctx->pathconf, *self->args);
        }
        /* destruct */
        assert((*self->args)->mode == H2O_EXPIRES_MODE_MAX_AGE);
        free(*self->args);
        *self->args = NULL;
    }

    --self->args;
    return 0;
}