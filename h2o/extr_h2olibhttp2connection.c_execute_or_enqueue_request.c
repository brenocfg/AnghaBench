#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ state; int /*<<< orphan*/  blocked_by_server; } ;
typedef  TYPE_1__ h2o_http2_stream_t ;
typedef  int /*<<< orphan*/  h2o_http2_conn_t ;

/* Variables and functions */
 scalar_t__ H2O_HTTP2_STREAM_STATE_RECV_HEADERS ; 
 scalar_t__ H2O_HTTP2_STREAM_STATE_REQ_PENDING ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  execute_or_enqueue_request_core (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  h2o_http2_stream_set_blocked_by_server (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  h2o_http2_stream_set_state (int /*<<< orphan*/ *,TYPE_1__*,scalar_t__) ; 
 scalar_t__ reset_stream_if_disregarded (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void execute_or_enqueue_request(h2o_http2_conn_t *conn, h2o_http2_stream_t *stream)
{
    assert(stream->state == H2O_HTTP2_STREAM_STATE_RECV_HEADERS || stream->state == H2O_HTTP2_STREAM_STATE_REQ_PENDING);

    if (reset_stream_if_disregarded(conn, stream))
        return;

    h2o_http2_stream_set_state(conn, stream, H2O_HTTP2_STREAM_STATE_REQ_PENDING);
    if (!stream->blocked_by_server)
        h2o_http2_stream_set_blocked_by_server(conn, stream, 1);
    execute_or_enqueue_request_core(conn, stream);
}