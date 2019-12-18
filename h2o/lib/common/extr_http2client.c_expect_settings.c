#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {int /*<<< orphan*/  read_frame; } ;
struct st_h2o_http2client_conn_t {scalar_t__ state; TYPE_1__ input; } ;
typedef  int ssize_t ;
struct TYPE_6__ {scalar_t__ type; } ;
typedef  TYPE_2__ h2o_http2_frame_t ;

/* Variables and functions */
 scalar_t__ H2O_HTTP2CLIENT_CONN_STATE_IS_CLOSING ; 
 int H2O_HTTP2_ERROR_PROTOCOL_CLOSE_IMMEDIATELY ; 
 scalar_t__ H2O_HTTP2_FRAME_TYPE_SETTINGS ; 
 int /*<<< orphan*/  H2O_HTTP2_SETTINGS_CLIENT_MAX_FRAME_SIZE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  expect_default ; 
 int h2o_http2_decode_frame (TYPE_2__*,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ ,char const**) ; 
 int handle_settings_frame (struct st_h2o_http2client_conn_t*,TYPE_2__*,char const**) ; 

__attribute__((used)) static ssize_t expect_settings(struct st_h2o_http2client_conn_t *conn, const uint8_t *src, size_t len, const char **err_desc)
{
    assert(conn->state != H2O_HTTP2CLIENT_CONN_STATE_IS_CLOSING);

    h2o_http2_frame_t frame;
    ssize_t ret;

    if ((ret = h2o_http2_decode_frame(&frame, src, len, H2O_HTTP2_SETTINGS_CLIENT_MAX_FRAME_SIZE, err_desc)) < 0)
        return ret;

    if (frame.type != H2O_HTTP2_FRAME_TYPE_SETTINGS)
        return H2O_HTTP2_ERROR_PROTOCOL_CLOSE_IMMEDIATELY;

    int hret = handle_settings_frame(conn, &frame, err_desc);
    if (hret != 0)
        return hret;

    conn->input.read_frame = expect_default;
    return ret;
}