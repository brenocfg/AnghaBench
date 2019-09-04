#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_12__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;
struct TYPE_13__ {int /*<<< orphan*/ * base; } ;
struct TYPE_18__ {int /*<<< orphan*/  query_at; TYPE_4__ path; TYPE_12__ authority; int /*<<< orphan*/  method; TYPE_3__* scheme; } ;
struct TYPE_19__ {int /*<<< orphan*/  query_at; TYPE_5__ input; int /*<<< orphan*/  norm_indexes; int /*<<< orphan*/  pool; int /*<<< orphan*/  path_normalized; TYPE_4__ path; TYPE_12__ authority; int /*<<< orphan*/  method; TYPE_3__* scheme; TYPE_1__* conn; int /*<<< orphan*/  processed_at; } ;
typedef  TYPE_6__ h2o_req_t ;
struct TYPE_15__ {TYPE_12__ hostport; } ;
struct TYPE_20__ {TYPE_2__ authority; } ;
typedef  TYPE_7__ h2o_hostconf_t ;
typedef  int /*<<< orphan*/  h2o_context_t ;
struct TYPE_16__ {int /*<<< orphan*/  default_port; } ;
struct TYPE_14__ {TYPE_7__** hosts; int /*<<< orphan*/ * ctx; } ;

/* Variables and functions */
 TYPE_7__* find_hostconf (TYPE_7__**,TYPE_12__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_get_timestamp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_url_normalize_path (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

h2o_hostconf_t *h2o_req_setup(h2o_req_t *req)
{
    h2o_context_t *ctx = req->conn->ctx;
    h2o_hostconf_t *hostconf;

    req->processed_at = h2o_get_timestamp(ctx, &req->pool);

    /* find the host context */
    if (req->input.authority.base != NULL) {
        if (req->conn->hosts[1] == NULL ||
            (hostconf = find_hostconf(req->conn->hosts, req->input.authority, req->input.scheme->default_port)) == NULL)
            hostconf = *req->conn->hosts;
    } else {
        /* set the authority name to the default one */
        hostconf = *req->conn->hosts;
        req->input.authority = hostconf->authority.hostport;
    }

    req->scheme = req->input.scheme;
    req->method = req->input.method;
    req->authority = req->input.authority;
    req->path = req->input.path;
    req->path_normalized =
        h2o_url_normalize_path(&req->pool, req->input.path.base, req->input.path.len, &req->query_at, &req->norm_indexes);
    req->input.query_at = req->query_at; /* we can do this since input.path == path */

    return hostconf;
}