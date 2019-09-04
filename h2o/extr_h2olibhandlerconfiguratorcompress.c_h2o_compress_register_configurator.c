#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  exit; int /*<<< orphan*/  enter; } ;
struct compress_configurator_t {TYPE_3__* vars; TYPE_3__* _vars_stack; TYPE_4__ super; } ;
typedef  int /*<<< orphan*/  h2o_globalconf_t ;
struct TYPE_6__ {int quality; } ;
struct TYPE_5__ {int quality; } ;
struct TYPE_7__ {TYPE_2__ brotli; TYPE_1__ gzip; } ;

/* Variables and functions */
 int H2O_CONFIGURATOR_FLAG_ALL_LEVELS ; 
 int H2O_CONFIGURATOR_FLAG_EXPECT_SCALAR ; 
 scalar_t__ h2o_configurator_create (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  h2o_configurator_define_command (TYPE_4__*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  on_config_compress ; 
 int /*<<< orphan*/  on_config_compress_min_size ; 
 int /*<<< orphan*/  on_config_enter ; 
 int /*<<< orphan*/  on_config_exit ; 
 int /*<<< orphan*/  on_config_gzip ; 

void h2o_compress_register_configurator(h2o_globalconf_t *conf)
{
    struct compress_configurator_t *c = (void *)h2o_configurator_create(conf, sizeof(*c));

    c->super.enter = on_config_enter;
    c->super.exit = on_config_exit;
    h2o_configurator_define_command(&c->super, "compress", H2O_CONFIGURATOR_FLAG_ALL_LEVELS, on_config_compress);
    h2o_configurator_define_command(&c->super, "compress-minimum-size",
                                    H2O_CONFIGURATOR_FLAG_ALL_LEVELS | H2O_CONFIGURATOR_FLAG_EXPECT_SCALAR,
                                    on_config_compress_min_size);
    h2o_configurator_define_command(&c->super, "gzip", H2O_CONFIGURATOR_FLAG_ALL_LEVELS | H2O_CONFIGURATOR_FLAG_EXPECT_SCALAR,
                                    on_config_gzip);
    c->vars = c->_vars_stack;
    c->vars->gzip.quality = -1;
    c->vars->brotli.quality = -1;
}