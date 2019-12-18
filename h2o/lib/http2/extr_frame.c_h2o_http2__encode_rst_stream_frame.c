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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  h2o_buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_HTTP2_FRAME_TYPE_RST_STREAM ; 
 int /*<<< orphan*/ * allocate_frame (int /*<<< orphan*/ **,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * h2o_http2_encode32u (int /*<<< orphan*/ *,int) ; 

void h2o_http2__encode_rst_stream_frame(h2o_buffer_t **buf, uint32_t stream_id, int errnum)
{
    uint8_t *dst = allocate_frame(buf, 4, H2O_HTTP2_FRAME_TYPE_RST_STREAM, 0, stream_id);
    dst = h2o_http2_encode32u(dst, errnum);
}