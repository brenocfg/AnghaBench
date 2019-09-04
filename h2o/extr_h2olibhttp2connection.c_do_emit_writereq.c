#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_11__ ;

/* Type definitions */
struct TYPE_19__ {scalar_t__ member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_5__ h2o_iovec_t ;
struct TYPE_17__ {scalar_t__ open; } ;
struct TYPE_16__ {scalar_t__ open; } ;
struct TYPE_18__ {TYPE_3__ push; TYPE_2__ pull; } ;
struct TYPE_15__ {TYPE_11__* buf; TYPE_11__* buf_in_flight; } ;
struct TYPE_20__ {int state; TYPE_4__ num_streams; TYPE_1__ _write; int /*<<< orphan*/  sock; int /*<<< orphan*/  scheduler; } ;
typedef  TYPE_6__ h2o_http2_conn_t ;
struct TYPE_14__ {scalar_t__ size; int /*<<< orphan*/  bytes; } ;

/* Variables and functions */
#define  H2O_HTTP2_CONN_STATE_HALF_CLOSED 130 
#define  H2O_HTTP2_CONN_STATE_IS_CLOSING 129 
#define  H2O_HTTP2_CONN_STATE_OPEN 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close_connection_now (TYPE_6__*) ; 
 int /*<<< orphan*/  emit_writereq_of_openref ; 
 int /*<<< orphan*/  h2o_buffer_init (TYPE_11__**,int /*<<< orphan*/ *) ; 
 scalar_t__ h2o_http2_conn_get_buffer_window (TYPE_6__*) ; 
 int /*<<< orphan*/  h2o_http2_scheduler_run (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  h2o_http2_wbuf_buffer_prototype ; 
 int /*<<< orphan*/  h2o_socket_write (int /*<<< orphan*/ ,TYPE_5__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  on_write_complete ; 
 int /*<<< orphan*/  update_idle_timeout (TYPE_6__*) ; 

void do_emit_writereq(h2o_http2_conn_t *conn)
{
    assert(conn->_write.buf_in_flight == NULL);

    /* push DATA frames */
    if (conn->state < H2O_HTTP2_CONN_STATE_IS_CLOSING && h2o_http2_conn_get_buffer_window(conn) > 0)
        h2o_http2_scheduler_run(&conn->scheduler, emit_writereq_of_openref, conn);

    if (conn->_write.buf->size != 0) {
        /* write and wait for completion */
        h2o_iovec_t buf = {conn->_write.buf->bytes, conn->_write.buf->size};
        h2o_socket_write(conn->sock, &buf, 1, on_write_complete);
        conn->_write.buf_in_flight = conn->_write.buf;
        h2o_buffer_init(&conn->_write.buf, &h2o_http2_wbuf_buffer_prototype);
        update_idle_timeout(conn);
    }

    /* close the connection if necessary */
    switch (conn->state) {
    case H2O_HTTP2_CONN_STATE_OPEN:
        break;
    case H2O_HTTP2_CONN_STATE_HALF_CLOSED:
        if (conn->num_streams.pull.open + conn->num_streams.push.open != 0)
            break;
        conn->state = H2O_HTTP2_CONN_STATE_IS_CLOSING;
    /* fall-thru */
    case H2O_HTTP2_CONN_STATE_IS_CLOSING:
        close_connection_now(conn);
        break;
    }
}