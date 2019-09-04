#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct st_h2o_http2client_stream_t {scalar_t__ state; int /*<<< orphan*/ * conn; } ;

/* Variables and functions */
 scalar_t__ H2O_HTTP2CLIENT_STREAM_STATE_RECV_HEADERS ; 
 int /*<<< orphan*/  call_callback_with_error (struct st_h2o_http2client_stream_t*,char const*) ; 
 int /*<<< orphan*/  close_stream (struct st_h2o_http2client_stream_t*) ; 
 int /*<<< orphan*/  on_connect_error (struct st_h2o_http2client_stream_t*,char*) ; 

__attribute__((used)) static void do_stream_timeout(struct st_h2o_http2client_stream_t *stream)
{
    if (stream->conn == NULL) {
        on_connect_error(stream, "connection timeout");
        return;
    }
    const char *errstr = stream->state == H2O_HTTP2CLIENT_STREAM_STATE_RECV_HEADERS ? "first byte timeout" : "I/O timeout";
    call_callback_with_error(stream, errstr);
    close_stream(stream);
}