#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ send_server_timing; scalar_t__ http1_is_persistent; int /*<<< orphan*/  bytes_sent; } ;
struct TYPE_10__ {char* buf; int /*<<< orphan*/  cb; } ;
struct TYPE_11__ {int /*<<< orphan*/ * chunked_buf; TYPE_1__ pull; } ;
struct st_h2o_http1_conn_t {int /*<<< orphan*/  sock; TYPE_5__ req; TYPE_2__ _ostr_final; } ;
typedef  scalar_t__ h2o_send_state_t ;
struct TYPE_12__ {scalar_t__ len; } ;
typedef  TYPE_3__ h2o_iovec_t ;

/* Variables and functions */
 scalar_t__ H2O_SEND_STATE_ERROR ; 
 scalar_t__ H2O_SEND_STATE_IN_PROGRESS ; 
 size_t MAX_PULL_BUF_SZ ; 
 int /*<<< orphan*/  encode_chunked (TYPE_3__*,TYPE_3__*,scalar_t__,scalar_t__,int,int /*<<< orphan*/ *) ; 
 TYPE_3__ h2o_iovec_init (char*,size_t) ; 
 scalar_t__ h2o_pull (TYPE_5__*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ h2o_send_state_is_in_progress (scalar_t__) ; 
 int /*<<< orphan*/  h2o_socket_write (int /*<<< orphan*/ ,TYPE_3__*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  on_send_complete ; 
 int /*<<< orphan*/  on_send_next_pull ; 

__attribute__((used)) static void proceed_pull(struct st_h2o_http1_conn_t *conn, size_t nfilled)
{
    h2o_iovec_t bufs[4];
    size_t bufcnt = 0;
    h2o_send_state_t send_state;
    h2o_iovec_t prefix = h2o_iovec_init(NULL, 0), suffix = h2o_iovec_init(NULL, 0);

    if (nfilled != 0)
        bufs[bufcnt++] = h2o_iovec_init(conn->_ostr_final.pull.buf, nfilled);

    if (nfilled < MAX_PULL_BUF_SZ) {
        h2o_iovec_t cbuf = h2o_iovec_init((char *)conn->_ostr_final.pull.buf + nfilled, MAX_PULL_BUF_SZ - nfilled);
        send_state = h2o_pull(&conn->req, conn->_ostr_final.pull.cb, &cbuf);
        conn->req.bytes_sent += cbuf.len;
        if (conn->_ostr_final.chunked_buf != NULL) {
            encode_chunked(&prefix, &suffix, send_state, cbuf.len, conn->req.send_server_timing != 0,
                           conn->_ostr_final.chunked_buf);
            if (prefix.len != 0)
                bufs[bufcnt++] = prefix;
            bufs[bufcnt++] = cbuf;
            if (suffix.len != 0)
                bufs[bufcnt++] = suffix;
        } else if (nfilled != 0) {
            bufs[bufcnt - 1].len += cbuf.len;
        } else {
            bufs[bufcnt++] = cbuf;
        }
        if (send_state == H2O_SEND_STATE_ERROR) {
            conn->req.http1_is_persistent = 0;
            conn->req.send_server_timing = 0; /* suppress sending trailers */
        }
    } else {
        send_state = H2O_SEND_STATE_IN_PROGRESS;
    }

    /* write */
    h2o_socket_write(conn->sock, bufs, bufcnt, h2o_send_state_is_in_progress(send_state) ? on_send_next_pull : on_send_complete);
}