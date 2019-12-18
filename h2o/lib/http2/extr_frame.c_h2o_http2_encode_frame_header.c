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
typedef  void* uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  h2o_fatal (char*) ; 
 void** h2o_http2_encode24u (void**,int /*<<< orphan*/ ) ; 
 void** h2o_http2_encode32u (void**,int /*<<< orphan*/ ) ; 

uint8_t *h2o_http2_encode_frame_header(uint8_t *dst, size_t length, uint8_t type, uint8_t flags, int32_t stream_id)
{
    if (length > 0xffffff)
        h2o_fatal("invalid length");

    dst = h2o_http2_encode24u(dst, (uint32_t)length);
    *dst++ = type;
    *dst++ = flags;
    dst = h2o_http2_encode32u(dst, stream_id);

    return dst;
}