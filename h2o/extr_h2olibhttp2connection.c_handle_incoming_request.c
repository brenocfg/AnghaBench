#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_21__ {int /*<<< orphan*/ * body; } ;
struct TYPE_18__ {int /*<<< orphan*/  path; int /*<<< orphan*/  authority; int /*<<< orphan*/  scheme; int /*<<< orphan*/  method; } ;
struct TYPE_17__ {TYPE_4__ _req_body; int /*<<< orphan*/  content_length; int /*<<< orphan*/  headers; TYPE_1__ input; int /*<<< orphan*/  pool; } ;
struct TYPE_22__ {scalar_t__ state; int /*<<< orphan*/  stream_id; TYPE_10__ req; int /*<<< orphan*/  cache_digests; } ;
typedef  TYPE_5__ h2o_http2_stream_t ;
struct TYPE_19__ {scalar_t__ open; } ;
struct TYPE_20__ {TYPE_2__ pull; } ;
struct TYPE_23__ {TYPE_3__ num_streams; int /*<<< orphan*/  _input_header_table; } ;
typedef  TYPE_6__ h2o_http2_conn_t ;

/* Variables and functions */
 int H2O_HPACK_PARSE_HEADERS_METHOD_EXISTS ; 
 int H2O_HPACK_PARSE_HEADERS_PATH_EXISTS ; 
 int H2O_HPACK_PARSE_HEADERS_SCHEME_EXISTS ; 
 int H2O_HTTP2_ERROR_INVALID_HEADER_CHAR ; 
 int H2O_HTTP2_ERROR_PROTOCOL ; 
 int H2O_HTTP2_ERROR_REFUSED_STREAM ; 
 scalar_t__ H2O_HTTP2_SETTINGS_HOST_MAX_CONCURRENT_STREAMS ; 
 int /*<<< orphan*/  H2O_HTTP2_STREAM_STATE_RECV_BODY ; 
 scalar_t__ H2O_HTTP2_STREAM_STATE_RECV_HEADERS ; 
 int /*<<< orphan*/  H2O_HTTP2_STREAM_STATE_REQ_PENDING ; 
 int /*<<< orphan*/  H2O_HTTP2_STREAM_STATE_SEND_HEADERS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  execute_or_enqueue_request (TYPE_6__*,TYPE_5__*) ; 
 int /*<<< orphan*/  h2o_hpack_decode_header ; 
 int h2o_hpack_parse_request (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t,char const**) ; 
 int /*<<< orphan*/  h2o_http2_stream_reset (TYPE_6__*,TYPE_5__*) ; 
 int /*<<< orphan*/  h2o_http2_stream_set_state (TYPE_6__*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_send_error_400 (TYPE_10__*,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stream_send_error (TYPE_6__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int handle_incoming_request(h2o_http2_conn_t *conn, h2o_http2_stream_t *stream, const uint8_t *src, size_t len,
                                   const char **err_desc)
{
    int ret, header_exists_map;

    assert(stream->state == H2O_HTTP2_STREAM_STATE_RECV_HEADERS);

    header_exists_map = 0;
    if ((ret = h2o_hpack_parse_request(&stream->req.pool, h2o_hpack_decode_header, &conn->_input_header_table,
                                       &stream->req.input.method, &stream->req.input.scheme, &stream->req.input.authority,
                                       &stream->req.input.path, &stream->req.headers, &header_exists_map,
                                       &stream->req.content_length, &stream->cache_digests, src, len, err_desc)) != 0) {
        /* all errors except invalid-header-char are connection errors */
        if (ret != H2O_HTTP2_ERROR_INVALID_HEADER_CHAR)
            return ret;
    }

/* handle stream-level errors */
#define EXPECTED_MAP                                                                                                               \
    (H2O_HPACK_PARSE_HEADERS_METHOD_EXISTS | H2O_HPACK_PARSE_HEADERS_PATH_EXISTS | H2O_HPACK_PARSE_HEADERS_SCHEME_EXISTS)
    if ((header_exists_map & EXPECTED_MAP) != EXPECTED_MAP) {
        ret = H2O_HTTP2_ERROR_PROTOCOL;
        goto SendRSTStream;
    }
#undef EXPECTED_MAP
    if (conn->num_streams.pull.open > H2O_HTTP2_SETTINGS_HOST_MAX_CONCURRENT_STREAMS) {
        ret = H2O_HTTP2_ERROR_REFUSED_STREAM;
        goto SendRSTStream;
    }

    /* handle request to send response */
    if (ret != 0) {
        assert(ret == H2O_HTTP2_ERROR_INVALID_HEADER_CHAR);
        /* fast forward the stream's state so that we can start sending the response */
        h2o_http2_stream_set_state(conn, stream, H2O_HTTP2_STREAM_STATE_REQ_PENDING);
        h2o_http2_stream_set_state(conn, stream, H2O_HTTP2_STREAM_STATE_SEND_HEADERS);
        h2o_send_error_400(&stream->req, "Invalid Headers", *err_desc, 0);
        return 0;
    }

    if (stream->req._req_body.body == NULL) {
        execute_or_enqueue_request(conn, stream);
    } else {
        h2o_http2_stream_set_state(conn, stream, H2O_HTTP2_STREAM_STATE_RECV_BODY);
    }
    return 0;

SendRSTStream:
    stream_send_error(conn, stream->stream_id, ret);
    h2o_http2_stream_reset(conn, stream);
    return 0;
}