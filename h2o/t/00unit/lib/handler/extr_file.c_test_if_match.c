#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_9__ ;
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_15__ ;
typedef  struct TYPE_17__   TYPE_14__ ;

/* Type definitions */
typedef  int ssize_t ;
struct TYPE_18__ {TYPE_2__* entries; } ;
struct TYPE_23__ {int status; TYPE_15__ headers; } ;
struct TYPE_22__ {void* path; void* method; } ;
struct TYPE_24__ {TYPE_5__ res; int /*<<< orphan*/  headers; int /*<<< orphan*/  pool; TYPE_4__ input; } ;
struct TYPE_26__ {TYPE_7__* body; TYPE_6__ req; } ;
typedef  TYPE_8__ h2o_loopback_conn_t ;
struct TYPE_27__ {int /*<<< orphan*/  base; int /*<<< orphan*/  len; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_9__ h2o_iovec_t ;
struct TYPE_25__ {scalar_t__ size; } ;
struct TYPE_21__ {int /*<<< orphan*/  hosts; } ;
struct TYPE_19__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;
struct TYPE_20__ {TYPE_1__ value; } ;
struct TYPE_17__ {TYPE_3__* globalconf; } ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_STRLIT (char*) ; 
 int /*<<< orphan*/  H2O_TOKEN_ETAG ; 
 int /*<<< orphan*/  H2O_TOKEN_IF_NONE_MATCH ; 
 TYPE_14__ ctx ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_add_header (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int h2o_find_header (TYPE_15__*,int /*<<< orphan*/ ,int) ; 
 void* h2o_iovec_init (int /*<<< orphan*/ ) ; 
 TYPE_8__* h2o_loopback_create (TYPE_14__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_loopback_destroy (TYPE_8__*) ; 
 int /*<<< orphan*/  h2o_loopback_run_loop (TYPE_8__*) ; 
 TYPE_9__ h2o_strdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int) ; 

__attribute__((used)) static void test_if_match(void)
{
    h2o_iovec_t etag = {NULL};

    { /* obtain etag */
        h2o_loopback_conn_t *conn = h2o_loopback_create(&ctx, ctx.globalconf->hosts);
        ssize_t etag_index;
        conn->req.input.method = h2o_iovec_init(H2O_STRLIT("GET"));
        conn->req.input.path = h2o_iovec_init(H2O_STRLIT("/"));
        h2o_loopback_run_loop(conn);
        ok(conn->req.res.status == 200);
        if ((etag_index = h2o_find_header(&conn->req.res.headers, H2O_TOKEN_ETAG, -1)) == -1) {
            ok(0);
            return;
        }
        etag = h2o_strdup(NULL, conn->req.res.headers.entries[etag_index].value.base,
                          conn->req.res.headers.entries[etag_index].value.len);
        h2o_loopback_destroy(conn);
    }

    { /* send if-non-match using the obtained etag */
        h2o_loopback_conn_t *conn = h2o_loopback_create(&ctx, ctx.globalconf->hosts);
        conn->req.input.method = h2o_iovec_init(H2O_STRLIT("GET"));
        conn->req.input.path = h2o_iovec_init(H2O_STRLIT("/"));
        h2o_add_header(&conn->req.pool, &conn->req.headers, H2O_TOKEN_IF_NONE_MATCH, NULL, etag.base, etag.len);
        h2o_loopback_run_loop(conn);
        ok(conn->req.res.status == 304);
        ok(conn->body->size == 0);
        h2o_loopback_destroy(conn);
    }

    free(etag.base);
}