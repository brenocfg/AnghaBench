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
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_7__ {scalar_t__ res; } ;
struct st_h2o_http2client_stream_t {TYPE_1__ state; } ;
struct TYPE_8__ {TYPE_5__* headers_unparsed; int /*<<< orphan*/  read_frame; } ;
struct st_h2o_http2client_conn_t {TYPE_2__ input; } ;
typedef  int ssize_t ;
struct TYPE_9__ {scalar_t__ type; int flags; scalar_t__ length; int /*<<< orphan*/  payload; int /*<<< orphan*/  stream_id; } ;
typedef  TYPE_3__ h2o_http2_frame_t ;
struct TYPE_10__ {scalar_t__ size; scalar_t__ bytes; } ;

/* Variables and functions */
 int H2O_HTTP2_ERROR_PROTOCOL ; 
 int H2O_HTTP2_FRAME_FLAG_END_HEADERS ; 
 int H2O_HTTP2_FRAME_FLAG_END_STREAM ; 
 scalar_t__ H2O_HTTP2_FRAME_TYPE_CONTINUATION ; 
 int /*<<< orphan*/  H2O_HTTP2_SETTINGS_CLIENT_MAX_FRAME_SIZE ; 
 scalar_t__ STREAM_STATE_BODY ; 
 scalar_t__ STREAM_STATE_CLOSED ; 
 int /*<<< orphan*/  expect_default ; 
 struct st_h2o_http2client_stream_t* get_stream (struct st_h2o_http2client_conn_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_buffer_dispose (TYPE_5__**) ; 
 int /*<<< orphan*/  h2o_buffer_reserve (TYPE_5__**,scalar_t__) ; 
 int h2o_http2_decode_frame (TYPE_3__*,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ ,char const**) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int on_head (struct st_h2o_http2client_conn_t*,struct st_h2o_http2client_stream_t*,int /*<<< orphan*/  const*,scalar_t__,char const**,int) ; 

__attribute__((used)) static ssize_t expect_continuation_of_headers(struct st_h2o_http2client_conn_t *conn, const uint8_t *src, size_t len,
                                              const char **err_desc)
{
    h2o_http2_frame_t frame;
    ssize_t ret;
    struct st_h2o_http2client_stream_t *stream;
    int hret;

    if ((ret = h2o_http2_decode_frame(&frame, src, len, H2O_HTTP2_SETTINGS_CLIENT_MAX_FRAME_SIZE, err_desc)) < 0)
        return ret;
    if (frame.type != H2O_HTTP2_FRAME_TYPE_CONTINUATION) {
        *err_desc = "expected CONTINUATION frame";
        return H2O_HTTP2_ERROR_PROTOCOL;
    }

    if ((stream = get_stream(conn, frame.stream_id)) == NULL || stream->state.res == STREAM_STATE_CLOSED) {
        *err_desc = "unexpected stream id in CONTINUATION frame";
        return H2O_HTTP2_ERROR_PROTOCOL;
    }

    if (stream->state.res == STREAM_STATE_BODY) {
        /* is a trailer, do nothing */
        return ret;
    }

    h2o_buffer_reserve(&conn->input.headers_unparsed, frame.length);
    memcpy(conn->input.headers_unparsed->bytes + conn->input.headers_unparsed->size, frame.payload, frame.length);
    conn->input.headers_unparsed->size += frame.length;

    if ((frame.flags & H2O_HTTP2_FRAME_FLAG_END_HEADERS) != 0) {
        int is_end_stream = (frame.flags & H2O_HTTP2_FRAME_FLAG_END_STREAM) != 0;
        conn->input.read_frame = expect_default;
        hret = on_head(conn, stream, (const uint8_t *)conn->input.headers_unparsed->bytes, conn->input.headers_unparsed->size,
                       err_desc, is_end_stream);
        if (hret != 0)
            ret = hret;
        h2o_buffer_dispose(&conn->input.headers_unparsed);
        conn->input.headers_unparsed = NULL;
    }

    return ret;
}