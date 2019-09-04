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
struct st_status_configurator {scalar_t__ duration_stats; int /*<<< orphan*/  stack; } ;
typedef  int /*<<< orphan*/  h2o_configurator_t ;
struct TYPE_3__ {int /*<<< orphan*/  globalconf; } ;
typedef  TYPE_1__ h2o_configurator_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  h2o_duration_stats_register (int /*<<< orphan*/ ) ; 

int on_exit_status(h2o_configurator_t *_conf, h2o_configurator_context_t *ctx, yoml_t *node)
{
    struct st_status_configurator *c = (void *)_conf;
    c->stack--;
    if (!c->stack && c->duration_stats) {
        h2o_duration_stats_register(ctx->globalconf);
    }
    return 0;
}