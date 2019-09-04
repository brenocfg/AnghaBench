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
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_1__* buf; } ;
struct TYPE_10__ {TYPE_8__* receiving; TYPE_7__ sending; } ;
struct st_fcgi_generator_t {scalar_t__ leftsize; TYPE_4__* req; TYPE_2__ resp; int /*<<< orphan*/ * sock; } ;
typedef  int /*<<< orphan*/  h2o_send_state_t ;
struct TYPE_11__ {scalar_t__ len; } ;
typedef  TYPE_3__ h2o_iovec_t ;
struct TYPE_14__ {scalar_t__ size; } ;
struct TYPE_12__ {int /*<<< orphan*/  preferred_chunk_size; } ;
struct TYPE_9__ {scalar_t__ size; } ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_SEND_STATE_ERROR ; 
 int /*<<< orphan*/  H2O_SEND_STATE_FINAL ; 
 int /*<<< orphan*/  H2O_SEND_STATE_IN_PROGRESS ; 
 scalar_t__ SIZE_MAX ; 
 TYPE_3__ h2o_doublebuffer_prepare (TYPE_7__*,TYPE_8__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_send (TYPE_4__*,TYPE_3__*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_send(struct st_fcgi_generator_t *generator)
{
    h2o_iovec_t vecs[1];
    size_t veccnt;
    h2o_send_state_t send_state;

    vecs[0] = h2o_doublebuffer_prepare(&generator->resp.sending, &generator->resp.receiving, generator->req->preferred_chunk_size);
    veccnt = vecs[0].len != 0 ? 1 : 0;
    if (generator->sock == NULL && vecs[0].len == generator->resp.sending.buf->size && generator->resp.receiving->size == 0) {
        if (generator->leftsize == 0 || generator->leftsize == SIZE_MAX) {
            send_state = H2O_SEND_STATE_FINAL;
        } else {
            send_state = H2O_SEND_STATE_ERROR;
        }
    } else {
        if (veccnt == 0)
            return;
        send_state = H2O_SEND_STATE_IN_PROGRESS;
    }
    h2o_send(generator->req, vecs, veccnt, send_state);
}