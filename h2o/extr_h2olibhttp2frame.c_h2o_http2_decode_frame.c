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
typedef  size_t ssize_t ;
struct TYPE_3__ {size_t length; int stream_id; int /*<<< orphan*/  const* payload; int /*<<< orphan*/  flags; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ h2o_http2_frame_t ;

/* Variables and functions */
 size_t H2O_HTTP2_ERROR_FRAME_SIZE ; 
 size_t H2O_HTTP2_ERROR_INCOMPLETE ; 
 size_t H2O_HTTP2_FRAME_HEADER_SIZE ; 
 size_t h2o_http2_decode24u (int /*<<< orphan*/  const*) ; 
 int h2o_http2_decode32u (int /*<<< orphan*/  const*) ; 

ssize_t h2o_http2_decode_frame(h2o_http2_frame_t *frame, const uint8_t *src, size_t len, size_t max_frame_size,
                               const char **err_desc)
{
    if (len < H2O_HTTP2_FRAME_HEADER_SIZE)
        return H2O_HTTP2_ERROR_INCOMPLETE;

    frame->length = h2o_http2_decode24u(src);
    frame->type = src[3];
    frame->flags = src[4];
    frame->stream_id = h2o_http2_decode32u(src + 5) & 0x7fffffff;

    if (frame->length > max_frame_size)
        return H2O_HTTP2_ERROR_FRAME_SIZE;

    if (len < H2O_HTTP2_FRAME_HEADER_SIZE + frame->length)
        return H2O_HTTP2_ERROR_INCOMPLETE;

    frame->payload = src + H2O_HTTP2_FRAME_HEADER_SIZE;

    return H2O_HTTP2_FRAME_HEADER_SIZE + frame->length;
}