#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct st_mruby_subreq_t {int dummy; } ;
typedef  int /*<<< orphan*/  mrb_value ;
struct TYPE_10__ {int /*<<< orphan*/ * exc; } ;
typedef  TYPE_3__ mrb_state ;
typedef  int /*<<< orphan*/  h2o_mruby_sender_t ;
struct TYPE_11__ {TYPE_2__* ctx; } ;
typedef  TYPE_4__ h2o_mruby_generator_t ;
struct TYPE_9__ {TYPE_1__* shared; } ;
struct TYPE_8__ {TYPE_3__* mrb; } ;

/* Variables and functions */
 int /*<<< orphan*/  app_input_stream_type ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * create_sender (TYPE_4__*,struct st_mruby_subreq_t*,int /*<<< orphan*/ ) ; 
 struct st_mruby_subreq_t* mrb_data_check_get_ptr (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

h2o_mruby_sender_t *h2o_mruby_middleware_sender_create(h2o_mruby_generator_t *generator, mrb_value body)
{
    mrb_state *mrb = generator->ctx->shared->mrb;
    struct st_mruby_subreq_t *subreq;

    assert(mrb->exc == NULL);

    if ((subreq = mrb_data_check_get_ptr(mrb, body, &app_input_stream_type)) == NULL)
        return NULL;

    return create_sender(generator, subreq, body);
}