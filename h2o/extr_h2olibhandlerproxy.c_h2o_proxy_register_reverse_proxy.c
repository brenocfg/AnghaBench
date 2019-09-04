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
struct TYPE_2__ {int supports_request_streaming; int /*<<< orphan*/  on_req; int /*<<< orphan*/  dispose; int /*<<< orphan*/  on_context_dispose; int /*<<< orphan*/  on_context_init; } ;
struct rp_handler_t {int /*<<< orphan*/ * sockpool; int /*<<< orphan*/  config; TYPE_1__ super; } ;
typedef  int /*<<< orphan*/  h2o_socketpool_t ;
typedef  int /*<<< orphan*/  h2o_proxy_config_vars_t ;
typedef  int /*<<< orphan*/  h2o_pathconf_t ;

/* Variables and functions */
 scalar_t__ h2o_create_handler (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  on_context_dispose ; 
 int /*<<< orphan*/  on_context_init ; 
 int /*<<< orphan*/  on_handler_dispose ; 
 int /*<<< orphan*/  on_req ; 

void h2o_proxy_register_reverse_proxy(h2o_pathconf_t *pathconf, h2o_proxy_config_vars_t *config, h2o_socketpool_t *sockpool)
{
    struct rp_handler_t *self = (void *)h2o_create_handler(pathconf, sizeof(*self));

    self->super.on_context_init = on_context_init;
    self->super.on_context_dispose = on_context_dispose;
    self->super.dispose = on_handler_dispose;
    self->super.on_req = on_req;
    self->super.supports_request_streaming = 1;
    self->config = *config;
    self->sockpool = sockpool;
}