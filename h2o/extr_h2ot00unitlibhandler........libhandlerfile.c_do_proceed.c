#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int off; TYPE_1__* ref; } ;
struct st_h2o_sendfile_generator_t {size_t bytesleft; int /*<<< orphan*/  super; int /*<<< orphan*/  buf; TYPE_2__ file; } ;
typedef  int ssize_t ;
typedef  scalar_t__ h2o_send_state_t ;
typedef  int /*<<< orphan*/  h2o_req_t ;
struct TYPE_7__ {int len; int /*<<< orphan*/  base; } ;
typedef  TYPE_3__ h2o_iovec_t ;
typedef  int /*<<< orphan*/  h2o_generator_t ;
struct TYPE_5__ {int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 scalar_t__ H2O_SEND_STATE_ERROR ; 
 scalar_t__ H2O_SEND_STATE_FINAL ; 
 scalar_t__ H2O_SEND_STATE_IN_PROGRESS ; 
 size_t MAX_BUF_SIZE ; 
 int /*<<< orphan*/  do_close (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  h2o_send (int /*<<< orphan*/ *,TYPE_3__*,int,scalar_t__) ; 
 int pread (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int) ; 

__attribute__((used)) static void do_proceed(h2o_generator_t *_self, h2o_req_t *req)
{
    struct st_h2o_sendfile_generator_t *self = (void *)_self;
    size_t rlen;
    ssize_t rret;
    h2o_iovec_t vec;
    h2o_send_state_t send_state;

    /* read the file */
    rlen = self->bytesleft;
    if (rlen > MAX_BUF_SIZE)
        rlen = MAX_BUF_SIZE;
    while ((rret = pread(self->file.ref->fd, self->buf, rlen, self->file.off)) == -1 && errno == EINTR)
        ;
    if (rret == -1) {
        h2o_send(req, NULL, 0, H2O_SEND_STATE_ERROR);
        do_close(&self->super, req);
        return;
    }
    self->file.off += rret;
    self->bytesleft -= rret;
    if (self->bytesleft == 0) {
        send_state = H2O_SEND_STATE_FINAL;
    } else {
        send_state = H2O_SEND_STATE_IN_PROGRESS;
    }

    /* send (and close if done) */
    vec.base = self->buf;
    vec.len = rret;
    h2o_send(req, &vec, 1, send_state);
    if (send_state == H2O_SEND_STATE_FINAL)
        do_close(&self->super, req);
}