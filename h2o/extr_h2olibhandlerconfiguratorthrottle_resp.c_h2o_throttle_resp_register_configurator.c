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
struct TYPE_2__ {int /*<<< orphan*/  exit; int /*<<< orphan*/  enter; } ;
struct throttle_resp_configurator_t {int /*<<< orphan*/  _vars_stack; int /*<<< orphan*/  vars; TYPE_1__ super; } ;
typedef  int /*<<< orphan*/  h2o_globalconf_t ;

/* Variables and functions */
 int H2O_CONFIGURATOR_FLAG_ALL_LEVELS ; 
 int H2O_CONFIGURATOR_FLAG_EXPECT_SCALAR ; 
 scalar_t__ h2o_configurator_create (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  h2o_configurator_define_command (TYPE_1__*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  on_config_enter ; 
 int /*<<< orphan*/  on_config_exit ; 
 int /*<<< orphan*/  on_config_throttle_resp ; 

void h2o_throttle_resp_register_configurator(h2o_globalconf_t *conf)
{
    struct throttle_resp_configurator_t *c = (void *)h2o_configurator_create(conf, sizeof(*c));

    c->super.enter = on_config_enter;
    c->super.exit = on_config_exit;
    h2o_configurator_define_command(&c->super, "throttle-response",
                                    H2O_CONFIGURATOR_FLAG_ALL_LEVELS | H2O_CONFIGURATOR_FLAG_EXPECT_SCALAR,
                                    on_config_throttle_resp);
    c->vars = c->_vars_stack;
}