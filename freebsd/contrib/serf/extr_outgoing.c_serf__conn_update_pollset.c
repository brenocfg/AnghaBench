#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  pollset_baton; scalar_t__ (* pollset_add ) (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *) ;scalar_t__ (* pollset_rm ) (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_2__ serf_context_t ;
struct TYPE_11__ {int reqevents; scalar_t__ state; int stop_writing; scalar_t__ probable_keepalive_limit; scalar_t__ completed_requests; scalar_t__ max_outstanding_requests; scalar_t__ completed_responses; int /*<<< orphan*/  baton; scalar_t__ async_responses; scalar_t__ vec_len; scalar_t__ requests; scalar_t__ skt; TYPE_2__* ctx; } ;
typedef  TYPE_3__ serf_connection_t ;
typedef  scalar_t__ apr_status_t ;
struct TYPE_9__ {scalar_t__ s; } ;
struct TYPE_12__ {int reqevents; TYPE_1__ desc; int /*<<< orphan*/  desc_type; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_4__ apr_pollfd_t ;

/* Variables and functions */
 int APR_POLLERR ; 
 int APR_POLLHUP ; 
 int APR_POLLIN ; 
 int APR_POLLOUT ; 
 int /*<<< orphan*/  APR_POLL_SOCKET ; 
 int /*<<< orphan*/  APR_STATUS_IS_NOTFOUND (scalar_t__) ; 
 scalar_t__ APR_SUCCESS ; 
 scalar_t__ SERF_CONN_CLOSING ; 
 scalar_t__ SERF_CONN_INIT ; 
 scalar_t__ request_or_data_pending (int /*<<< orphan*/ *,TYPE_3__*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *) ; 

apr_status_t serf__conn_update_pollset(serf_connection_t *conn)
{
    serf_context_t *ctx = conn->ctx;
    apr_status_t status;
    apr_pollfd_t desc = { 0 };

    if (!conn->skt) {
        return APR_SUCCESS;
    }

    /* Remove the socket from the poll set. */
    desc.desc_type = APR_POLL_SOCKET;
    desc.desc.s = conn->skt;
    desc.reqevents = conn->reqevents;

    status = ctx->pollset_rm(ctx->pollset_baton,
                             &desc, &conn->baton);
    if (status && !APR_STATUS_IS_NOTFOUND(status))
        return status;

    /* Now put it back in with the correct read/write values. */
    desc.reqevents = APR_POLLHUP | APR_POLLERR;
    if (conn->requests &&
        conn->state != SERF_CONN_INIT) {
        /* If there are any outstanding events, then we want to read. */
        /* ### not true. we only want to read IF we have sent some data */
        desc.reqevents |= APR_POLLIN;

        /* Don't write if OpenSSL told us that it needs to read data first. */
        if (conn->stop_writing != 1) {

            /* If the connection is not closing down and
             *   has unwritten data or
             *   there are any requests that still have buckets to write out,
             *     then we want to write.
             */
            if (conn->vec_len &&
                conn->state != SERF_CONN_CLOSING)
                desc.reqevents |= APR_POLLOUT;
            else {

                if ((conn->probable_keepalive_limit &&
                     conn->completed_requests > conn->probable_keepalive_limit) ||
                    (conn->max_outstanding_requests &&
                     conn->completed_requests - conn->completed_responses >=
                     conn->max_outstanding_requests)) {
                        /* we wouldn't try to write any way right now. */
                }
                else if (request_or_data_pending(NULL, conn)) {
                    desc.reqevents |= APR_POLLOUT;
                }
            }
        }
    }

    /* If we can have async responses, always look for something to read. */
    if (conn->async_responses) {
        desc.reqevents |= APR_POLLIN;
    }

    /* save our reqevents, so we can pass it in to remove later. */
    conn->reqevents = desc.reqevents;

    /* Note: even if we don't want to read/write this socket, we still
     * want to poll it for hangups and errors.
     */
    return ctx->pollset_add(ctx->pollset_baton,
                            &desc, &conn->baton);
}