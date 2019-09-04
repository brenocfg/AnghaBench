#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;
typedef  TYPE_1__ h2o_iovec_t ;
typedef  int /*<<< orphan*/  h2o_buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_HTTP2_FRAME_TYPE_ORIGIN ; 
 int /*<<< orphan*/ * allocate_frame (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void h2o_http2_encode_origin_frame(h2o_buffer_t **buf, h2o_iovec_t payload)
{
    uint8_t *dst = allocate_frame(buf, payload.len, H2O_HTTP2_FRAME_TYPE_ORIGIN, 0, 0);
    memcpy(dst, payload.base, payload.len);
}