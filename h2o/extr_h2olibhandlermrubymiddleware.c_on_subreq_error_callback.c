#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  pool; } ;
struct st_mruby_subreq_t {int /*<<< orphan*/  error_stream; TYPE_2__ super; TYPE_1__* ctx; } ;
typedef  int /*<<< orphan*/  mrb_value ;
struct TYPE_17__ {int /*<<< orphan*/ * exc; } ;
typedef  TYPE_4__ mrb_state ;
struct TYPE_18__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;
typedef  TYPE_5__ h2o_iovec_t ;
struct TYPE_16__ {TYPE_4__* mrb; } ;
struct TYPE_14__ {TYPE_3__* shared; } ;

/* Variables and functions */
 int /*<<< orphan*/  RSTRING_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_5__ h2o_concat (int /*<<< orphan*/ *,TYPE_5__,TYPE_5__) ; 
 int /*<<< orphan*/  h2o_error_printf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_mruby_new_str (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_funcall (TYPE_4__*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_inspect (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_nil_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_obj_value (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void on_subreq_error_callback(void *data, h2o_iovec_t prefix, h2o_iovec_t msg)
{
    struct st_mruby_subreq_t *subreq = (void *)data;
    mrb_state *mrb = subreq->ctx->shared->mrb;

    assert(!mrb_nil_p(subreq->error_stream));

    h2o_iovec_t concat = h2o_concat(&subreq->super.pool, prefix, msg);
    mrb_value msgstr = h2o_mruby_new_str(mrb, concat.base, concat.len);
    mrb_funcall(mrb, subreq->error_stream, "write", 1, msgstr);
    if (mrb->exc != NULL) {
        h2o_error_printf("%s\n", RSTRING_PTR(mrb_inspect(mrb, mrb_obj_value(mrb->exc))));
        mrb->exc = NULL;
    }
}