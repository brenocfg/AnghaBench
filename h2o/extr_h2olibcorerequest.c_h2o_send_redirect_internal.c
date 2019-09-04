#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  len; int /*<<< orphan*/ * base; } ;
struct TYPE_13__ {int /*<<< orphan*/  path; TYPE_6__ authority; int /*<<< orphan*/ * scheme; } ;
typedef  TYPE_3__ h2o_url_t ;
struct TYPE_14__ {int /*<<< orphan*/ * overrides; int /*<<< orphan*/  pool; int /*<<< orphan*/  path; TYPE_6__ authority; TYPE_2__* hostconf; int /*<<< orphan*/ * scheme; } ;
typedef  TYPE_4__ h2o_req_t ;
typedef  int /*<<< orphan*/  h2o_iovec_t ;
struct TYPE_11__ {TYPE_6__ hostport; } ;
struct TYPE_12__ {TYPE_1__ authority; } ;

/* Variables and functions */
 int /*<<< orphan*/  h2o_concat (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ h2o_lcstris (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_reprocess_request_deferred (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_6__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  h2o_send_error_deferred_502 (TYPE_4__*,char*,char*,int /*<<< orphan*/ ) ; 
 TYPE_6__ h2o_strdup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ h2o_url_parse_relative (char const*,size_t,TYPE_3__*) ; 
 int /*<<< orphan*/  h2o_url_resolve_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void h2o_send_redirect_internal(h2o_req_t *req, h2o_iovec_t method, const char *url_str, size_t url_len, int preserve_overrides)
{
    h2o_url_t url;

    /* parse the location URL */
    if (h2o_url_parse_relative(url_str, url_len, &url) != 0) {
        /* TODO log h2o_error_printf("[proxy] cannot handle location header: %.*s\n", (int)url_len, url); */
        h2o_send_error_deferred_502(req, "Gateway Error", "internal error", 0);
        return;
    }
    /* convert the location to absolute (while creating copies of the values passed to the deferred call) */
    if (url.scheme == NULL)
        url.scheme = req->scheme;
    if (url.authority.base == NULL) {
        if (req->hostconf != NULL)
            url.authority = req->hostconf->authority.hostport;
        else
            url.authority = req->authority;
    } else {
        if (h2o_lcstris(url.authority.base, url.authority.len, req->authority.base, req->authority.len)) {
            url.authority = req->authority;
        } else {
            url.authority = h2o_strdup(&req->pool, url.authority.base, url.authority.len);
            preserve_overrides = 0;
        }
    }
    h2o_iovec_t base_path = req->path;
    h2o_url_resolve_path(&base_path, &url.path);
    url.path = h2o_concat(&req->pool, base_path, url.path);

    h2o_reprocess_request_deferred(req, method, url.scheme, url.authority, url.path, preserve_overrides ? req->overrides : NULL, 1);
}