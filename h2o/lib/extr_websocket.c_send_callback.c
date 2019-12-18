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
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wslay_event_context_ptr ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int ssize_t ;
struct TYPE_4__ {int cnt; TYPE_3__* bufs; } ;
struct TYPE_5__ {TYPE_1__ _write_buf; int /*<<< orphan*/  ws_ctx; int /*<<< orphan*/  sock; } ;
typedef  TYPE_2__ h2o_websocket_conn_t ;
struct TYPE_6__ {size_t len; int /*<<< orphan*/  base; } ;
typedef  TYPE_3__ h2o_iovec_t ;

/* Variables and functions */
 int /*<<< orphan*/  WSLAY_ERR_WOULDBLOCK ; 
 int /*<<< orphan*/  h2o_mem_alloc (size_t) ; 
 scalar_t__ h2o_socket_is_writing (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wslay_event_set_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t send_callback(wslay_event_context_ptr ctx, const uint8_t *data, size_t len, int flags, void *_conn)
{
    h2o_websocket_conn_t *conn = _conn;
    h2o_iovec_t *buf;

    /* return WOULDBLOCK if pending or no buffer available */
    if (h2o_socket_is_writing(conn->sock) ||
        conn->_write_buf.cnt == sizeof(conn->_write_buf.bufs) / sizeof(conn->_write_buf.bufs[0])) {
        wslay_event_set_error(conn->ws_ctx, WSLAY_ERR_WOULDBLOCK);
        return -1;
    }

    buf = &conn->_write_buf.bufs[conn->_write_buf.cnt];

    /* copy data */
    buf->base = h2o_mem_alloc(len);
    buf->len = len;
    memcpy(buf->base, data, len);
    ++conn->_write_buf.cnt;
    return len;
}