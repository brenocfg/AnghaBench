#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mrb_value ;
struct TYPE_17__ {int /*<<< orphan*/  kernel_module; } ;
typedef  TYPE_4__ mrb_state ;
struct TYPE_18__ {TYPE_1__* handler; TYPE_3__* shared; } ;
typedef  TYPE_5__ h2o_mruby_context_t ;
struct TYPE_15__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;
struct TYPE_19__ {int /*<<< orphan*/  lineno; int /*<<< orphan*/  path; TYPE_2__ source; } ;
typedef  TYPE_6__ h2o_mruby_config_vars_t ;
struct TYPE_16__ {TYPE_4__* mrb; } ;
struct TYPE_14__ {TYPE_6__ config; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_mruby_assert (TYPE_4__*) ; 
 int /*<<< orphan*/  h2o_mruby_new_str (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_array_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_fixnum_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_funcall (TYPE_4__*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_hash_new_capa (TYPE_4__*,int) ; 
 int /*<<< orphan*/  mrb_hash_set (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_intern_lit (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  mrb_obj_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_symbol_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

mrb_value prepare_fibers(h2o_mruby_context_t *ctx)
{
    mrb_state *mrb = ctx->shared->mrb;

    h2o_mruby_config_vars_t config = ctx->handler->config;
    mrb_value conf = mrb_hash_new_capa(mrb, 3);
    mrb_hash_set(mrb, conf, mrb_symbol_value(mrb_intern_lit(mrb, "code")),
                 h2o_mruby_new_str(mrb, config.source.base, config.source.len));
    mrb_hash_set(mrb, conf, mrb_symbol_value(mrb_intern_lit(mrb, "file")),
                 h2o_mruby_new_str(mrb, config.path, strlen(config.path)));
    mrb_hash_set(mrb, conf, mrb_symbol_value(mrb_intern_lit(mrb, "line")), mrb_fixnum_value(config.lineno));

    /* run code and generate handler */
    mrb_value result = mrb_funcall(mrb, mrb_obj_value(mrb->kernel_module), "_h2o_prepare_app", 1, conf);
    h2o_mruby_assert(mrb);
    assert(mrb_array_p(result));

    return result;
}