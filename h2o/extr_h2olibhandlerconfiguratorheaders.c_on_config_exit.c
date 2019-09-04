#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  yoml_t ;
struct headers_configurator_t {int /*<<< orphan*/ ** cmds; } ;
typedef  int /*<<< orphan*/  h2o_configurator_t ;
struct TYPE_3__ {int /*<<< orphan*/ * pathconf; } ;
typedef  TYPE_1__ h2o_configurator_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  h2o_headers_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_mem_addref_shared (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_mem_release_shared (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int on_config_exit(h2o_configurator_t *_self, h2o_configurator_context_t *ctx, yoml_t *node)
{
    struct headers_configurator_t *self = (void *)_self;

    if (ctx->pathconf != NULL && *self->cmds != NULL) {
        if (*self->cmds != NULL)
            h2o_mem_addref_shared(*self->cmds);
        h2o_headers_register(ctx->pathconf, *self->cmds);
    }

    if (*self->cmds != NULL)
        h2o_mem_release_shared(*self->cmds);
    --self->cmds;
    return 0;
}