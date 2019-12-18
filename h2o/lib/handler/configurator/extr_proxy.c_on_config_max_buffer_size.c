#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  yoml_t ;
struct proxy_configurator_t {TYPE_2__* vars; } ;
typedef  int /*<<< orphan*/  h2o_configurator_context_t ;
struct TYPE_8__ {scalar_t__ configurator; } ;
typedef  TYPE_3__ h2o_configurator_command_t ;
struct TYPE_6__ {int /*<<< orphan*/  max_buffer_size; } ;
struct TYPE_7__ {TYPE_1__ conf; } ;

/* Variables and functions */
 int h2o_configurator_scanf (TYPE_3__*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int on_config_max_buffer_size(h2o_configurator_command_t *cmd, h2o_configurator_context_t *ctx, yoml_t *node)
{
    struct proxy_configurator_t *self = (void *)cmd->configurator;
    return h2o_configurator_scanf(cmd, node, "%zu", &self->vars->conf.max_buffer_size);
}