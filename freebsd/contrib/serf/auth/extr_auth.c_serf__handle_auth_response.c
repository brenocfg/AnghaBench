#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int code; int /*<<< orphan*/  version; } ;
typedef  TYPE_1__ serf_status_line ;
struct TYPE_17__ {TYPE_4__* conn; int /*<<< orphan*/  setup_baton; int /*<<< orphan*/  setup; scalar_t__ ssltunnel; } ;
typedef  TYPE_2__ serf_request_t ;
struct TYPE_21__ {TYPE_5__* scheme; } ;
struct TYPE_18__ {TYPE_8__ proxy_authn_info; } ;
typedef  TYPE_3__ serf_context_t ;
struct TYPE_19__ {TYPE_3__* ctx; } ;
typedef  TYPE_4__ serf_connection_t ;
typedef  int /*<<< orphan*/  serf_bucket_t ;
typedef  scalar_t__ (* serf__validate_response_func_t ) (TYPE_5__*,int /*<<< orphan*/ ,int,TYPE_4__*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;
typedef  TYPE_8__ serf__authn_info_t ;
typedef  scalar_t__ apr_status_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_20__ {scalar_t__ (* validate_response_func ) (TYPE_5__*,int /*<<< orphan*/ ,int,TYPE_4__*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 scalar_t__ APR_EOF ; 
 scalar_t__ APR_STATUS_IS_EAGAIN (scalar_t__) ; 
 scalar_t__ APR_STATUS_IS_EOF (scalar_t__) ; 
 scalar_t__ APR_SUCCESS ; 
 int /*<<< orphan*/  HOST ; 
 int /*<<< orphan*/  PROXY ; 
 scalar_t__ SERF_BUCKET_READ_ERROR (scalar_t__) ; 
 scalar_t__ discard_body (int /*<<< orphan*/ *) ; 
 scalar_t__ dispatch_auth (int,TYPE_2__*,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *) ; 
 TYPE_8__* serf__get_authn_info_for_server (TYPE_4__*) ; 
 int /*<<< orphan*/  serf__ssltunnel_request_create (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ serf_bucket_response_status (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ serf_bucket_response_wait_for_headers (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serf_connection_priority_request_create (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

apr_status_t serf__handle_auth_response(int *consumed_response,
                                        serf_request_t *request,
                                        serf_bucket_t *response,
                                        void *baton,
                                        apr_pool_t *pool)
{
    apr_status_t status;
    serf_status_line sl;

    *consumed_response = 0;

    /* TODO: the response bucket was created by the application, not at all
       guaranteed that this is of type response_bucket!! */
    status = serf_bucket_response_status(response, &sl);
    if (SERF_BUCKET_READ_ERROR(status)) {
        return status;
    }
    if (!sl.version && (APR_STATUS_IS_EOF(status) ||
                        APR_STATUS_IS_EAGAIN(status))) {
        return status;
    }

    status = serf_bucket_response_wait_for_headers(response);
    if (status) {
        if (!APR_STATUS_IS_EOF(status)) {
            return status;
        }

        /* If status is APR_EOF, there were no headers to read.
           This can be ok in some situations, and it definitely
           means there's no authentication requested now. */
        return APR_SUCCESS;
    }

    if (sl.code == 401 || sl.code == 407) {
        /* Authentication requested. */

        /* Don't bother handling the authentication request if the response
           wasn't received completely yet. Serf will call serf__handle_auth_response
           again when more data is received. */
        status = discard_body(response);
        *consumed_response = 1;
        
        /* Discard all response body before processing authentication. */
        if (!APR_STATUS_IS_EOF(status)) {
            return status;
        }

        status = dispatch_auth(sl.code, request, response, baton, pool);
        if (status != APR_SUCCESS) {
            return status;
        }

        /* Requeue the request with the necessary auth headers. */
        /* ### Application doesn't know about this request! */
        if (request->ssltunnel) {
            serf__ssltunnel_request_create(request->conn,
                                           request->setup,
                                           request->setup_baton);
        } else {
            serf_connection_priority_request_create(request->conn,
                                                    request->setup,
                                                    request->setup_baton);
        }

        return APR_EOF;
    } else {
        serf__validate_response_func_t validate_resp;
        serf_connection_t *conn = request->conn;
        serf_context_t *ctx = conn->ctx;
        serf__authn_info_t *authn_info;
        apr_status_t resp_status = APR_SUCCESS;


        /* Validate the response server authn headers. */
        authn_info = serf__get_authn_info_for_server(conn);
        if (authn_info->scheme) {
            validate_resp = authn_info->scheme->validate_response_func;
            resp_status = validate_resp(authn_info->scheme, HOST, sl.code,
                                        conn, request, response, pool);
        }

        /* Validate the response proxy authn headers. */
        authn_info = &ctx->proxy_authn_info;
        if (!resp_status && authn_info->scheme) {
            validate_resp = authn_info->scheme->validate_response_func;
            resp_status = validate_resp(authn_info->scheme, PROXY, sl.code,
                                        conn, request, response, pool);
        }

        if (resp_status) {
            /* If there was an error in the final step of the authentication,
               consider the reponse body as invalid and discard it. */
            status = discard_body(response);
            *consumed_response = 1;
            if (!APR_STATUS_IS_EOF(status)) {
                return status;
            }
            /* The whole body was discarded, now return our error. */
            return resp_status;
        }
    }

    return APR_SUCCESS;
}