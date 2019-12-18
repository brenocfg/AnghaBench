#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ state; int /*<<< orphan*/ * ssltunnel_ostream; int /*<<< orphan*/  allocator; int /*<<< orphan*/  skt; int /*<<< orphan*/ * stream; int /*<<< orphan*/ * ostream_head; int /*<<< orphan*/ * ostream_tail; scalar_t__ connect_time; scalar_t__ latency; } ;
typedef  TYPE_1__ serf_connection_t ;
typedef  int /*<<< orphan*/  serf_bucket_t ;
typedef  scalar_t__ apr_status_t ;

/* Variables and functions */
 scalar_t__ APR_SUCCESS ; 
 scalar_t__ SERF_CONN_CONNECTED ; 
 scalar_t__ apr_time_now () ; 
 scalar_t__ do_conn_setup (TYPE_1__*) ; 
 int /*<<< orphan*/ * serf_bucket_socket_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static apr_status_t prepare_conn_streams(serf_connection_t *conn,
                                         serf_bucket_t **istream,
                                         serf_bucket_t **ostreamt,
                                         serf_bucket_t **ostreamh)
{
    apr_status_t status;

    if (conn->stream == NULL) {
        conn->latency = apr_time_now() - conn->connect_time;
    }

    /* Do we need a SSL tunnel first? */
    if (conn->state == SERF_CONN_CONNECTED) {
        /* If the connection does not have an associated bucket, then
         * call the setup callback to get one.
         */
        if (conn->stream == NULL) {
            status = do_conn_setup(conn);
            if (status) {
                return status;
            }
        }
        *ostreamt = conn->ostream_tail;
        *ostreamh = conn->ostream_head;
        *istream = conn->stream;
    } else {
        /* SSL tunnel needed and not set up yet, get a direct unencrypted
         stream for this socket */
        if (conn->stream == NULL) {
            *istream = serf_bucket_socket_create(conn->skt,
                                                 conn->allocator);
        }
        /* Don't create the ostream bucket chain including the ssl_encrypt
         bucket yet. This ensure the CONNECT request is sent unencrypted
         to the proxy. */
        *ostreamt = *ostreamh = conn->ssltunnel_ostream;
    }

    return APR_SUCCESS;
}