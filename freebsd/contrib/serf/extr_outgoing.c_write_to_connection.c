#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int writing_started; int /*<<< orphan*/  next; int /*<<< orphan*/ * req_bkt; } ;
typedef  TYPE_2__ serf_request_t ;
struct TYPE_14__ {scalar_t__ probable_keepalive_limit; scalar_t__ completed_requests; int dirty_conn; int max_outstanding_requests; scalar_t__ state; int completed_responses; scalar_t__ vec_len; int stop_writing; int /*<<< orphan*/  requests; scalar_t__ async_responses; scalar_t__ hit_eof; TYPE_1__* ctx; int /*<<< orphan*/  vec; int /*<<< orphan*/  stream; } ;
typedef  TYPE_3__ serf_connection_t ;
typedef  int /*<<< orphan*/  serf_bucket_t ;
typedef  scalar_t__ apr_status_t ;
struct TYPE_12__ {int dirty_pollset; } ;

/* Variables and functions */
 scalar_t__ APR_STATUS_IS_EAGAIN (scalar_t__) ; 
 scalar_t__ APR_STATUS_IS_ECONNABORTED (scalar_t__) ; 
 scalar_t__ APR_STATUS_IS_ECONNRESET (scalar_t__) ; 
 int /*<<< orphan*/  APR_STATUS_IS_EOF (scalar_t__) ; 
 scalar_t__ APR_STATUS_IS_EPIPE (scalar_t__) ; 
 scalar_t__ APR_SUCCESS ; 
 int /*<<< orphan*/  IOV_MAX ; 
 scalar_t__ SERF_CONN_CONNECTED ; 
 scalar_t__ SERF_ERROR_WAIT_CONN ; 
 int /*<<< orphan*/  SERF_READ_ALL_AVAIL ; 
 int /*<<< orphan*/  destroy_request (TYPE_2__*) ; 
 scalar_t__ no_more_writes (TYPE_3__*) ; 
 scalar_t__ prepare_conn_streams (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  request_or_data_pending (TYPE_2__**,TYPE_3__*) ; 
 int /*<<< orphan*/  serf_bucket_aggregate_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serf_bucket_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ serf_bucket_read_iovec (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ setup_request (TYPE_2__*) ; 
 scalar_t__ socket_writev (TYPE_3__*) ; 

__attribute__((used)) static apr_status_t write_to_connection(serf_connection_t *conn)
{
    if (conn->probable_keepalive_limit &&
        conn->completed_requests > conn->probable_keepalive_limit) {

        conn->dirty_conn = 1;
        conn->ctx->dirty_pollset = 1;

        /* backoff for now. */
        return APR_SUCCESS;
    }

    /* Keep reading and sending until we run out of stuff to read, or
     * writing would block.
     */
    while (1) {
        serf_request_t *request;
        int stop_reading = 0;
        apr_status_t status;
        apr_status_t read_status;
        serf_bucket_t *ostreamt;
        serf_bucket_t *ostreamh;
        int max_outstanding_requests = conn->max_outstanding_requests;

        /* If we're setting up an ssl tunnel, we can't send real requests
           at yet, as they need to be encrypted and our encrypt buckets
           aren't created yet as we still need to read the unencrypted
           response of the CONNECT request. */
        if (conn->state != SERF_CONN_CONNECTED)
            max_outstanding_requests = 1;

        if (max_outstanding_requests &&
            conn->completed_requests -
                conn->completed_responses >= max_outstanding_requests) {
            /* backoff for now. */
            return APR_SUCCESS;
        }

        /* If we have unwritten data, then write what we can. */
        while (conn->vec_len) {
            status = socket_writev(conn);

            /* If the write would have blocked, then we're done. Don't try
             * to write anything else to the socket.
             */
            if (APR_STATUS_IS_EAGAIN(status))
                return APR_SUCCESS;
            if (APR_STATUS_IS_EPIPE(status) ||
                APR_STATUS_IS_ECONNRESET(status) ||
                APR_STATUS_IS_ECONNABORTED(status))
                return no_more_writes(conn);
            if (status)
                return status;
        }
        /* ### can we have a short write, yet no EAGAIN? a short write
           ### would imply unwritten_len > 0 ... */
        /* assert: unwritten_len == 0. */

        /* We may need to move forward to a request which has something
         * to write.
         */
        if (!request_or_data_pending(&request, conn)) {
            /* No more requests (with data) are registered with the
             * connection, and no data is pending on the outgoing stream.
             * Let's update the pollset so that we don't try to write to this
             * socket again.
             */
            conn->dirty_conn = 1;
            conn->ctx->dirty_pollset = 1;
            return APR_SUCCESS;
        }

        status = prepare_conn_streams(conn, &conn->stream, &ostreamt, &ostreamh);
        if (status) {
            return status;
        }

        if (request) {
            if (request->req_bkt == NULL) {
                read_status = setup_request(request);
                if (read_status) {
                    /* Something bad happened. Propagate any errors. */
                    return read_status;
                }
            }

            if (!request->writing_started) {
                request->writing_started = 1;
                serf_bucket_aggregate_append(ostreamt, request->req_bkt);
            }
        }

        /* ### optimize at some point by using read_for_sendfile */
        /* TODO: now that read_iovec will effectively try to return as much
           data as available, we probably don't want to read ALL_AVAIL, but
           a lower number, like the size of one or a few TCP packets, the
           available TCP buffer size ... */
        read_status = serf_bucket_read_iovec(ostreamh,
                                             SERF_READ_ALL_AVAIL,
                                             IOV_MAX,
                                             conn->vec,
                                             &conn->vec_len);

        if (!conn->hit_eof) {
            if (APR_STATUS_IS_EAGAIN(read_status)) {
                /* We read some stuff, but should not try to read again. */
                stop_reading = 1;
            }
            else if (read_status == SERF_ERROR_WAIT_CONN) {
                /* The bucket told us that it can't provide more data until
                   more data is read from the socket. This normally happens
                   during a SSL handshake.

                   We should avoid looking for writability for a while so
                   that (hopefully) something will appear in the bucket so
                   we can actually write something. otherwise, we could
                   end up in a CPU spin: socket wants something, but we
                   don't have anything (and keep returning EAGAIN)
                 */
                conn->stop_writing = 1;
                conn->dirty_conn = 1;
                conn->ctx->dirty_pollset = 1;
            }
            else if (read_status && !APR_STATUS_IS_EOF(read_status)) {
                /* Something bad happened. Propagate any errors. */
                return read_status;
            }
        }

        /* If we got some data, then deliver it. */
        /* ### what to do if we got no data?? is that a problem? */
        if (conn->vec_len > 0) {
            status = socket_writev(conn);

            /* If we can't write any more, or an error occurred, then
             * we're done here.
             */
            if (APR_STATUS_IS_EAGAIN(status))
                return APR_SUCCESS;
            if (APR_STATUS_IS_EPIPE(status))
                return no_more_writes(conn);
            if (APR_STATUS_IS_ECONNRESET(status) ||
                APR_STATUS_IS_ECONNABORTED(status)) {
                return no_more_writes(conn);
            }
            if (status)
                return status;
        }

        if (read_status == SERF_ERROR_WAIT_CONN) {
            stop_reading = 1;
            conn->stop_writing = 1;
            conn->dirty_conn = 1;
            conn->ctx->dirty_pollset = 1;
        }
        else if (request && read_status && conn->hit_eof &&
                 conn->vec_len == 0) {
            /* If we hit the end of the request bucket and all of its data has
             * been written, then clear it out to signify that we're done
             * sending the request. On the next iteration through this loop:
             * - if there are remaining bytes they will be written, and as the 
             * request bucket will be completely read it will be destroyed then.
             * - we'll see if there are other requests that need to be sent 
             * ("pipelining").
             */
            conn->hit_eof = 0;
            serf_bucket_destroy(request->req_bkt);
            request->req_bkt = NULL;

            /* If our connection has async responses enabled, we're not
             * going to get a reply back, so kill the request.
             */
            if (conn->async_responses) {
                conn->requests = request->next;
                destroy_request(request);
            }

            conn->completed_requests++;

            if (conn->probable_keepalive_limit &&
                conn->completed_requests > conn->probable_keepalive_limit) {
                /* backoff for now. */
                stop_reading = 1;
            }
        }

        if (stop_reading) {
            return APR_SUCCESS;
        }
    }
    /* NOTREACHED */
}