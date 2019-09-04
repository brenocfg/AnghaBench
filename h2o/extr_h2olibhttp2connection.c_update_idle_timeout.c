#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
struct TYPE_20__ {int /*<<< orphan*/  cb; } ;
struct TYPE_18__ {TYPE_5__* ctx; } ;
struct TYPE_14__ {int /*<<< orphan*/ * buf_in_flight; } ;
struct TYPE_13__ {scalar_t__ blocked_by_server; } ;
struct TYPE_19__ {TYPE_9__ _timeout_entry; TYPE_6__ super; TYPE_2__ _write; TYPE_1__ num_streams; TYPE_11__* sock; } ;
typedef  TYPE_7__ h2o_http2_conn_t ;
struct TYPE_17__ {TYPE_4__* globalconf; int /*<<< orphan*/  loop; } ;
struct TYPE_15__ {int /*<<< orphan*/  idle_timeout; } ;
struct TYPE_16__ {TYPE_3__ http2; } ;
struct TYPE_12__ {int /*<<< orphan*/ * ssl; } ;

/* Variables and functions */
 scalar_t__ h2o_socket_ssl_is_early_data (TYPE_11__*) ; 
 int /*<<< orphan*/  h2o_timer_link (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_9__*) ; 
 int /*<<< orphan*/  h2o_timer_unlink (TYPE_9__*) ; 
 int /*<<< orphan*/  on_idle_timeout ; 

__attribute__((used)) static void update_idle_timeout(h2o_http2_conn_t *conn)
{
    h2o_timer_unlink(&conn->_timeout_entry);

    /* always set idle timeout if TLS handshake is in progress */
    if (conn->sock->ssl != NULL && h2o_socket_ssl_is_early_data(conn->sock))
        goto SetTimeout;

    /* no need to set timeout if pending requests exist */
    if (conn->num_streams.blocked_by_server != 0)
        return;

    /* no need to set timeout if write is in flight */
    if (conn->_write.buf_in_flight != NULL)
        return;

SetTimeout:
    conn->_timeout_entry.cb = on_idle_timeout;
    h2o_timer_link(conn->super.ctx->loop, conn->super.ctx->globalconf->http2.idle_timeout, &conn->_timeout_entry);
}