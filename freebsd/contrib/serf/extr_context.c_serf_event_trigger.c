#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  serf_listener_t ;
struct TYPE_13__ {int /*<<< orphan*/ * client; int /*<<< orphan*/ * listener; TYPE_5__* conn; } ;
struct TYPE_14__ {scalar_t__ type; TYPE_2__ u; } ;
typedef  TYPE_3__ serf_io_baton_t ;
typedef  int /*<<< orphan*/  serf_incoming_t ;
struct TYPE_15__ {int /*<<< orphan*/  pollset_baton; int /*<<< orphan*/  (* pollset_rm ) (int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_4__ serf_context_t ;
struct TYPE_16__ {scalar_t__ status; int seen_in_pollset; int /*<<< orphan*/  baton; int /*<<< orphan*/  reqevents; scalar_t__ skt; TYPE_4__* ctx; } ;
typedef  TYPE_5__ serf_connection_t ;
typedef  scalar_t__ apr_status_t ;
struct TYPE_12__ {scalar_t__ s; } ;
struct TYPE_17__ {int rtnevents; int /*<<< orphan*/  reqevents; TYPE_1__ desc; void* desc_type; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_6__ apr_pollfd_t ;

/* Variables and functions */
 int APR_POLLHUP ; 
 void* APR_POLL_SOCKET ; 
 scalar_t__ APR_SUCCESS ; 
 scalar_t__ SERF_IO_CLIENT ; 
 scalar_t__ SERF_IO_CONN ; 
 scalar_t__ SERF_IO_LISTENER ; 
 scalar_t__ serf__process_client (int /*<<< orphan*/ *,int) ; 
 scalar_t__ serf__process_connection (TYPE_5__*,int) ; 
 scalar_t__ serf__process_listener (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ *) ; 

apr_status_t serf_event_trigger(
    serf_context_t *s,
    void *serf_baton,
    const apr_pollfd_t *desc)
{
    apr_pollfd_t tdesc = { 0 };
    apr_status_t status = APR_SUCCESS;
    serf_io_baton_t *io = serf_baton;

    if (io->type == SERF_IO_CONN) {
        serf_connection_t *conn = io->u.conn;
        serf_context_t *ctx = conn->ctx;

        /* If this connection has already failed, return the error again, and try
         * to remove it from the pollset again
         */
        if (conn->status) {
            tdesc.desc_type = APR_POLL_SOCKET;
            tdesc.desc.s = conn->skt;
            tdesc.reqevents = conn->reqevents;
            ctx->pollset_rm(ctx->pollset_baton,
                            &tdesc, &conn->baton);
            return conn->status;
        }
        /* apr_pollset_poll() can return a conn multiple times... */
        if ((conn->seen_in_pollset & desc->rtnevents) != 0 ||
            (conn->seen_in_pollset & APR_POLLHUP) != 0) {
            return APR_SUCCESS;
        }

        conn->seen_in_pollset |= desc->rtnevents;

        if ((conn->status = serf__process_connection(conn,
                                         desc->rtnevents)) != APR_SUCCESS) {

            /* it's possible that the connection was already reset and thus the
               socket cleaned up. */
            if (conn->skt) {
                tdesc.desc_type = APR_POLL_SOCKET;
                tdesc.desc.s = conn->skt;
                tdesc.reqevents = conn->reqevents;
                ctx->pollset_rm(ctx->pollset_baton,
                                &tdesc, &conn->baton);
            }
            return conn->status;
        }
    }
    else if (io->type == SERF_IO_LISTENER) {
        serf_listener_t *l = io->u.listener;

        status = serf__process_listener(l);

        if (status) {
            return status;
        }
    }
    else if (io->type == SERF_IO_CLIENT) {
        serf_incoming_t *c = io->u.client;

        status = serf__process_client(c, desc->rtnevents);

        if (status) {
            return status;
        }
    }
    return status;
}