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
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  h2o_buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_HTTP2_FRAME_TYPE_WINDOW_UPDATE ; 
 int /*<<< orphan*/ * allocate_frame (int /*<<< orphan*/ **,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * h2o_http2_encode32u (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void h2o_http2_encode_window_update_frame(h2o_buffer_t **buf, uint32_t stream_id, int32_t window_size_increment)
{
    uint8_t *dst = allocate_frame(buf, 4, H2O_HTTP2_FRAME_TYPE_WINDOW_UPDATE, 0, stream_id);
    dst = h2o_http2_encode32u(dst, window_size_increment);
}