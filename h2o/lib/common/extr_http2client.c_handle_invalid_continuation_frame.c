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
struct st_h2o_http2client_conn_t {int dummy; } ;
typedef  int /*<<< orphan*/  h2o_http2_frame_t ;

/* Variables and functions */
 int H2O_HTTP2_ERROR_PROTOCOL ; 

__attribute__((used)) static int handle_invalid_continuation_frame(struct st_h2o_http2client_conn_t *conn, h2o_http2_frame_t *frame,
                                             const char **err_desc)
{
    *err_desc = "received invalid CONTINUATION frame";
    return H2O_HTTP2_ERROR_PROTOCOL;
}