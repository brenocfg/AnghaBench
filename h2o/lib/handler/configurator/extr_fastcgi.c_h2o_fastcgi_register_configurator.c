#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  exit; int /*<<< orphan*/  enter; } ;
struct fastcgi_configurator_t {TYPE_2__ super; TYPE_1__* vars; TYPE_1__* _vars_stack; } ;
typedef  int /*<<< orphan*/  h2o_globalconf_t ;
struct TYPE_3__ {scalar_t__ keepalive_timeout; int /*<<< orphan*/  io_timeout; } ;

/* Variables and functions */
 int H2O_CONFIGURATOR_FLAG_ALL_LEVELS ; 
 int H2O_CONFIGURATOR_FLAG_DEFERRED ; 
 int H2O_CONFIGURATOR_FLAG_EXPECT_SCALAR ; 
 int H2O_CONFIGURATOR_FLAG_EXTENSION ; 
 int H2O_CONFIGURATOR_FLAG_PATH ; 
 int /*<<< orphan*/  H2O_DEFAULT_FASTCGI_IO_TIMEOUT ; 
 scalar_t__ h2o_configurator_create (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  h2o_configurator_define_command (TYPE_2__*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  on_config_connect ; 
 int /*<<< orphan*/  on_config_document_root ; 
 int /*<<< orphan*/  on_config_enter ; 
 int /*<<< orphan*/  on_config_exit ; 
 int /*<<< orphan*/  on_config_send_delegated_uri ; 
 int /*<<< orphan*/  on_config_spawn ; 
 int /*<<< orphan*/  on_config_timeout_io ; 
 int /*<<< orphan*/  on_config_timeout_keepalive ; 

void h2o_fastcgi_register_configurator(h2o_globalconf_t *conf)
{
    struct fastcgi_configurator_t *c = (void *)h2o_configurator_create(conf, sizeof(*c));

    /* set default vars */
    c->vars = c->_vars_stack;
    c->vars->io_timeout = H2O_DEFAULT_FASTCGI_IO_TIMEOUT;
    c->vars->keepalive_timeout = 0;

    /* setup handlers */
    c->super.enter = on_config_enter;
    c->super.exit = on_config_exit;

    h2o_configurator_define_command(&c->super, "fastcgi.connect",
                                    H2O_CONFIGURATOR_FLAG_PATH | H2O_CONFIGURATOR_FLAG_EXTENSION | H2O_CONFIGURATOR_FLAG_DEFERRED,
                                    on_config_connect);
    h2o_configurator_define_command(&c->super, "fastcgi.spawn",
                                    H2O_CONFIGURATOR_FLAG_PATH | H2O_CONFIGURATOR_FLAG_EXTENSION | H2O_CONFIGURATOR_FLAG_DEFERRED,
                                    on_config_spawn);
    h2o_configurator_define_command(&c->super, "fastcgi.timeout.io",
                                    H2O_CONFIGURATOR_FLAG_ALL_LEVELS | H2O_CONFIGURATOR_FLAG_EXPECT_SCALAR, on_config_timeout_io);
    h2o_configurator_define_command(&c->super, "fastcgi.timeout.keepalive",
                                    H2O_CONFIGURATOR_FLAG_ALL_LEVELS | H2O_CONFIGURATOR_FLAG_EXPECT_SCALAR,
                                    on_config_timeout_keepalive);
    h2o_configurator_define_command(&c->super, "fastcgi.document_root",
                                    H2O_CONFIGURATOR_FLAG_ALL_LEVELS | H2O_CONFIGURATOR_FLAG_EXPECT_SCALAR,
                                    on_config_document_root);
    h2o_configurator_define_command(&c->super, "fastcgi.send-delegated-uri",
                                    H2O_CONFIGURATOR_FLAG_ALL_LEVELS | H2O_CONFIGURATOR_FLAG_EXPECT_SCALAR,
                                    on_config_send_delegated_uri);
}