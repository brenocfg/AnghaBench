#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_6__ {scalar_t__ base; } ;
typedef  TYPE_1__ h2o_iovec_t ;
struct TYPE_7__ {int /*<<< orphan*/  size; } ;
typedef  TYPE_2__ h2o_buffer_t ;

/* Variables and functions */
 scalar_t__ H2O_HTTP2_FRAME_HEADER_SIZE ; 
 TYPE_1__ h2o_buffer_reserve (TYPE_2__**,scalar_t__) ; 
 int /*<<< orphan*/ * h2o_http2_encode_frame_header (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint8_t *allocate_frame(h2o_buffer_t **buf, size_t length, uint8_t type, uint8_t flags, int32_t stream_id)
{
    h2o_iovec_t alloced = h2o_buffer_reserve(buf, H2O_HTTP2_FRAME_HEADER_SIZE + length);
    (*buf)->size += H2O_HTTP2_FRAME_HEADER_SIZE + length;
    return h2o_http2_encode_frame_header((uint8_t *)alloced.base, length, type, flags, stream_id);
}