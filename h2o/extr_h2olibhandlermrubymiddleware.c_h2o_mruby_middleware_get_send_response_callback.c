#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct st_mruby_subreq_t {int dummy; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int /*<<< orphan*/ * h2o_mruby_send_response_callback_t ;
struct TYPE_5__ {TYPE_1__* shared; } ;
typedef  TYPE_2__ h2o_mruby_context_t ;
struct TYPE_4__ {int /*<<< orphan*/ * mrb; } ;

/* Variables and functions */
 int /*<<< orphan*/  app_request_type ; 
 struct st_mruby_subreq_t* mrb_data_check_get_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * send_response_callback ; 

h2o_mruby_send_response_callback_t h2o_mruby_middleware_get_send_response_callback(h2o_mruby_context_t *ctx, mrb_value resp)
{
    mrb_state *mrb = ctx->shared->mrb;
    struct st_mruby_subreq_t *subreq;
    if ((subreq = mrb_data_check_get_ptr(mrb, resp, &app_request_type)) == NULL)
        return NULL;
    return send_response_callback;
}