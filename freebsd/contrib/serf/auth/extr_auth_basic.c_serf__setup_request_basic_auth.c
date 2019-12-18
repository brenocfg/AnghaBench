#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  serf_request_t ;
struct TYPE_10__ {TYPE_4__* baton; } ;
struct TYPE_8__ {TYPE_3__ proxy_authn_info; } ;
typedef  TYPE_1__ serf_context_t ;
struct TYPE_9__ {TYPE_1__* ctx; } ;
typedef  TYPE_2__ serf_connection_t ;
typedef  int /*<<< orphan*/  serf_bucket_t ;
typedef  TYPE_3__ serf__authn_info_t ;
typedef  scalar_t__ peer_t ;
struct TYPE_11__ {scalar_t__ value; scalar_t__ header; } ;
typedef  TYPE_4__ basic_authn_info_t ;
typedef  int /*<<< orphan*/  apr_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_SUCCESS ; 
 scalar_t__ HOST ; 
 int /*<<< orphan*/  SERF_ERROR_AUTHN_FAILED ; 
 TYPE_3__* serf__get_authn_info_for_server (TYPE_2__*) ; 
 int /*<<< orphan*/  serf_bucket_headers_setn (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 

apr_status_t
serf__setup_request_basic_auth(peer_t peer,
                               int code,
                               serf_connection_t *conn,
                               serf_request_t *request,
                               const char *method,
                               const char *uri,
                               serf_bucket_t *hdrs_bkt)
{
    serf_context_t *ctx = conn->ctx;
    serf__authn_info_t *authn_info;
    basic_authn_info_t *basic_info;

    if (peer == HOST) {
        authn_info = serf__get_authn_info_for_server(conn);
    } else {
        authn_info = &ctx->proxy_authn_info;
    }
    basic_info = authn_info->baton;

    if (basic_info && basic_info->header && basic_info->value) {
        serf_bucket_headers_setn(hdrs_bkt, basic_info->header,
                                 basic_info->value);
        return APR_SUCCESS;
    }

    return SERF_ERROR_AUTHN_FAILED;
}