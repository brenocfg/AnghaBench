#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  window; TYPE_4__* buf; } ;
struct TYPE_8__ {TYPE_2__* ctx; int /*<<< orphan*/  sock; } ;
struct st_h2o_http2client_conn_t {TYPE_5__ output; TYPE_3__ super; } ;
typedef  size_t ssize_t ;
struct TYPE_9__ {size_t capacity; size_t size; } ;
struct TYPE_6__ {int /*<<< orphan*/  latency_optimization; } ;
struct TYPE_7__ {TYPE_1__ http2; } ;

/* Variables and functions */
 size_t H2O_HTTP2_FRAME_HEADER_SIZE ; 
 size_t h2o_http2_window_get_avail (int /*<<< orphan*/ *) ; 
 size_t h2o_socket_prepare_for_latency_optimized_write (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t conn_get_buffer_window(struct st_h2o_http2client_conn_t *conn)
{
    ssize_t ret, winsz;
    size_t capacity, cwnd_left;

    capacity = conn->output.buf->capacity;
    if ((cwnd_left = h2o_socket_prepare_for_latency_optimized_write(conn->super.sock,
                                                                    &conn->super.ctx->http2.latency_optimization)) < capacity) {
        capacity = cwnd_left;
        if (capacity < conn->output.buf->size)
            return 0;
    }

    ret = capacity - conn->output.buf->size;
    if (ret < H2O_HTTP2_FRAME_HEADER_SIZE)
        return 0;
    ret -= H2O_HTTP2_FRAME_HEADER_SIZE;
    winsz = h2o_http2_window_get_avail(&conn->output.window);
    if (winsz < ret)
        ret = winsz;
    return ret;
}