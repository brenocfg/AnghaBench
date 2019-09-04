#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  h2o_http2_window_t ;
struct TYPE_5__ {int /*<<< orphan*/  buf; } ;
struct TYPE_6__ {TYPE_1__ _write; } ;
typedef  TYPE_2__ h2o_http2_conn_t ;

/* Variables and functions */
 size_t INT32_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  h2o_http2_conn_request_write (TYPE_2__*) ; 
 int /*<<< orphan*/  h2o_http2_encode_window_update_frame (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_http2_window_update (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void send_window_update(h2o_http2_conn_t *conn, uint32_t stream_id, h2o_http2_window_t *window, size_t delta)
{
    assert(delta <= INT32_MAX);
    h2o_http2_encode_window_update_frame(&conn->_write.buf, stream_id, (int32_t)delta);
    h2o_http2_conn_request_write(conn);
    h2o_http2_window_update(window, delta);
}