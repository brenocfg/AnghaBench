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
struct TYPE_3__ {int /*<<< orphan*/  hostconf; } ;
typedef  TYPE_1__ h2o_configurator_context_t ;
typedef  int /*<<< orphan*/  h2o_configurator_command_t ;

/* Variables and functions */
 int h2o_configurator_get_one_of (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  h2o_http2_debug_state_register (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int on_config_debug_state(h2o_configurator_command_t *cmd, h2o_configurator_context_t *ctx, yoml_t *node)
{
    switch (h2o_configurator_get_one_of(cmd, node, "minimum,hpack")) {
    case 0: /* minimum */
        h2o_http2_debug_state_register(ctx->hostconf, 0);
        return 0;
    case 1: /* with hpack state*/
        h2o_http2_debug_state_register(ctx->hostconf, 1);
        return 0;
    default: /* error */
        return -1;
    }
}