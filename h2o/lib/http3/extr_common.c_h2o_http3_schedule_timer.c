#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_9__ {scalar_t__ expire_at; } ;
struct TYPE_8__ {TYPE_3__ _timeout; TYPE_1__* ctx; int /*<<< orphan*/  quic; } ;
typedef  TYPE_2__ h2o_http3_conn_t ;
struct TYPE_7__ {int /*<<< orphan*/  loop; } ;

/* Variables and functions */
 scalar_t__ h2o_now (int /*<<< orphan*/ ) ; 
 scalar_t__ h2o_timer_is_linked (TYPE_3__*) ; 
 int /*<<< orphan*/  h2o_timer_link (int /*<<< orphan*/ ,scalar_t__,TYPE_3__*) ; 
 int /*<<< orphan*/  h2o_timer_unlink (TYPE_3__*) ; 
 scalar_t__ quicly_get_first_timeout (int /*<<< orphan*/ ) ; 

void h2o_http3_schedule_timer(h2o_http3_conn_t *conn)
{
    int64_t timeout = quicly_get_first_timeout(conn->quic);
    if (h2o_timer_is_linked(&conn->_timeout)) {
#if !H2O_USE_LIBUV /* optimization to skip registering a timer specifying the same time */
        if (timeout == conn->_timeout.expire_at)
            return;
#endif
        h2o_timer_unlink(&conn->_timeout);
    }
    uint64_t now = h2o_now(conn->ctx->loop), delay = now < timeout ? timeout - now : 0;
    h2o_timer_link(conn->ctx->loop, delay, &conn->_timeout);
}