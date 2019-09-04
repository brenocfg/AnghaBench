#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int status; char const* reason; int /*<<< orphan*/  headers; int /*<<< orphan*/  content_length; } ;
struct TYPE_11__ {TYPE_1__ res; int /*<<< orphan*/  pool; scalar_t__ http1_is_persistent; int /*<<< orphan*/ * pathconf; } ;
typedef  TYPE_2__ h2o_req_t ;
struct TYPE_12__ {int /*<<< orphan*/  fallback_path; } ;
typedef  TYPE_3__ h2o_hostconf_t ;

/* Variables and functions */
 int H2O_SEND_ERROR_HTTP1_CLOSE_CONNECTION ; 
 int H2O_SEND_ERROR_KEEP_HEADERS ; 
 int /*<<< orphan*/  H2O_STRLIT (char*) ; 
 int /*<<< orphan*/  H2O_TOKEN_CONTENT_TYPE ; 
 int /*<<< orphan*/  SIZE_MAX ; 
 int /*<<< orphan*/  h2o_add_header (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_req_bind_conf (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 TYPE_3__* h2o_req_setup (TYPE_2__*) ; 
 int /*<<< orphan*/  h2o_send_inline (TYPE_2__*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

void h2o_send_error_generic(h2o_req_t *req, int status, const char *reason, const char *body, int flags)
{
    if (req->pathconf == NULL) {
        h2o_hostconf_t *hostconf = h2o_req_setup(req);
        h2o_req_bind_conf(req, hostconf, &hostconf->fallback_path);
    }

    if ((flags & H2O_SEND_ERROR_HTTP1_CLOSE_CONNECTION) != 0)
        req->http1_is_persistent = 0;

    req->res.status = status;
    req->res.reason = reason;
    req->res.content_length = strlen(body);

    if ((flags & H2O_SEND_ERROR_KEEP_HEADERS) == 0)
        memset(&req->res.headers, 0, sizeof(req->res.headers));

    h2o_add_header(&req->pool, &req->res.headers, H2O_TOKEN_CONTENT_TYPE, NULL, H2O_STRLIT("text/plain; charset=utf-8"));

    h2o_send_inline(req, body, SIZE_MAX);
}