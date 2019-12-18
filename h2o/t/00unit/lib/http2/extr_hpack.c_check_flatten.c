#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_12__ {int /*<<< orphan*/  size; int /*<<< orphan*/  entries; } ;
struct TYPE_13__ {TYPE_1__ headers; int /*<<< orphan*/  status; } ;
typedef  TYPE_2__ h2o_res_t ;
struct TYPE_14__ {int /*<<< orphan*/  length; int /*<<< orphan*/  payload; } ;
typedef  TYPE_3__ h2o_http2_frame_t ;
typedef  int /*<<< orphan*/  h2o_hpack_header_table_t ;
struct TYPE_15__ {int /*<<< orphan*/  size; scalar_t__ bytes; } ;
typedef  TYPE_4__ h2o_buffer_t ;
struct TYPE_11__ {int /*<<< orphan*/  max_frame_size; } ;

/* Variables and functions */
 TYPE_10__ H2O_HTTP2_SETTINGS_DEFAULT ; 
 int /*<<< orphan*/  SIZE_MAX ; 
 int /*<<< orphan*/  h2o_buffer_dispose (TYPE_4__**) ; 
 int /*<<< orphan*/  h2o_buffer_init (TYPE_4__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_hpack_flatten_response (TYPE_4__**,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ h2o_http2_decode_frame (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const**) ; 
 int h2o_memis (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,size_t) ; 
 int /*<<< orphan*/  h2o_socket_buffer_prototype ; 
 int /*<<< orphan*/  ok (int) ; 

__attribute__((used)) static void check_flatten(h2o_hpack_header_table_t *header_table, h2o_res_t *res, const char *expected, size_t expected_len)
{
    h2o_buffer_t *buf;
    h2o_http2_frame_t frame;
    const char *err_desc;

    h2o_buffer_init(&buf, &h2o_socket_buffer_prototype);
    h2o_hpack_flatten_response(&buf, header_table, 1, H2O_HTTP2_SETTINGS_DEFAULT.max_frame_size, res->status, res->headers.entries,
                               res->headers.size, NULL, SIZE_MAX);

    ok(h2o_http2_decode_frame(&frame, (uint8_t *)buf->bytes, buf->size, H2O_HTTP2_SETTINGS_DEFAULT.max_frame_size, &err_desc) > 0);
    ok(h2o_memis(frame.payload, frame.length, expected, expected_len));

    h2o_buffer_dispose(&buf);
}