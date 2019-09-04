#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_16__ ;
typedef  struct TYPE_18__   TYPE_14__ ;
typedef  struct TYPE_17__   TYPE_13__ ;

/* Type definitions */
typedef  int ssize_t ;
struct TYPE_18__ {TYPE_2__* entries; } ;
struct TYPE_19__ {int status; TYPE_14__ headers; } ;
struct TYPE_23__ {void* path; void* method; } ;
struct TYPE_24__ {TYPE_16__ res; int /*<<< orphan*/  headers; int /*<<< orphan*/  pool; TYPE_4__ input; } ;
struct TYPE_26__ {TYPE_6__* body; TYPE_5__ req; } ;
typedef  TYPE_7__ h2o_loopback_conn_t ;
struct TYPE_27__ {char* base; int len; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_8__ h2o_iovec_t ;
struct TYPE_25__ {size_t size; int /*<<< orphan*/  bytes; } ;
struct TYPE_22__ {int /*<<< orphan*/  hosts; } ;
struct TYPE_20__ {char* base; int len; } ;
struct TYPE_21__ {TYPE_1__ value; } ;
struct TYPE_17__ {TYPE_3__* globalconf; } ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_STRLIT (char*) ; 
 int H2O_TIMESTR_RFC1123_LEN ; 
 int /*<<< orphan*/  H2O_TOKEN_CONTENT_RANGE ; 
 int /*<<< orphan*/  H2O_TOKEN_CONTENT_TYPE ; 
 int /*<<< orphan*/  H2O_TOKEN_ETAG ; 
 int /*<<< orphan*/  H2O_TOKEN_IF_RANGE ; 
 int /*<<< orphan*/  H2O_TOKEN_LAST_MODIFIED ; 
 int /*<<< orphan*/  H2O_TOKEN_RANGE ; 
 int check_header (TYPE_16__*,int /*<<< orphan*/ ,char*) ; 
 TYPE_13__ ctx ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  h2o_add_header (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,...) ; 
 int h2o_find_header (TYPE_14__*,int /*<<< orphan*/ ,int) ; 
 void* h2o_iovec_init (int /*<<< orphan*/ ) ; 
 TYPE_7__* h2o_loopback_create (TYPE_13__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_loopback_destroy (TYPE_7__*) ; 
 int /*<<< orphan*/  h2o_loopback_run_loop (TYPE_7__*) ; 
 TYPE_8__ h2o_strdup (int /*<<< orphan*/ *,char*,int) ; 
 char* malloc (int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  ok (int) ; 

__attribute__((used)) static void test_if_range(void)
{
    h2o_iovec_t etag = {NULL}, weak_etag = {NULL};
    char lm_date[H2O_TIMESTR_RFC1123_LEN + 1];
    size_t body_size;

    { /* obtain etag */
        h2o_loopback_conn_t *conn = h2o_loopback_create(&ctx, ctx.globalconf->hosts);
        ssize_t etag_index;
        conn->req.input.method = h2o_iovec_init(H2O_STRLIT("GET"));
        conn->req.input.path = h2o_iovec_init(H2O_STRLIT("/1000.txt"));
        h2o_loopback_run_loop(conn);
        ok(conn->req.res.status == 200);
        if ((etag_index = h2o_find_header(&conn->req.res.headers, H2O_TOKEN_ETAG, -1)) == -1) {
            ok(0);
            return;
        }
        etag = h2o_strdup(NULL, conn->req.res.headers.entries[etag_index].value.base,
                          conn->req.res.headers.entries[etag_index].value.len);
        weak_etag.base = malloc(etag.len + 2);
        weak_etag.len = etag.len + 2;
        weak_etag.base[0] = 'W';
        weak_etag.base[1] = '/';
        memcpy(weak_etag.base + 2, etag.base, etag.len);
        body_size = conn->body->size;
        h2o_loopback_destroy(conn);
    }

    { /* obtain last-modified */
        h2o_loopback_conn_t *conn = h2o_loopback_create(&ctx, ctx.globalconf->hosts);
        ssize_t lm_index;
        conn->req.input.method = h2o_iovec_init(H2O_STRLIT("GET"));
        conn->req.input.path = h2o_iovec_init(H2O_STRLIT("/1000.txt"));
        h2o_loopback_run_loop(conn);
        ok(conn->req.res.status == 200);
        ok(conn->body->size == body_size);
        if ((lm_index = h2o_find_header(&conn->req.res.headers, H2O_TOKEN_LAST_MODIFIED, -1)) == -1) {
            ok(0);
            return;
        }
        ok(conn->req.res.headers.entries[lm_index].value.len == H2O_TIMESTR_RFC1123_LEN);
        memcpy(lm_date, conn->req.res.headers.entries[lm_index].value.base, H2O_TIMESTR_RFC1123_LEN);
        lm_date[H2O_TIMESTR_RFC1123_LEN] = '\0';
        h2o_loopback_destroy(conn);
    }

    { /* send if-range with no range */
        h2o_loopback_conn_t *conn = h2o_loopback_create(&ctx, ctx.globalconf->hosts);
        conn->req.input.method = h2o_iovec_init(H2O_STRLIT("GET"));
        conn->req.input.path = h2o_iovec_init(H2O_STRLIT("/1000.txt"));
        h2o_add_header(&conn->req.pool, &conn->req.headers, H2O_TOKEN_IF_RANGE, NULL, etag.base, etag.len);
        h2o_loopback_run_loop(conn);
        ok(conn->req.res.status == 200);
        ok(conn->body->size == body_size);
        h2o_loopback_destroy(conn);
    }

    { /* send obtained etag as if-range with range */
        h2o_loopback_conn_t *conn = h2o_loopback_create(&ctx, ctx.globalconf->hosts);
        conn->req.input.method = h2o_iovec_init(H2O_STRLIT("GET"));
        conn->req.input.path = h2o_iovec_init(H2O_STRLIT("/1000.txt"));
        h2o_add_header(&conn->req.pool, &conn->req.headers, H2O_TOKEN_IF_RANGE, NULL, etag.base, etag.len);
        h2o_add_header(&conn->req.pool, &conn->req.headers, H2O_TOKEN_RANGE, NULL, H2O_STRLIT("bytes=0-10"));
        h2o_loopback_run_loop(conn);
        ok(conn->req.res.status == 206);
        ok(check_header(&conn->req.res, H2O_TOKEN_CONTENT_TYPE, "text/plain"));
        ok(check_header(&conn->req.res, H2O_TOKEN_CONTENT_RANGE, "bytes 0-10/1000"));
        ok(conn->body->size == 11);
        ok(memcmp(conn->body->bytes, "123456789\n1", 11) == 0);
        h2o_loopback_destroy(conn);
    }

    { /* send obtained last-modified as if-range with range */
        h2o_loopback_conn_t *conn = h2o_loopback_create(&ctx, ctx.globalconf->hosts);
        conn->req.input.method = h2o_iovec_init(H2O_STRLIT("GET"));
        conn->req.input.path = h2o_iovec_init(H2O_STRLIT("/1000.txt"));
        h2o_add_header(&conn->req.pool, &conn->req.headers, H2O_TOKEN_IF_RANGE, NULL, lm_date, H2O_TIMESTR_RFC1123_LEN);
        h2o_add_header(&conn->req.pool, &conn->req.headers, H2O_TOKEN_RANGE, NULL, H2O_STRLIT("bytes=0-10"));
        h2o_loopback_run_loop(conn);
        ok(conn->req.res.status == 206);
        ok(check_header(&conn->req.res, H2O_TOKEN_CONTENT_TYPE, "text/plain"));
        ok(check_header(&conn->req.res, H2O_TOKEN_CONTENT_RANGE, "bytes 0-10/1000"));
        ok(conn->body->size == 11);
        ok(memcmp(conn->body->bytes, "123456789\n1", 11) == 0);
        h2o_loopback_destroy(conn);
    }

    { /* send weak etag as if-range with range */
        h2o_loopback_conn_t *conn = h2o_loopback_create(&ctx, ctx.globalconf->hosts);
        conn->req.input.method = h2o_iovec_init(H2O_STRLIT("GET"));
        conn->req.input.path = h2o_iovec_init(H2O_STRLIT("/1000.txt"));
        h2o_add_header(&conn->req.pool, &conn->req.headers, H2O_TOKEN_IF_RANGE, NULL, weak_etag.base, weak_etag.len);
        h2o_add_header(&conn->req.pool, &conn->req.headers, H2O_TOKEN_RANGE, NULL, H2O_STRLIT("bytes=0-10"));
        h2o_loopback_run_loop(conn);
        ok(conn->req.res.status == 200);
        ok(check_header(&conn->req.res, H2O_TOKEN_CONTENT_TYPE, "text/plain"));
        ok(conn->body->size == body_size);
        h2o_loopback_destroy(conn);
    }

    { /* send different etag as if-range with range */
        h2o_loopback_conn_t *conn = h2o_loopback_create(&ctx, ctx.globalconf->hosts);
        conn->req.input.method = h2o_iovec_init(H2O_STRLIT("GET"));
        conn->req.input.path = h2o_iovec_init(H2O_STRLIT("/1000.txt"));
        etag.base[1] = 'z';
        h2o_add_header(&conn->req.pool, &conn->req.headers, H2O_TOKEN_IF_RANGE, NULL, etag.base, etag.len);
        h2o_add_header(&conn->req.pool, &conn->req.headers, H2O_TOKEN_RANGE, NULL, H2O_STRLIT("bytes=0-10"));
        h2o_loopback_run_loop(conn);
        ok(conn->req.res.status == 200);
        ok(check_header(&conn->req.res, H2O_TOKEN_CONTENT_TYPE, "text/plain"));
        ok(conn->body->size == body_size);
        h2o_loopback_destroy(conn);
    }

    { /* send if-range using an old date */
        h2o_loopback_conn_t *conn = h2o_loopback_create(&ctx, ctx.globalconf->hosts);
        conn->req.input.method = h2o_iovec_init(H2O_STRLIT("GET"));
        conn->req.input.path = h2o_iovec_init(H2O_STRLIT("/1000.txt"));
        h2o_add_header(&conn->req.pool, &conn->req.headers, H2O_TOKEN_IF_RANGE, NULL, H2O_STRLIT("Sun, 06 Nov 1994 08:49:37 GMT"));
        h2o_add_header(&conn->req.pool, &conn->req.headers, H2O_TOKEN_RANGE, NULL, H2O_STRLIT("bytes=0-10"));
        h2o_loopback_run_loop(conn);
        ok(conn->req.res.status == 200);
        ok(check_header(&conn->req.res, H2O_TOKEN_CONTENT_TYPE, "text/plain"));
        ok(conn->body->size == body_size);
        h2o_loopback_destroy(conn);
    }

    { /* send if-range using a date in the future */
        h2o_loopback_conn_t *conn = h2o_loopback_create(&ctx, ctx.globalconf->hosts);
        conn->req.input.method = h2o_iovec_init(H2O_STRLIT("GET"));
        conn->req.input.path = h2o_iovec_init(H2O_STRLIT("/1000.txt"));
        h2o_add_header(&conn->req.pool, &conn->req.headers, H2O_TOKEN_IF_RANGE, NULL, H2O_STRLIT("Wed, 18 May 2033 12:33:20 GMT"));
        h2o_add_header(&conn->req.pool, &conn->req.headers, H2O_TOKEN_RANGE, NULL, H2O_STRLIT("bytes=0-10"));
        h2o_loopback_run_loop(conn);
        ok(conn->req.res.status == 206);
        ok(check_header(&conn->req.res, H2O_TOKEN_CONTENT_TYPE, "text/plain"));
        ok(check_header(&conn->req.res, H2O_TOKEN_CONTENT_RANGE, "bytes 0-10/1000"));
        ok(conn->body->size == 11);
        ok(memcmp(conn->body->bytes, "123456789\n1", 11) == 0);
        h2o_loopback_destroy(conn);
    }

    free(etag.base);
    free(weak_etag.base);
}