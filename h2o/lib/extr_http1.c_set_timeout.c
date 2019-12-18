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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_7__ {int /*<<< orphan*/ * cb; } ;
struct TYPE_6__ {TYPE_1__* ctx; } ;
struct st_h2o_http1_conn_t {TYPE_3__ _timeout_entry; TYPE_2__ super; } ;
typedef  int /*<<< orphan*/ * h2o_timer_cb ;
struct TYPE_5__ {int /*<<< orphan*/  loop; } ;

/* Variables and functions */
 int /*<<< orphan*/  h2o_timer_link (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  h2o_timer_unlink (TYPE_3__*) ; 

__attribute__((used)) static void set_timeout(struct st_h2o_http1_conn_t *conn, uint64_t timeout, h2o_timer_cb cb)
{
    if (conn->_timeout_entry.cb != NULL)
        h2o_timer_unlink(&conn->_timeout_entry);
    conn->_timeout_entry.cb = cb;
    if (cb != NULL)
        h2o_timer_link(conn->super.ctx->loop, timeout, &conn->_timeout_entry);
}