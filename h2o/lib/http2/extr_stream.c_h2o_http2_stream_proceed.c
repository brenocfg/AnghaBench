#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ state; int /*<<< orphan*/  req; int /*<<< orphan*/  blocked_by_server; int /*<<< orphan*/  _req_streaming_in_progress; } ;
typedef  TYPE_1__ h2o_http2_stream_t ;
typedef  int /*<<< orphan*/  h2o_http2_conn_t ;

/* Variables and functions */
 scalar_t__ H2O_HTTP2_STREAM_STATE_END_STREAM ; 
 int /*<<< orphan*/  h2o_http2_stream_close (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  h2o_http2_stream_set_blocked_by_server (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  h2o_proceed_response (int /*<<< orphan*/ *) ; 

void h2o_http2_stream_proceed(h2o_http2_conn_t *conn, h2o_http2_stream_t *stream)
{
    if (stream->state == H2O_HTTP2_STREAM_STATE_END_STREAM) {
        if (!stream->_req_streaming_in_progress) {
            h2o_http2_stream_close(conn, stream);
        }
    } else {
        if (!stream->blocked_by_server)
            h2o_http2_stream_set_blocked_by_server(conn, stream, 1);
        h2o_proceed_response(&stream->req);
    }
}