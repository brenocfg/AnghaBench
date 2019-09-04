#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  yoml_t ;
struct TYPE_9__ {TYPE_3__* globalconf; } ;
typedef  TYPE_4__ h2o_configurator_context_t ;
typedef  int /*<<< orphan*/  h2o_configurator_command_t ;
struct TYPE_6__ {int /*<<< orphan*/  max_cwnd; } ;
struct TYPE_7__ {TYPE_1__ latency_optimization; } ;
struct TYPE_8__ {TYPE_2__ http2; } ;

/* Variables and functions */
 int h2o_configurator_scanf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int on_config_http2_latency_optimization_max_cwnd(h2o_configurator_command_t *cmd, h2o_configurator_context_t *ctx,
                                                         yoml_t *node)
{
    return h2o_configurator_scanf(cmd, node, "%u", &ctx->globalconf->http2.latency_optimization.max_cwnd);
}