#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_12__ ;

/* Type definitions */
struct TYPE_21__ {int /*<<< orphan*/  cb; } ;
struct TYPE_18__ {TYPE_4__* ctx; } ;
struct TYPE_14__ {scalar_t__ blocked_by_server; } ;
struct TYPE_19__ {int /*<<< orphan*/ * buf_in_flight; } ;
struct TYPE_20__ {TYPE_9__ _timeout_entry; TYPE_5__ super; TYPE_1__ num_streams; TYPE_12__* sock; TYPE_6__ _write; } ;
typedef  TYPE_7__ h2o_http2_conn_t ;
struct TYPE_17__ {TYPE_3__* globalconf; int /*<<< orphan*/  loop; } ;
struct TYPE_15__ {int /*<<< orphan*/  idle_timeout; } ;
struct TYPE_16__ {TYPE_2__ http2; } ;
struct TYPE_13__ {int /*<<< orphan*/ * ssl; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ h2o_socket_ssl_is_early_data (TYPE_12__*) ; 
 int /*<<< orphan*/  h2o_timer_is_linked (TYPE_9__*) ; 
 int /*<<< orphan*/  h2o_timer_link (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_9__*) ; 
 int /*<<< orphan*/  h2o_timer_unlink (TYPE_9__*) ; 
 int /*<<< orphan*/  on_idle_timeout ; 

__attribute__((used)) static void update_idle_timeout(h2o_http2_conn_t *conn)
{
    /* do nothing touch anything if write is in progress */
    if (conn->_write.buf_in_flight != NULL) {
        assert(h2o_timer_is_linked(&conn->_timeout_entry));
        return;
    }

    h2o_timer_unlink(&conn->_timeout_entry);

    /* always set idle timeout if TLS handshake is in progress */
    if (conn->sock->ssl != NULL && h2o_socket_ssl_is_early_data(conn->sock))
        goto SetTimeout;

    /* no need to set timeout if pending requests exist */
    if (conn->num_streams.blocked_by_server != 0)
        return;

SetTimeout:
    conn->_timeout_entry.cb = on_idle_timeout;
    h2o_timer_link(conn->super.ctx->loop, conn->super.ctx->globalconf->http2.idle_timeout, &conn->_timeout_entry);
}