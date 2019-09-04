#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mrb_value ;
struct TYPE_13__ {int /*<<< orphan*/  exc; int /*<<< orphan*/  ud; } ;
typedef  TYPE_2__ mrb_state ;
struct TYPE_14__ {TYPE_8__* req; } ;
typedef  TYPE_3__ h2o_mruby_generator_t ;
struct TYPE_12__ {int status; } ;
struct TYPE_15__ {TYPE_1__ res; } ;

/* Variables and functions */
 TYPE_3__* h2o_mruby_get_generator (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int h2o_mruby_iterate_rack_headers (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_8__*) ; 
 int /*<<< orphan*/  h2o_send_informational (TYPE_8__*) ; 
 int /*<<< orphan*/  handle_early_hints_header ; 
 int /*<<< orphan*/  mrb_exc_raise (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_get_args (TYPE_2__*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 
 int /*<<< orphan*/  mrb_obj_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_proc_cfunc_env_get (TYPE_2__*,int /*<<< orphan*/ ) ; 

mrb_value send_early_hints_proc(mrb_state *mrb, mrb_value self)
{
    mrb_value headers;
    mrb_get_args(mrb, "H", &headers);

    h2o_mruby_generator_t *generator = h2o_mruby_get_generator(mrb, mrb_proc_cfunc_env_get(mrb, 0));
    if (generator == NULL)
        return mrb_nil_value();

    if (h2o_mruby_iterate_rack_headers(mrb->ud, headers, handle_early_hints_header, generator->req) == -1)
        mrb_exc_raise(mrb, mrb_obj_value(mrb->exc));
    generator->req->res.status = 103;
    h2o_send_informational(generator->req);

    return mrb_nil_value();
}