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
struct TYPE_6__ {int /*<<< orphan*/  off; TYPE_1__* ref; } ;
struct st_h2o_sendfile_generator_t {scalar_t__ bytesleft; int /*<<< orphan*/  super; TYPE_2__ file; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  h2o_send_state_t ;
typedef  int /*<<< orphan*/  h2o_req_t ;
struct TYPE_7__ {scalar_t__ len; int /*<<< orphan*/  base; } ;
typedef  TYPE_3__ h2o_iovec_t ;
typedef  int /*<<< orphan*/  h2o_generator_t ;
struct TYPE_5__ {int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  H2O_SEND_STATE_ERROR ; 
 int /*<<< orphan*/  H2O_SEND_STATE_FINAL ; 
 int /*<<< orphan*/  H2O_SEND_STATE_IN_PROGRESS ; 
 int /*<<< orphan*/  do_close (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 int pread (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static h2o_send_state_t do_pull(h2o_generator_t *_self, h2o_req_t *req, h2o_iovec_t *buf)
{
    struct st_h2o_sendfile_generator_t *self = (void *)_self;
    ssize_t rret;

    if (self->bytesleft < buf->len)
        buf->len = self->bytesleft;
    while ((rret = pread(self->file.ref->fd, buf->base, buf->len, self->file.off)) == -1 && errno == EINTR)
        ;
    if (rret <= 0) {
        buf->len = 0;
        self->bytesleft = 0;
        do_close(&self->super, req);
        return H2O_SEND_STATE_ERROR;
    } else {
        buf->len = rret;
        self->file.off += rret;
        self->bytesleft -= rret;
    }

    if (self->bytesleft != 0)
        return H2O_SEND_STATE_IN_PROGRESS;
    do_close(&self->super, req);
    return H2O_SEND_STATE_FINAL;
}