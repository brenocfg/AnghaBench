#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_16__ {int /*<<< orphan*/ * (* on_head ) (TYPE_7__*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/ * on_body; } ;
struct TYPE_19__ {scalar_t__ (* informational_cb ) (TYPE_7__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;TYPE_4__ _cb; int /*<<< orphan*/  pool; } ;
struct st_h2o_http3client_req_t {int /*<<< orphan*/ * handle_input; TYPE_7__ super; TYPE_3__* conn; TYPE_2__* quic; } ;
struct TYPE_17__ {int type; int /*<<< orphan*/  length; int /*<<< orphan*/  payload; } ;
typedef  TYPE_5__ h2o_http3_read_frame_t ;
struct TYPE_18__ {int /*<<< orphan*/  size; int /*<<< orphan*/  entries; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_6__ h2o_headers_t ;
struct TYPE_13__ {int /*<<< orphan*/  dec; } ;
struct TYPE_12__ {TYPE_1__ qpack; } ;
struct TYPE_15__ {TYPE_10__ super; } ;
struct TYPE_14__ {int /*<<< orphan*/  stream_id; } ;

/* Variables and functions */
 int H2O_HPACK_ENCODE_INT_MAX_LENGTH ; 
 int H2O_HTTP2_ERROR_INCOMPLETE ; 
 int H2O_HTTP3_ERROR_EOS ; 
 int H2O_HTTP3_ERROR_EXCESSIVE_LOAD ; 
 int H2O_HTTP3_ERROR_FRAME_UNEXPECTED ; 
 int H2O_HTTP3_ERROR_GENERAL_PROTOCOL ; 
 int H2O_HTTP3_ERROR_INCOMPLETE ; 
 int H2O_HTTP3_ERROR_INTERNAL ; 
 int H2O_HTTP3_ERROR_NONE ; 
#define  H2O_HTTP3_FRAME_TYPE_DATA 128 
 int H2O_HTTP3_FRAME_TYPE_HEADERS ; 
 int /*<<< orphan*/  H2O_HTTP3_STREAM_TYPE_REQUEST ; 
 int h2o_http3_read_frame (TYPE_5__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/  const**,int /*<<< orphan*/  const*,char const**) ; 
 int /*<<< orphan*/  h2o_http3_send_qpack_header_ack (TYPE_10__*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/ * h2o_httpclient_error_is_eos ; 
 int /*<<< orphan*/  h2o_iovec_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int h2o_qpack_parse_response (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,TYPE_6__*,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const**) ; 
 int /*<<< orphan*/ * handle_input_expect_data_frame ; 
 int /*<<< orphan*/  on_error_before_head (struct st_h2o_http3client_req_t*,char const*) ; 
 scalar_t__ stub1 (TYPE_7__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stub2 (TYPE_7__*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int handle_input_expect_headers(struct st_h2o_http3client_req_t *req, const uint8_t **src, const uint8_t *src_end, int err,
                                       const char **err_desc)
{
    h2o_http3_read_frame_t frame;
    int status;
    h2o_headers_t headers = {NULL};
    uint8_t header_ack[H2O_HPACK_ENCODE_INT_MAX_LENGTH];
    size_t header_ack_len;
    int ret, frame_is_eos;

    /* read HEADERS frame */
    if ((ret = h2o_http3_read_frame(&frame, 1, H2O_HTTP3_STREAM_TYPE_REQUEST, src, src_end, err_desc)) != 0) {
        if (ret == H2O_HTTP3_ERROR_INCOMPLETE) {
            if (err != 0) {
                on_error_before_head(req, err == H2O_HTTP3_ERROR_NONE ? "unexpected close" : "reset by peer");
                return 0;
            }
            return ret;
        }
        on_error_before_head(req, "response header too large");
        return H2O_HTTP3_ERROR_EXCESSIVE_LOAD; /* FIXME correct code? */
    }
    frame_is_eos = *src == src_end && err != 0;
    if (frame.type != H2O_HTTP3_FRAME_TYPE_HEADERS) {
        switch (frame.type) {
        case H2O_HTTP3_FRAME_TYPE_DATA:
            *err_desc = "received DATA frame before HEADERS";
            return H2O_HTTP3_ERROR_FRAME_UNEXPECTED;
        default:
            return 0;
        }
    }
    if ((ret = h2o_qpack_parse_response(req->super.pool, req->conn->super.qpack.dec, req->quic->stream_id, &status, &headers,
                                        header_ack, &header_ack_len, frame.payload, frame.length, err_desc)) != 0) {
        if (ret == H2O_HTTP2_ERROR_INCOMPLETE) {
            /* the request is blocked by the QPACK stream */
            req->handle_input = NULL; /* FIXME */
            return 0;
        }
        on_error_before_head(req, *err_desc != NULL ? *err_desc : "qpack error");
        return H2O_HTTP3_ERROR_GENERAL_PROTOCOL; /* FIXME */
    }
    if (header_ack_len != 0)
        h2o_http3_send_qpack_header_ack(&req->conn->super, header_ack, header_ack_len);

    /* handle 1xx */
    if (100 <= status && status <= 199) {
        if (status == 101) {
            on_error_before_head(req, "unexpected 101");
            return H2O_HTTP3_ERROR_GENERAL_PROTOCOL;
        }
        if (frame_is_eos) {
            on_error_before_head(req, err == H2O_HTTP3_ERROR_EOS ? "unexpected close" : "reset by peer");
            return 0;
        }
        if (req->super.informational_cb != NULL &&
            req->super.informational_cb(&req->super, 0, status, h2o_iovec_init(NULL, 0), headers.entries, headers.size) != 0) {
            return H2O_HTTP3_ERROR_INTERNAL;
        }
        return 0;
    }

    /* handle final response */
    if ((req->super._cb.on_body = req->super._cb.on_head(&req->super, frame_is_eos ? h2o_httpclient_error_is_eos : NULL, 0x300,
                                                         status, h2o_iovec_init(NULL, 0), headers.entries, headers.size, 0)) ==
        NULL)
        return frame_is_eos ? 0 : H2O_HTTP3_ERROR_INTERNAL;

    /* handle body */
    req->handle_input = handle_input_expect_data_frame;
    return 0;
}