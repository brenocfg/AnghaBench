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
typedef  int /*<<< orphan*/  yoml_t ;
struct compress_configurator_t {TYPE_1__* vars; } ;
typedef  int /*<<< orphan*/  h2o_configurator_context_t ;
struct TYPE_6__ {scalar_t__ configurator; } ;
typedef  TYPE_2__ h2o_configurator_command_t ;
struct TYPE_5__ {int /*<<< orphan*/  min_size; } ;

/* Variables and functions */
 int h2o_configurator_scanf (TYPE_2__*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int on_config_compress_min_size(h2o_configurator_command_t *cmd, h2o_configurator_context_t *ctx, yoml_t *node)
{
    struct compress_configurator_t *self = (void *)cmd->configurator;
    return h2o_configurator_scanf(cmd, node, "%zu", &self->vars->min_size);
}