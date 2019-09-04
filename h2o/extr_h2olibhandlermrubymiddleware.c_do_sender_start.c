#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct st_mruby_subreq_t {scalar_t__ state; TYPE_3__* buf; } ;
struct st_h2o_mruby_middleware_sender_t {int /*<<< orphan*/  sending; struct st_mruby_subreq_t* subreq; } ;
struct TYPE_5__ {int /*<<< orphan*/  req; scalar_t__ sender; } ;
typedef  TYPE_1__ h2o_mruby_generator_t ;
struct TYPE_6__ {scalar_t__ size; } ;

/* Variables and functions */
 scalar_t__ FINAL_RECEIVED ; 
 int /*<<< orphan*/  H2O_SEND_STATE_FINAL ; 
 int /*<<< orphan*/  H2O_SEND_STATE_IN_PROGRESS ; 
 int /*<<< orphan*/  h2o_doublebuffer_prepare_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_mruby_sender_do_send_buffer (TYPE_1__*,int /*<<< orphan*/ *,TYPE_3__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_send (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void do_sender_start(h2o_mruby_generator_t *generator)
{
    struct st_h2o_mruby_middleware_sender_t *sender = (void *)generator->sender;
    struct st_mruby_subreq_t *subreq = sender->subreq;

    if (subreq->buf->size == 0 && subreq->state != FINAL_RECEIVED) {
        h2o_doublebuffer_prepare_empty(&sender->sending);
        h2o_send(generator->req, NULL, 0, H2O_SEND_STATE_IN_PROGRESS);
    } else {
        h2o_mruby_sender_do_send_buffer(generator, &sender->sending, &subreq->buf,
                                        subreq->state == FINAL_RECEIVED ? H2O_SEND_STATE_FINAL : H2O_SEND_STATE_IN_PROGRESS);
    }
}