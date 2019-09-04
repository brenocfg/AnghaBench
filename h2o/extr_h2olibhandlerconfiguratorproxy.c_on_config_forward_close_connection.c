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
typedef  int ssize_t ;
struct TYPE_7__ {TYPE_2__* globalconf; } ;
typedef  TYPE_3__ h2o_configurator_context_t ;
typedef  int /*<<< orphan*/  h2o_configurator_command_t ;
struct TYPE_5__ {int forward_close_connection; } ;
struct TYPE_6__ {TYPE_1__ proxy; } ;

/* Variables and functions */
 int h2o_configurator_get_one_of (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int on_config_forward_close_connection(h2o_configurator_command_t *cmd, h2o_configurator_context_t *ctx, yoml_t *node)
{
    ssize_t ret = h2o_configurator_get_one_of(cmd, node, "OFF,ON");
    if (ret == -1)
        return -1;
    ctx->globalconf->proxy.forward_close_connection = (int)ret;
    return 0;
}