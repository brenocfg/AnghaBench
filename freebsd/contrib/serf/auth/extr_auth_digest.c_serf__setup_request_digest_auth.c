#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {void* auth_baton; } ;
typedef  TYPE_1__ serf_request_t ;
struct TYPE_16__ {TYPE_5__* baton; } ;
struct TYPE_14__ {TYPE_4__ proxy_authn_info; } ;
typedef  TYPE_2__ serf_context_t ;
struct TYPE_15__ {int /*<<< orphan*/  pool; TYPE_2__* ctx; } ;
typedef  TYPE_3__ serf_connection_t ;
typedef  int /*<<< orphan*/  serf_bucket_t ;
typedef  TYPE_4__ serf__authn_info_t ;
typedef  scalar_t__ peer_t ;
struct TYPE_17__ {char* header; int /*<<< orphan*/  digest_nc; scalar_t__ realm; } ;
typedef  TYPE_5__ digest_authn_info_t ;
struct TYPE_18__ {char* path; } ;
typedef  TYPE_6__ apr_uri_t ;
typedef  int /*<<< orphan*/  apr_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_SUCCESS ; 
 scalar_t__ HOST ; 
 int /*<<< orphan*/  apr_uri_parse (int /*<<< orphan*/ ,char const*,TYPE_6__*) ; 
 int /*<<< orphan*/  build_auth_header (char const**,TYPE_5__*,char const*,char const*,int /*<<< orphan*/ ) ; 
 TYPE_4__* serf__get_authn_info_for_server (TYPE_3__*) ; 
 int /*<<< orphan*/  serf_bucket_headers_setn (int /*<<< orphan*/ *,char*,char const*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

apr_status_t
serf__setup_request_digest_auth(peer_t peer,
                                int code,
                                serf_connection_t *conn,
                                serf_request_t *request,
                                const char *method,
                                const char *uri,
                                serf_bucket_t *hdrs_bkt)
{
    serf_context_t *ctx = conn->ctx;
    serf__authn_info_t *authn_info;
    digest_authn_info_t *digest_info;
    apr_status_t status;

    if (peer == HOST) {
        authn_info = serf__get_authn_info_for_server(conn);
    } else {
        authn_info = &ctx->proxy_authn_info;
    }
    digest_info = authn_info->baton;

    if (digest_info && digest_info->realm) {
        const char *value;
        const char *path;

        /* TODO: per request pool? */

        /* for request 'CONNECT serf.googlecode.com:443', the uri also should be
           serf.googlecode.com:443. apr_uri_parse can't handle this, so special
           case. */
        if (strcmp(method, "CONNECT") == 0)
            path = uri;
        else {
            apr_uri_t parsed_uri;

            /* Extract path from uri. */
            status = apr_uri_parse(conn->pool, uri, &parsed_uri);
            if (status)
                return status;

            path = parsed_uri.path;
        }

        /* Build a new Authorization header. */
        digest_info->header = (peer == HOST) ? "Authorization" :
            "Proxy-Authorization";
        status = build_auth_header(&value, digest_info, path, method,
                                   conn->pool);
        if (status)
            return status;

        serf_bucket_headers_setn(hdrs_bkt, digest_info->header,
                                 value);
        digest_info->digest_nc++;

        /* Store the uri of this request on the serf_request_t object, to make
           it available when validating the Authentication-Info header of the
           matching response. */
        request->auth_baton = (void *)path;
    }

    return APR_SUCCESS;
}