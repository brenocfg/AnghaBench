#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  writing_started; struct TYPE_14__* next; int /*<<< orphan*/ * resp_bkt; int /*<<< orphan*/  acceptor_baton; int /*<<< orphan*/ * (* acceptor ) (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;scalar_t__ req_bkt; } ;
typedef  TYPE_2__ serf_request_t ;
struct TYPE_15__ {int dirty_conn; scalar_t__ completed_responses; scalar_t__ probable_keepalive_limit; TYPE_1__* ctx; int /*<<< orphan*/ * requests_tail; TYPE_2__* requests; int /*<<< orphan*/  stream; scalar_t__ async_responses; int /*<<< orphan*/  pool; scalar_t__ stop_writing; } ;
typedef  TYPE_3__ serf_connection_t ;
typedef  int /*<<< orphan*/  serf_bucket_t ;
typedef  int /*<<< orphan*/  apr_status_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_13__ {int dirty_pollset; } ;

/* Variables and functions */
 scalar_t__ APR_STATUS_IS_EAGAIN (int /*<<< orphan*/ ) ; 
 scalar_t__ APR_STATUS_IS_ECONNABORTED (int /*<<< orphan*/ ) ; 
 scalar_t__ APR_STATUS_IS_ECONNRESET (int /*<<< orphan*/ ) ; 
 scalar_t__ APR_STATUS_IS_EOF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  APR_SUCCESS ; 
 int FALSE ; 
 int /*<<< orphan*/  SERF_ERROR_ABORTED_CONNECTION ; 
 int SERF_ERROR_CLOSING ; 
 int /*<<< orphan*/  SERF_ERROR_REQUEST_LOST ; 
 int /*<<< orphan*/  apr_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_pool_create (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_request (TYPE_2__*) ; 
 int /*<<< orphan*/  handle_async_response (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  handle_response (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int is_conn_closing (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepare_conn_streams (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 scalar_t__ request_or_data_pending (TYPE_2__**,TYPE_3__*) ; 
 int /*<<< orphan*/  reset_connection (TYPE_3__*,int) ; 
 int /*<<< orphan*/  serf_bucket_peek (int /*<<< orphan*/ ,char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub1 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static apr_status_t read_from_connection(serf_connection_t *conn)
{
    apr_status_t status;
    apr_pool_t *tmppool;
    int close_connection = FALSE;

    /* Whatever is coming in on the socket corresponds to the first request
     * on our chain.
     */
    serf_request_t *request = conn->requests;

    /* If the stop_writing flag was set on the connection, reset it now because
       there is some data to read. */
    if (conn->stop_writing) {
        conn->stop_writing = 0;
        conn->dirty_conn = 1;
        conn->ctx->dirty_pollset = 1;
    }

    /* assert: request != NULL */

    if ((status = apr_pool_create(&tmppool, conn->pool)) != APR_SUCCESS)
        goto error;

    /* Invoke response handlers until we have no more work. */
    while (1) {
        serf_bucket_t *dummy1, *dummy2;

        apr_pool_clear(tmppool);

        /* Only interested in the input stream here. */
        status = prepare_conn_streams(conn, &conn->stream, &dummy1, &dummy2);
        if (status) {
            goto error;
        }

        /* We have a different codepath when we can have async responses. */
        if (conn->async_responses) {
            /* TODO What about socket errors? */
            status = handle_async_response(conn, tmppool);
            if (APR_STATUS_IS_EAGAIN(status)) {
                status = APR_SUCCESS;
                goto error;
            }
            if (status) {
                goto error;
            }
            continue;
        }

        /* We are reading a response for a request we haven't
         * written yet!
         *
         * This shouldn't normally happen EXCEPT:
         *
         * 1) when the other end has closed the socket and we're
         *    pending an EOF return.
         * 2) Doing the initial SSL handshake - we'll get EAGAIN
         *    as the SSL buckets will hide the handshake from us
         *    but not return any data.
         * 3) When the server sends us an SSL alert.
         *
         * In these cases, we should not receive any actual user data.
         *
         * 4) When the server sends a error response, like 408 Request timeout.
         *    This response should be passed to the application.
         *
         * If we see an EOF (due to either an expired timeout or the server
         * sending the SSL 'close notify' shutdown alert), we'll reset the
         * connection and open a new one.
         */
        if (request->req_bkt || !request->writing_started) {
            const char *data;
            apr_size_t len;

            status = serf_bucket_peek(conn->stream, &data, &len);

            if (APR_STATUS_IS_EOF(status)) {
                reset_connection(conn, 1);
                status = APR_SUCCESS;
                goto error;
            }
            else if (APR_STATUS_IS_EAGAIN(status) && !len) {
                status = APR_SUCCESS;
                goto error;
            } else if (status && !APR_STATUS_IS_EAGAIN(status)) {
                /* Read error */
                goto error;
            }

            /* Unexpected response from the server */

        }

        /* If the request doesn't have a response bucket, then call the
         * acceptor to get one created.
         */
        if (request->resp_bkt == NULL) {
            request->resp_bkt = (*request->acceptor)(request, conn->stream,
                                                     request->acceptor_baton,
                                                     tmppool);
            apr_pool_clear(tmppool);
        }

        status = handle_response(request, tmppool);

        /* Some systems will not generate a HUP poll event so we have to
         * handle the ECONNRESET issue and ECONNABORT here.
         */
        if (APR_STATUS_IS_ECONNRESET(status) ||
            APR_STATUS_IS_ECONNABORTED(status) ||
            status == SERF_ERROR_REQUEST_LOST) {
            /* If the connection had ever been good, be optimistic & try again.
             * If it has never tried again (incl. a retry), fail.
             */
            if (conn->completed_responses) {
                reset_connection(conn, 1);
                status = APR_SUCCESS;
            }
            else if (status == SERF_ERROR_REQUEST_LOST) {
                status = SERF_ERROR_ABORTED_CONNECTION;
            }
            goto error;
        }

        /* If our response handler says it can't do anything more, we now
         * treat that as a success.
         */
        if (APR_STATUS_IS_EAGAIN(status)) {
            /* It is possible that while reading the response, the ssl layer
               has prepared some data to send. If this was the last request,
               serf will not check for socket writability, so force this here.
             */
            if (request_or_data_pending(&request, conn) && !request) {
                conn->dirty_conn = 1;
                conn->ctx->dirty_pollset = 1;
            }
            status = APR_SUCCESS;
            goto error;
        }

        /* If we received APR_SUCCESS, run this loop again. */
        if (!status) {
            continue;
        }

        close_connection = is_conn_closing(request->resp_bkt);

        if (!APR_STATUS_IS_EOF(status) &&
            close_connection != SERF_ERROR_CLOSING) {
            /* Whether success, or an error, there is no more to do unless
             * this request has been completed.
             */
            goto error;
        }

        /* The response has been fully-read, so that means the request has
         * either been fully-delivered (most likely), or that we don't need to
         * write the rest of it anymore, e.g. when a 408 Request timeout was
         $ received.
         * Remove it from our queue and loop to read another response.
         */
        conn->requests = request->next;

        destroy_request(request);

        request = conn->requests;

        /* If we're truly empty, update our tail. */
        if (request == NULL) {
            conn->requests_tail = NULL;
        }

        conn->completed_responses++;

        /* We've to rebuild pollset since completed_responses is changed. */
        conn->dirty_conn = 1;
        conn->ctx->dirty_pollset = 1;

        /* This means that we're being advised that the connection is done. */
        if (close_connection == SERF_ERROR_CLOSING) {
            reset_connection(conn, 1);
            if (APR_STATUS_IS_EOF(status))
                status = APR_SUCCESS;
            goto error;
        }

        /* The server is suddenly deciding to serve more responses than we've
         * seen before.
         *
         * Let our requests go.
         */
        if (conn->probable_keepalive_limit &&
            conn->completed_responses > conn->probable_keepalive_limit) {
            conn->probable_keepalive_limit = 0;
        }

        /* If we just ran out of requests or have unwritten requests, then
         * update the pollset. We don't want to read from this socket any
         * more. We are definitely done with this loop, too.
         */
        if (request == NULL || !request->writing_started) {
            conn->dirty_conn = 1;
            conn->ctx->dirty_pollset = 1;
            status = APR_SUCCESS;
            goto error;
        }
    }

error:
    apr_pool_destroy(tmppool);
    return status;
}