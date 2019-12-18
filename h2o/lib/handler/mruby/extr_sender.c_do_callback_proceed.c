#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  body_obj; int /*<<< orphan*/  final_sent; } ;
struct st_h2o_mruby_callback_sender_t {int /*<<< orphan*/  receiving; int /*<<< orphan*/  sending; TYPE_1__ super; scalar_t__ has_error; } ;
typedef  int /*<<< orphan*/  h2o_req_t ;
struct TYPE_6__ {scalar_t__ sender; } ;
typedef  TYPE_2__ h2o_mruby_generator_t ;
typedef  int /*<<< orphan*/  h2o_generator_t ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_SEND_STATE_ERROR ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  h2o_doublebuffer_consume (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_mruby_sender_do_send (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_mruby_sender_do_send_buffer (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int mrb_nil_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_callback_proceed(h2o_generator_t *_generator, h2o_req_t *req)
{
    h2o_mruby_generator_t *generator = (void *)_generator;
    struct st_h2o_mruby_callback_sender_t *sender = (void *)generator->sender;

    assert(!sender->super.final_sent);

    h2o_doublebuffer_consume(&sender->sending);

    if (sender->has_error) {
        h2o_mruby_sender_do_send(generator, NULL, 0, H2O_SEND_STATE_ERROR);
    } else {
        int is_final = mrb_nil_p(sender->super.body_obj);
        h2o_mruby_sender_do_send_buffer(generator, &sender->sending, &sender->receiving, is_final);
    }
}