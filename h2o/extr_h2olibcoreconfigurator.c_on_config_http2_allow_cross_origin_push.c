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
struct st_core_configurator_t {TYPE_2__* vars; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  h2o_configurator_context_t ;
struct TYPE_8__ {scalar_t__ configurator; } ;
typedef  TYPE_3__ h2o_configurator_command_t ;
struct TYPE_6__ {int allow_cross_origin_push; } ;
struct TYPE_7__ {TYPE_1__ http2; } ;

/* Variables and functions */
 int h2o_configurator_get_one_of (TYPE_3__*,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int on_config_http2_allow_cross_origin_push(h2o_configurator_command_t *cmd, h2o_configurator_context_t *ctx, yoml_t *node)
{
    struct st_core_configurator_t *self = (void *)cmd->configurator;
    ssize_t on;

    if ((on = h2o_configurator_get_one_of(cmd, node, "OFF,ON")) == -1)
        return -1;
    self->vars->http2.allow_cross_origin_push = (int)on;

    return 0;
}