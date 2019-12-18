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
struct mruby_configurator_t {TYPE_1__ super; int /*<<< orphan*/  _vars_stack; int /*<<< orphan*/  vars; } ;
typedef  int /*<<< orphan*/  h2o_globalconf_t ;

/* Variables and functions */
 int H2O_CONFIGURATOR_FLAG_DEFERRED ; 
 int H2O_CONFIGURATOR_FLAG_EXPECT_SCALAR ; 
 int H2O_CONFIGURATOR_FLAG_PATH ; 
 scalar_t__ h2o_configurator_create (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  h2o_configurator_define_command (TYPE_1__*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  on_config_enter ; 
 int /*<<< orphan*/  on_config_exit ; 
 int /*<<< orphan*/  on_config_mruby_handler ; 
 int /*<<< orphan*/  on_config_mruby_handler_file ; 
 int /*<<< orphan*/  on_config_mruby_handler_path ; 

void h2o_mruby_register_configurator(h2o_globalconf_t *conf)
{
    struct mruby_configurator_t *c = (void *)h2o_configurator_create(conf, sizeof(*c));

    c->vars = c->_vars_stack;
    c->super.enter = on_config_enter;
    c->super.exit = on_config_exit;

    h2o_configurator_define_command(
        &c->super, "mruby.handler",
        H2O_CONFIGURATOR_FLAG_PATH | H2O_CONFIGURATOR_FLAG_DEFERRED | H2O_CONFIGURATOR_FLAG_EXPECT_SCALAR, on_config_mruby_handler);
    h2o_configurator_define_command(&c->super, "mruby.handler-file",
                                    H2O_CONFIGURATOR_FLAG_PATH | H2O_CONFIGURATOR_FLAG_DEFERRED |
                                        H2O_CONFIGURATOR_FLAG_EXPECT_SCALAR,
                                    on_config_mruby_handler_file);
    h2o_configurator_define_command(&c->super, "mruby.handler_path", H2O_CONFIGURATOR_FLAG_PATH | H2O_CONFIGURATOR_FLAG_DEFERRED,
                                    on_config_mruby_handler_path);
}