#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* on_body ) (TYPE_3__*,char*) ;} ;
struct TYPE_7__ {TYPE_1__ _cb; } ;
struct st_h2o_http3client_req_t {int (* handle_input ) (struct st_h2o_http3client_req_t*,int /*<<< orphan*/  const**,int /*<<< orphan*/  const*,int,char const**) ;int /*<<< orphan*/  bytes_left_in_data_frame; TYPE_3__ super; } ;
struct TYPE_6__ {int type; int /*<<< orphan*/  length; } ;
typedef  TYPE_2__ h2o_http3_read_frame_t ;

/* Variables and functions */
 int H2O_HTTP3_ERROR_INCOMPLETE ; 
#define  H2O_HTTP3_FRAME_TYPE_DATA 128 
 int /*<<< orphan*/  H2O_HTTP3_STREAM_TYPE_REQUEST ; 
 int h2o_http3_read_frame (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/  const**,int /*<<< orphan*/  const*,char const**) ; 
 int handle_input_data_payload (struct st_h2o_http3client_req_t*,int /*<<< orphan*/  const**,int /*<<< orphan*/  const*,int,char const**) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,char*) ; 

int handle_input_expect_data_frame(struct st_h2o_http3client_req_t *req, const uint8_t **src, const uint8_t *src_end, int err,
                                   const char **err_desc)
{
    h2o_http3_read_frame_t frame;
    int ret;

    if ((ret = h2o_http3_read_frame(&frame, 1, H2O_HTTP3_STREAM_TYPE_REQUEST, src, src_end, err_desc)) != 0) {
        /* incomplete */
        if (ret == H2O_HTTP3_ERROR_INCOMPLETE && err == 0)
            return ret;
        req->super._cb.on_body(&req->super, "malformed frame");
        return ret;
    }

    switch (frame.type) {
    case H2O_HTTP3_FRAME_TYPE_DATA:
        break;
    default:
        /* FIXME handle push_promise, trailers */
        return 0;
    }

    req->bytes_left_in_data_frame = frame.length;

    /* unexpected close of DATA frame is handled by handle_input_data_payload. We rely on the function to detect if the DATA frame
     * is closed right after the frame header */
    req->handle_input = handle_input_data_payload;
    return handle_input_data_payload(req, src, src_end, err, err_desc);
}