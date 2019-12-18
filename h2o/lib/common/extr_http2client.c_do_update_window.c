#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  window; TYPE_2__* body; } ;
struct TYPE_4__ {int /*<<< orphan*/  ctx; } ;
struct st_h2o_http2client_stream_t {TYPE_3__ input; int /*<<< orphan*/  stream_id; int /*<<< orphan*/  conn; TYPE_1__ super; } ;
typedef  int /*<<< orphan*/  h2o_httpclient_t ;
struct TYPE_5__ {size_t size; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  enqueue_window_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 size_t get_max_buffer_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_update_window(h2o_httpclient_t *_client)
{
    struct st_h2o_http2client_stream_t *stream = (void *)_client;
    size_t max = get_max_buffer_size(stream->super.ctx);
    size_t bufsize = stream->input.body->size;
    assert(bufsize <= max);
    enqueue_window_update(stream->conn, stream->stream_id, &stream->input.window, max - bufsize);
}