#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int cnt; TYPE_4__* bufs; TYPE_4__* alloced_ptr; TYPE_4__* smallbufs; } ;
struct TYPE_9__ {int /*<<< orphan*/ * write; } ;
struct TYPE_10__ {TYPE_1__ _cb; } ;
struct st_h2o_evloop_socket_t {TYPE_3__ _wreq; int /*<<< orphan*/  _flags; int /*<<< orphan*/  fd; TYPE_2__ super; } ;
typedef  int /*<<< orphan*/  h2o_socket_t ;
typedef  int /*<<< orphan*/ * h2o_socket_cb ;
struct TYPE_12__ {scalar_t__ len; scalar_t__ base; } ;
typedef  TYPE_4__ h2o_iovec_t ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_SOCKET_FLAG_IS_WRITE_NOTIFY ; 
 int /*<<< orphan*/  H2O_STRLIT (char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_4__ h2o_iovec_init (int /*<<< orphan*/ ) ; 
 TYPE_4__* h2o_mem_alloc (int) ; 
 int /*<<< orphan*/  link_to_pending (struct st_h2o_evloop_socket_t*) ; 
 int /*<<< orphan*/  link_to_statechanged (struct st_h2o_evloop_socket_t*) ; 
 scalar_t__ write_core (int /*<<< orphan*/ ,TYPE_4__**,size_t*,size_t*) ; 

void do_write(h2o_socket_t *_sock, h2o_iovec_t *bufs, size_t bufcnt, h2o_socket_cb cb)
{
    struct st_h2o_evloop_socket_t *sock = (struct st_h2o_evloop_socket_t *)_sock;
    size_t first_buf_written, i;

    assert(sock->super._cb.write == NULL);
    assert(sock->_wreq.cnt == 0);
    sock->super._cb.write = cb;

    /* try to write now */
    if (write_core(sock->fd, &bufs, &bufcnt, &first_buf_written) != 0) {
        /* fill in _wreq.bufs with fake data to indicate error */
        sock->_wreq.bufs = sock->_wreq.smallbufs;
        sock->_wreq.cnt = 1;
        *sock->_wreq.bufs = h2o_iovec_init(H2O_STRLIT("deadbeef"));
        sock->_flags |= H2O_SOCKET_FLAG_IS_WRITE_NOTIFY;
        link_to_pending(sock);
        return;
    }
    if (bufcnt == 0) {
        /* write complete, schedule the callback */
        sock->_flags |= H2O_SOCKET_FLAG_IS_WRITE_NOTIFY;
        link_to_pending(sock);
        return;
    }

    /* setup the buffer to send pending data */
    if (bufcnt <= sizeof(sock->_wreq.smallbufs) / sizeof(sock->_wreq.smallbufs[0])) {
        sock->_wreq.bufs = sock->_wreq.smallbufs;
    } else {
        sock->_wreq.bufs = h2o_mem_alloc(sizeof(h2o_iovec_t) * bufcnt);
        sock->_wreq.alloced_ptr = sock->_wreq.bufs;
    }
    sock->_wreq.bufs[0].base = bufs[0].base + first_buf_written;
    sock->_wreq.bufs[0].len = bufs[0].len - first_buf_written;
    for (i = 1; i < bufcnt; ++i)
        sock->_wreq.bufs[i] = bufs[i];
    sock->_wreq.cnt = bufcnt;

    /* schedule the write */
    link_to_statechanged(sock);
}