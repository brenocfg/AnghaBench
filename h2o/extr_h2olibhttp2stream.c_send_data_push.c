#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  h2o_send_state_t ;
struct TYPE_11__ {size_t base; size_t len; } ;
typedef  TYPE_2__ h2o_iovec_t ;
typedef  int /*<<< orphan*/  h2o_http2_stream_t ;
struct TYPE_10__ {int /*<<< orphan*/  buf; } ;
struct TYPE_12__ {TYPE_1__ _write; } ;
typedef  TYPE_3__ h2o_http2_conn_t ;
struct TYPE_13__ {size_t base; } ;

/* Variables and functions */
 size_t H2O_HTTP2_FRAME_HEADER_SIZE ; 
 int /*<<< orphan*/  H2O_SEND_STATE_IN_PROGRESS ; 
 size_t calc_max_payload_size (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  commit_data_header (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 TYPE_7__ h2o_buffer_reserve (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  h2o_send_state_is_in_progress (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (size_t,size_t,size_t) ; 
 size_t sz_min (size_t,size_t) ; 

__attribute__((used)) static h2o_iovec_t *send_data_push(h2o_http2_conn_t *conn, h2o_http2_stream_t *stream, h2o_iovec_t *bufs, size_t bufcnt,
                                   h2o_send_state_t send_state)
{
    h2o_iovec_t dst;
    size_t max_payload_size;

    if ((max_payload_size = calc_max_payload_size(conn, stream)) == 0)
        goto Exit;

    /* reserve buffer and point dst to the payload */
    dst.base =
        h2o_buffer_reserve(&conn->_write.buf, H2O_HTTP2_FRAME_HEADER_SIZE + max_payload_size).base + H2O_HTTP2_FRAME_HEADER_SIZE;
    dst.len = max_payload_size;

    /* emit data */
    while (bufcnt != 0) {
        if (bufs->len != 0)
            break;
        ++bufs;
        --bufcnt;
    }
    while (bufcnt != 0) {
        size_t fill_size = sz_min(dst.len, bufs->len);
        memcpy(dst.base, bufs->base, fill_size);
        dst.base += fill_size;
        dst.len -= fill_size;
        bufs->base += fill_size;
        bufs->len -= fill_size;
        while (bufs->len == 0) {
            ++bufs;
            --bufcnt;
            if (bufcnt == 0)
                break;
        }
        if (dst.len == 0)
            break;
    }

    /* commit the DATA frame if we have actually emitted payload */
    if (dst.len != max_payload_size || !h2o_send_state_is_in_progress(send_state)) {
        size_t payload_len = max_payload_size - dst.len;
        if (bufcnt != 0) {
            send_state = H2O_SEND_STATE_IN_PROGRESS;
        }
        commit_data_header(conn, stream, &conn->_write.buf, payload_len, send_state);
    }

Exit:
    return bufs;
}