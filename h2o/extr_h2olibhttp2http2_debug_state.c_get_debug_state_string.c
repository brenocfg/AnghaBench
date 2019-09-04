#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int state; int /*<<< orphan*/  stream_id; } ;
typedef  TYPE_1__ h2o_http2_stream_t ;

/* Variables and functions */
#define  H2O_HTTP2_STREAM_STATE_END_STREAM 135 
#define  H2O_HTTP2_STREAM_STATE_IDLE 134 
#define  H2O_HTTP2_STREAM_STATE_RECV_BODY 133 
#define  H2O_HTTP2_STREAM_STATE_RECV_HEADERS 132 
#define  H2O_HTTP2_STREAM_STATE_REQ_PENDING 131 
#define  H2O_HTTP2_STREAM_STATE_SEND_BODY 130 
#define  H2O_HTTP2_STREAM_STATE_SEND_BODY_IS_FINAL 129 
#define  H2O_HTTP2_STREAM_STATE_SEND_HEADERS 128 
 char const* debug_state_string_half_closed_remote ; 
 char const* debug_state_string_open ; 
 char const* debug_state_string_reserved_local ; 
 scalar_t__ h2o_http2_stream_is_push (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *get_debug_state_string(h2o_http2_stream_t *stream)
{
    if (h2o_http2_stream_is_push(stream->stream_id)) {
        switch (stream->state) {
        case H2O_HTTP2_STREAM_STATE_RECV_HEADERS:
        case H2O_HTTP2_STREAM_STATE_RECV_BODY:
        case H2O_HTTP2_STREAM_STATE_REQ_PENDING:
            return debug_state_string_reserved_local;
        case H2O_HTTP2_STREAM_STATE_SEND_HEADERS:
        case H2O_HTTP2_STREAM_STATE_SEND_BODY:
        case H2O_HTTP2_STREAM_STATE_SEND_BODY_IS_FINAL:
            return debug_state_string_half_closed_remote;
        case H2O_HTTP2_STREAM_STATE_IDLE:
        case H2O_HTTP2_STREAM_STATE_END_STREAM:
            return NULL;
        }
    } else {
        switch (stream->state) {
        case H2O_HTTP2_STREAM_STATE_RECV_HEADERS:
        case H2O_HTTP2_STREAM_STATE_RECV_BODY:
            return debug_state_string_open;
        case H2O_HTTP2_STREAM_STATE_REQ_PENDING:
        case H2O_HTTP2_STREAM_STATE_SEND_HEADERS:
        case H2O_HTTP2_STREAM_STATE_SEND_BODY:
        case H2O_HTTP2_STREAM_STATE_SEND_BODY_IS_FINAL:
            return debug_state_string_half_closed_remote;
        case H2O_HTTP2_STREAM_STATE_IDLE:
        case H2O_HTTP2_STREAM_STATE_END_STREAM:
            return NULL;
        }
    }
    return NULL;
}