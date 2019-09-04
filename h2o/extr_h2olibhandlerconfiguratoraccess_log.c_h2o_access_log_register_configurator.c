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
struct st_h2o_access_log_configurator_t {TYPE_1__ super; int /*<<< orphan*/  _handles_stack; int /*<<< orphan*/  handles; } ;
typedef  int /*<<< orphan*/  h2o_globalconf_t ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_CONFIGURATOR_FLAG_ALL_LEVELS ; 
 scalar_t__ h2o_configurator_create (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  h2o_configurator_define_command (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  on_config ; 
 int /*<<< orphan*/  on_config_enter ; 
 int /*<<< orphan*/  on_config_exit ; 

void h2o_access_log_register_configurator(h2o_globalconf_t *conf)
{
    struct st_h2o_access_log_configurator_t *self = (void *)h2o_configurator_create(conf, sizeof(*self));

    self->super.enter = on_config_enter;
    self->super.exit = on_config_exit;
    self->handles = self->_handles_stack;

    h2o_configurator_define_command(&self->super, "access-log", H2O_CONFIGURATOR_FLAG_ALL_LEVELS, on_config);
}