#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  yoml_t ;
struct st_status_configurator {int duration_stats; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  h2o_configurator_context_t ;
struct TYPE_4__ {scalar_t__ configurator; } ;
typedef  TYPE_1__ h2o_configurator_command_t ;

/* Variables and functions */
 scalar_t__ h2o_configurator_get_one_of (TYPE_1__*,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int on_config_duration_stats(h2o_configurator_command_t *cmd, h2o_configurator_context_t *ctx, yoml_t *node)
{
    struct st_status_configurator *c = (void *)cmd->configurator;
    ssize_t ret;
    switch (ret = h2o_configurator_get_one_of(cmd, node, "OFF,ON")) {
    case 0: /* OFF */
    case 1: /* ON */
        c->duration_stats = (int)ret;
        return 0;
    default: /* error */
        return -1;
    }
}