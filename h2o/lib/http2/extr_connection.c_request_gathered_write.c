#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  timeout_entry; } ;
struct TYPE_11__ {TYPE_3__* ctx; } ;
struct TYPE_13__ {scalar_t__ state; TYPE_5__ _write; TYPE_4__ super; TYPE_2__* sock; } ;
typedef  TYPE_6__ h2o_http2_conn_t ;
struct TYPE_10__ {int /*<<< orphan*/  loop; } ;
struct TYPE_8__ {int /*<<< orphan*/ * write; } ;
struct TYPE_9__ {TYPE_1__ _cb; } ;

/* Variables and functions */
 scalar_t__ H2O_HTTP2_CONN_STATE_IS_CLOSING ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  h2o_timer_is_linked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_timer_link (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void request_gathered_write(h2o_http2_conn_t *conn)
{
    assert(conn->state < H2O_HTTP2_CONN_STATE_IS_CLOSING);
    if (conn->sock->_cb.write == NULL && !h2o_timer_is_linked(&conn->_write.timeout_entry)) {
        h2o_timer_link(conn->super.ctx->loop, 0, &conn->_write.timeout_entry);
    }
}