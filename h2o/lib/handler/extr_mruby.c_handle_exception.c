#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/ * exc; } ;
typedef  TYPE_2__ mrb_state ;
struct TYPE_12__ {TYPE_8__* req; } ;
typedef  TYPE_3__ h2o_mruby_generator_t ;
struct TYPE_13__ {TYPE_1__* shared; } ;
typedef  TYPE_4__ h2o_mruby_context_t ;
struct TYPE_14__ {int /*<<< orphan*/ * _generator; } ;
struct TYPE_10__ {TYPE_2__* mrb; } ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_MRUBY_MODULE_NAME ; 
 int /*<<< orphan*/  RSTRING_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_error_printf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_req_log_error (TYPE_8__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_send_error_500 (TYPE_8__*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_inspect (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_obj_value (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void handle_exception(h2o_mruby_context_t *ctx, h2o_mruby_generator_t *generator)
{
    mrb_state *mrb = ctx->shared->mrb;
    assert(mrb->exc != NULL);

    if (generator == NULL || generator->req->_generator != NULL) {
        h2o_error_printf("mruby raised: %s\n", RSTRING_PTR(mrb_inspect(mrb, mrb_obj_value(mrb->exc))));
    } else {
        h2o_req_log_error(generator->req, H2O_MRUBY_MODULE_NAME, "mruby raised: %s\n",
                          RSTRING_PTR(mrb_inspect(mrb, mrb_obj_value(mrb->exc))));
        h2o_send_error_500(generator->req, "Internal Server Error", "Internal Server Error", 0);
    }
    mrb->exc = NULL;
}