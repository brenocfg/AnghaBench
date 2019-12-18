#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_9__ {int /*<<< orphan*/  path; int /*<<< orphan*/  authority; int /*<<< orphan*/  scheme; int /*<<< orphan*/  method; } ;
struct TYPE_10__ {int /*<<< orphan*/  headers; TYPE_1__ input; int /*<<< orphan*/  pool; } ;
struct TYPE_11__ {TYPE_2__ req; } ;
typedef  TYPE_3__ h2o_http2_stream_t ;
struct TYPE_12__ {int /*<<< orphan*/  _input_header_table; } ;
typedef  TYPE_4__ h2o_http2_conn_t ;

/* Variables and functions */
 int /*<<< orphan*/  h2o_hpack_decode_header ; 
 int h2o_hpack_parse_request (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t,char const**) ; 
 int /*<<< orphan*/  h2o_iovec_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_request_body_chunk (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int handle_trailing_headers(h2o_http2_conn_t *conn, h2o_http2_stream_t *stream, const uint8_t *src, size_t len,
                                   const char **err_desc)
{
    size_t dummy_content_length;
    int ret;

    if ((ret = h2o_hpack_parse_request(&stream->req.pool, h2o_hpack_decode_header, &conn->_input_header_table,
                                       &stream->req.input.method, &stream->req.input.scheme, &stream->req.input.authority,
                                       &stream->req.input.path, &stream->req.headers, NULL, &dummy_content_length, NULL, src, len,
                                       err_desc)) != 0)
        return ret;
    handle_request_body_chunk(conn, stream, h2o_iovec_init(NULL, 0), 1);
    return 0;
}