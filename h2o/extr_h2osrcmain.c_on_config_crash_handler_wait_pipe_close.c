#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  yoml_t ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  h2o_configurator_context_t ;
typedef  int /*<<< orphan*/  h2o_configurator_command_t ;
struct TYPE_2__ {int crash_handler_wait_pipe_close; } ;

/* Variables and functions */
 TYPE_1__ conf ; 
 int h2o_configurator_get_one_of (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int on_config_crash_handler_wait_pipe_close(h2o_configurator_command_t *cmd, h2o_configurator_context_t *ctx, yoml_t *node)
{
    ssize_t v;

    if ((v = h2o_configurator_get_one_of(cmd, node, "OFF,ON")) == -1)
        return -1;

    conf.crash_handler_wait_pipe_close = (int)v;
    return 0;
}