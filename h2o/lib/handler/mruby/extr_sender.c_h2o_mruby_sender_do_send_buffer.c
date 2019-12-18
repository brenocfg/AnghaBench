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
typedef  int /*<<< orphan*/  h2o_sendvec_t ;
typedef  int /*<<< orphan*/  h2o_send_state_t ;
struct TYPE_16__ {TYPE_1__* req; } ;
typedef  TYPE_3__ h2o_mruby_generator_t ;
struct TYPE_17__ {scalar_t__ len; int /*<<< orphan*/  base; } ;
typedef  TYPE_4__ h2o_iovec_t ;
struct TYPE_18__ {TYPE_2__* buf; int /*<<< orphan*/  inflight; } ;
typedef  TYPE_5__ h2o_doublebuffer_t ;
struct TYPE_19__ {scalar_t__ size; } ;
typedef  TYPE_6__ h2o_buffer_t ;
struct TYPE_15__ {scalar_t__ size; } ;
struct TYPE_14__ {int /*<<< orphan*/  preferred_chunk_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_SEND_STATE_FINAL ; 
 int /*<<< orphan*/  H2O_SEND_STATE_IN_PROGRESS ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_4__ h2o_doublebuffer_prepare (TYPE_5__*,TYPE_6__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_mruby_sender_do_send (TYPE_3__*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_sendvec_init_raw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

void h2o_mruby_sender_do_send_buffer(h2o_mruby_generator_t *generator, h2o_doublebuffer_t *db, h2o_buffer_t **input, int is_final)
{
    assert(!db->inflight);

    h2o_iovec_t buf = h2o_doublebuffer_prepare(db, input, generator->req->preferred_chunk_size);
    size_t bufcnt = 1;
    h2o_send_state_t send_state;

    if (is_final && buf.len == db->buf->size && (*input)->size == 0) {
        if (buf.len == 0)
            --bufcnt;
        send_state = H2O_SEND_STATE_FINAL;
    } else {
        if (buf.len == 0)
            return;
        send_state = H2O_SEND_STATE_IN_PROGRESS;
    }

    h2o_sendvec_t vec;
    h2o_sendvec_init_raw(&vec, buf.base, buf.len);
    h2o_mruby_sender_do_send(generator, &vec, bufcnt, send_state);
}