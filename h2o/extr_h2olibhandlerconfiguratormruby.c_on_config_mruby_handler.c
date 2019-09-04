#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  scalar; } ;
struct TYPE_13__ {scalar_t__ line; int /*<<< orphan*/  filename; TYPE_1__ data; } ;
typedef  TYPE_2__ yoml_t ;
struct mruby_configurator_t {TYPE_8__* vars; } ;
struct TYPE_14__ {int /*<<< orphan*/  pathconf; } ;
typedef  TYPE_3__ h2o_configurator_context_t ;
struct TYPE_15__ {scalar_t__ configurator; } ;
typedef  TYPE_4__ h2o_configurator_command_t ;
struct TYPE_16__ {int lineno; int /*<<< orphan*/  path; int /*<<< orphan*/  source; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIZE_MAX ; 
 int /*<<< orphan*/  compile_test (int /*<<< orphan*/ ,TYPE_8__*,char*) ; 
 int /*<<< orphan*/  get_mrb (struct mruby_configurator_t*) ; 
 int /*<<< orphan*/  h2o_configurator_errprintf (TYPE_4__*,TYPE_2__*,char*,char*) ; 
 int /*<<< orphan*/  h2o_mruby_register (int /*<<< orphan*/ ,TYPE_8__*) ; 
 int /*<<< orphan*/  h2o_strdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int on_config_mruby_handler(h2o_configurator_command_t *cmd, h2o_configurator_context_t *ctx, yoml_t *node)
{
    struct mruby_configurator_t *self = (void *)cmd->configurator;

    /* set source */
    self->vars->source = h2o_strdup(NULL, node->data.scalar, SIZE_MAX);
    self->vars->path = node->filename;
    self->vars->lineno = (int)node->line + 1;

    /* check if there is any error in source */
    char errbuf[1024];
    if (!compile_test(get_mrb(self), self->vars, errbuf)) {
        h2o_configurator_errprintf(cmd, node, "ruby compile error:%s", errbuf);
        return -1;
    }

    /* register */
    h2o_mruby_register(ctx->pathconf, self->vars);

    return 0;
}