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
struct TYPE_6__ {size_t bytes_left_in_data_frame; int /*<<< orphan*/  handle_input; } ;
struct TYPE_5__ {size_t req_body_bytes_received; int /*<<< orphan*/  entity; } ;
struct st_h2o_http3_server_stream_t {TYPE_2__ recvbuf; TYPE_1__ req; TYPE_3__* req_body; } ;
struct TYPE_7__ {int /*<<< orphan*/  size; int /*<<< orphan*/  bytes; } ;

/* Variables and functions */
 int H2O_HTTP3_ERROR_INTERNAL ; 
 int /*<<< orphan*/  h2o_buffer_init (TYPE_3__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_buffer_try_append (TYPE_3__**,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  h2o_iovec_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_socket_buffer_prototype ; 
 int /*<<< orphan*/  handle_input_expect_data ; 

__attribute__((used)) static int handle_input_expect_data_payload(struct st_h2o_http3_server_stream_t *stream, const uint8_t **src,
                                            const uint8_t *src_end, const char **err_desc)
{
    size_t bytes_avail = src_end - *src;

    /* append data to body buffer */
    if (bytes_avail > stream->recvbuf.bytes_left_in_data_frame)
        bytes_avail = stream->recvbuf.bytes_left_in_data_frame;
    if (stream->req_body == NULL)
        h2o_buffer_init(&stream->req_body, &h2o_socket_buffer_prototype);
    if (!h2o_buffer_try_append(&stream->req_body, *src, bytes_avail))
        return H2O_HTTP3_ERROR_INTERNAL;
    stream->req.entity = h2o_iovec_init(stream->req_body->bytes, stream->req_body->size);
    stream->req.req_body_bytes_received += bytes_avail;
    stream->recvbuf.bytes_left_in_data_frame -= bytes_avail;
    *src += bytes_avail;

    if (stream->recvbuf.bytes_left_in_data_frame == 0)
        stream->recvbuf.handle_input = handle_input_expect_data;

    return 0;
}