#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  buf; } ;
struct st_h2o_http2client_conn_t {TYPE_1__ output; } ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  h2o_http2_window_t ;

/* Variables and functions */
 size_t INT32_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  h2o_http2_encode_window_update_frame (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t h2o_http2_window_get_avail (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_http2_window_update (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  request_write (struct st_h2o_http2client_conn_t*) ; 

__attribute__((used)) static void enqueue_window_update(struct st_h2o_http2client_conn_t *conn, uint32_t stream_id, h2o_http2_window_t *window,
                                  size_t desired)
{
    assert(desired <= INT32_MAX);
    if (h2o_http2_window_get_avail(window) * 2 < desired) {
        int32_t delta = (int32_t)(desired - h2o_http2_window_get_avail(window));
        h2o_http2_encode_window_update_frame(&conn->output.buf, stream_id, delta);
        request_write(conn);
        h2o_http2_window_update(window, delta);
    }
}