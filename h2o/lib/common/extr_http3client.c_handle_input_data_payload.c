#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {scalar_t__ (* on_body ) (TYPE_3__*,char const*) ;} ;
struct TYPE_6__ {TYPE_2__ _cb; } ;
struct TYPE_4__ {int /*<<< orphan*/  body; } ;
struct st_h2o_http3client_req_t {size_t bytes_left_in_data_frame; TYPE_3__ super; int /*<<< orphan*/  handle_input; TYPE_1__ recvbuf; } ;

/* Variables and functions */
 int H2O_HTTP3_ERROR_EOS ; 
 int H2O_HTTP3_ERROR_INTERNAL ; 
 int /*<<< orphan*/  h2o_buffer_append (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 char* h2o_httpclient_error_is_eos ; 
 int /*<<< orphan*/  handle_input_expect_data_frame ; 
 scalar_t__ stub1 (TYPE_3__*,char const*) ; 

__attribute__((used)) static int handle_input_data_payload(struct st_h2o_http3client_req_t *req, const uint8_t **src, const uint8_t *src_end, int err,
                                     const char **err_desc)
{
    size_t payload_bytes = req->bytes_left_in_data_frame;
    const char *errstr;

    /* save data, update states */
    if (src_end - *src < payload_bytes)
        payload_bytes = src_end - *src;
    h2o_buffer_append(&req->recvbuf.body, *src, payload_bytes);
    *src += payload_bytes;
    req->bytes_left_in_data_frame -= payload_bytes;
    if (req->bytes_left_in_data_frame == 0)
        req->handle_input = handle_input_expect_data_frame;

    /* call the handler */
    errstr = NULL;
    if (*src == src_end && err != 0) {
        /* FIXME also check content-length? see what other protocol handlers do */
        errstr = err == H2O_HTTP3_ERROR_EOS && req->bytes_left_in_data_frame == 0 ? h2o_httpclient_error_is_eos : "reset by peer";
    } else {
        errstr = NULL;
    }
    if (req->super._cb.on_body(&req->super, errstr) != 0)
        return H2O_HTTP3_ERROR_INTERNAL;

    return 0;
}