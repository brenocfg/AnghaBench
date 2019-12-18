#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int seen_in_pollset; scalar_t__ completed_requests; TYPE_1__* address; int /*<<< orphan*/  skt; int /*<<< orphan*/  probable_keepalive_limit; scalar_t__ completed_responses; } ;
typedef  TYPE_2__ serf_connection_t ;
typedef  int /*<<< orphan*/  error ;
typedef  int /*<<< orphan*/  apr_status_t ;
typedef  int apr_socklen_t ;
typedef  int /*<<< orphan*/  apr_os_sock_t ;
typedef  int apr_int16_t ;
struct TYPE_7__ {struct TYPE_7__* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  APR_EGENERAL ; 
 int /*<<< orphan*/  APR_FROM_OS_ERROR (int) ; 
 int APR_POLLERR ; 
 int APR_POLLHUP ; 
 int APR_POLLIN ; 
 int APR_POLLOUT ; 
 scalar_t__ APR_STATUS_IS_ECONNREFUSED (int /*<<< orphan*/ ) ; 
 scalar_t__ APR_STATUS_IS_ENETUNREACH (int /*<<< orphan*/ ) ; 
 scalar_t__ APR_STATUS_IS_TIMEUP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  APR_SUCCESS ; 
 int /*<<< orphan*/  SERF_ERROR_ABORTED_CONNECTION ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_ERROR ; 
 int /*<<< orphan*/  apr_os_sock_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  read_from_connection (TYPE_2__*) ; 
 int /*<<< orphan*/  reset_connection (TYPE_2__*,int) ; 
 int /*<<< orphan*/  write_to_connection (TYPE_2__*) ; 

apr_status_t serf__process_connection(serf_connection_t *conn,
                                      apr_int16_t events)
{
    apr_status_t status;

    /* POLLHUP/ERR should come after POLLIN so if there's an error message or
     * the like sitting on the connection, we give the app a chance to read
     * it before we trigger a reset condition.
     */
    if ((events & APR_POLLIN) != 0) {
        if ((status = read_from_connection(conn)) != APR_SUCCESS)
            return status;

        /* If we decided to reset our connection, return now as we don't
         * want to write.
         */
        if ((conn->seen_in_pollset & APR_POLLHUP) != 0) {
            return APR_SUCCESS;
        }
    }
    if ((events & APR_POLLHUP) != 0) {
        /* The connection got reset by the server. On Windows this can happen
           when all data is read, so just cleanup the connection and open
           a new one.
           If we haven't had any successful responses on this connection,
           then error out as it is likely a server issue. */
        if (conn->completed_responses) {
            return reset_connection(conn, 1);
        }
        return SERF_ERROR_ABORTED_CONNECTION;
    }
    if ((events & APR_POLLERR) != 0) {
        /* We might be talking to a buggy HTTP server that doesn't
         * do lingering-close.  (httpd < 2.1.8 does this.)
         *
         * See:
         *
         * http://issues.apache.org/bugzilla/show_bug.cgi?id=35292
         */
        if (conn->completed_requests && !conn->probable_keepalive_limit) {
            return reset_connection(conn, 1);
        }
#ifdef SO_ERROR
        /* If possible, get the error from the platform's socket layer and
           convert it to an APR status code. */
        {
            apr_os_sock_t osskt;
            if (!apr_os_sock_get(&osskt, conn->skt)) {
                int error;
                apr_socklen_t l = sizeof(error);

                if (!getsockopt(osskt, SOL_SOCKET, SO_ERROR, (char*)&error,
                                &l)) {
                    status = APR_FROM_OS_ERROR(error);

                    /* Handle fallback for multi-homed servers.
                     
                       ### Improve algorithm to find better than just 'next'?

                       Current Windows versions already handle re-ordering for
                       api users by using statistics on the recently failed
                       connections to order the list of addresses. */
                    if (conn->completed_requests == 0
                        && conn->address->next != NULL
                        && (APR_STATUS_IS_ECONNREFUSED(status)
                            || APR_STATUS_IS_TIMEUP(status)
                            || APR_STATUS_IS_ENETUNREACH(status))) {

                        conn->address = conn->address->next;
                        return reset_connection(conn, 1);
                    }

                    return status;
                  }
            }
        }
#endif
        return APR_EGENERAL;
    }
    if ((events & APR_POLLOUT) != 0) {
        if ((status = write_to_connection(conn)) != APR_SUCCESS)
            return status;
    }
    return APR_SUCCESS;
}