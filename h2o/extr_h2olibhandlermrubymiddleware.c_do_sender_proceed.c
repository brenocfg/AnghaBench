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
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct st_mruby_subreq_t {scalar_t__ state; int /*<<< orphan*/  super; scalar_t__ chain_proceed; TYPE_4__* buf; } ;
struct st_h2o_mruby_middleware_sender_t {struct st_mruby_subreq_t* subreq; int /*<<< orphan*/  sending; } ;
typedef  int /*<<< orphan*/  h2o_req_t ;
struct TYPE_7__ {TYPE_1__* sender; } ;
typedef  TYPE_2__ h2o_mruby_generator_t ;
typedef  int /*<<< orphan*/  h2o_generator_t ;
struct TYPE_8__ {scalar_t__ size; } ;
struct TYPE_6__ {scalar_t__ final_sent; } ;

/* Variables and functions */
 scalar_t__ FINAL_RECEIVED ; 
 int /*<<< orphan*/  H2O_SEND_STATE_FINAL ; 
 int /*<<< orphan*/  H2O_SEND_STATE_IN_PROGRESS ; 
 int /*<<< orphan*/  h2o_buffer_dispose (TYPE_4__**) ; 
 int /*<<< orphan*/  h2o_doublebuffer_consume (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_mruby_sender_do_send_buffer (TYPE_2__*,int /*<<< orphan*/ *,TYPE_4__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_proceed_response (int /*<<< orphan*/ *) ; 

void do_sender_proceed(h2o_generator_t *_generator, h2o_req_t *req)
{
    h2o_mruby_generator_t *generator = (void *)_generator;
    struct st_h2o_mruby_middleware_sender_t *sender = (void *)generator->sender;
    struct st_mruby_subreq_t *subreq = sender->subreq;

    if (generator->sender->final_sent)
        return; /* TODO: close subreq ASAP */

    if (subreq->buf != NULL) {
        h2o_doublebuffer_consume(&sender->sending);

        if (subreq->buf->size != 0) {
            h2o_mruby_sender_do_send_buffer(generator, &sender->sending, &subreq->buf,
                                            subreq->state == FINAL_RECEIVED ? H2O_SEND_STATE_FINAL : H2O_SEND_STATE_IN_PROGRESS);
            return; /* don't proceed because it's already requested in subreq_ostream_send*/
        } else {
            /* start direct shortcut */
            h2o_buffer_dispose(&subreq->buf);
            subreq->buf = NULL;
        }
    }

    if (sender->subreq->chain_proceed)
        h2o_proceed_response(&sender->subreq->super);
}