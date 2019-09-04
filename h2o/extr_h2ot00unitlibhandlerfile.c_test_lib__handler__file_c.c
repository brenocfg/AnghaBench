#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_13__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  h2o_pathconf_t ;
struct TYPE_14__ {int status; } ;
struct TYPE_17__ {void* path; void* method; } ;
struct TYPE_18__ {TYPE_13__ res; TYPE_3__ input; } ;
struct TYPE_19__ {TYPE_4__ req; TYPE_1__* body; } ;
typedef  TYPE_5__ h2o_loopback_conn_t ;
typedef  int /*<<< orphan*/  h2o_hostconf_t ;
typedef  int /*<<< orphan*/  h2o_globalconf_t ;
struct TYPE_20__ {TYPE_2__* globalconf; } ;
struct TYPE_16__ {int /*<<< orphan*/  hosts; } ;
struct TYPE_15__ {scalar_t__ size; int /*<<< orphan*/  bytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_STRLIT (char*) ; 
 int /*<<< orphan*/  H2O_TOKEN_CONTENT_TYPE ; 
 int /*<<< orphan*/  H2O_TOKEN_LOCATION ; 
 int check_header (TYPE_13__*,int /*<<< orphan*/ ,char*) ; 
 TYPE_9__ ctx ; 
 int /*<<< orphan*/  h2o_config_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_config_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * h2o_config_register_host (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/ * h2o_config_register_path (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_context_dispose (TYPE_9__*) ; 
 int /*<<< orphan*/  h2o_context_init (TYPE_9__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_file_register (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* h2o_iovec_init (int /*<<< orphan*/ ) ; 
 TYPE_5__* h2o_loopback_create (TYPE_9__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_loopback_destroy (TYPE_5__*) ; 
 int /*<<< orphan*/  h2o_loopback_run_loop (TYPE_5__*) ; 
 int h2o_memis (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int) ; 
 int /*<<< orphan*/  sha1sum (int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  subtest (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_if_match ; 
 int /*<<< orphan*/  test_if_modified_since ; 
 int /*<<< orphan*/  test_if_range ; 
 int /*<<< orphan*/  test_loop ; 
 int /*<<< orphan*/  test_process_range ; 
 int /*<<< orphan*/  test_range_req ; 
 int /*<<< orphan*/  test_strong_etag_cmp ; 

void test_lib__handler__file_c()
{
    h2o_globalconf_t globalconf;
    h2o_hostconf_t *hostconf;
    h2o_pathconf_t *pathconf;

    h2o_config_init(&globalconf);
    hostconf = h2o_config_register_host(&globalconf, h2o_iovec_init(H2O_STRLIT("default")), 65535);
    pathconf = h2o_config_register_path(hostconf, "/", 0);
    h2o_file_register(pathconf, "t/00unit/assets", NULL, NULL, 0);

    h2o_context_init(&ctx, test_loop, &globalconf);

    {
        h2o_loopback_conn_t *conn = h2o_loopback_create(&ctx, ctx.globalconf->hosts);
        conn->req.input.method = h2o_iovec_init(H2O_STRLIT("HEAD"));
        conn->req.input.path = h2o_iovec_init(H2O_STRLIT("/"));
        h2o_loopback_run_loop(conn);
        ok(conn->req.res.status == 200);
        ok(check_header(&conn->req.res, H2O_TOKEN_CONTENT_TYPE, "text/html"));
        ok(conn->body->size == 0);
        h2o_loopback_destroy(conn);
    }
    {
        h2o_loopback_conn_t *conn = h2o_loopback_create(&ctx, ctx.globalconf->hosts);
        conn->req.input.method = h2o_iovec_init(H2O_STRLIT("GET"));
        conn->req.input.path = h2o_iovec_init(H2O_STRLIT("/"));
        h2o_loopback_run_loop(conn);
        ok(conn->req.res.status == 200);
        ok(check_header(&conn->req.res, H2O_TOKEN_CONTENT_TYPE, "text/html"));
        ok(h2o_memis(conn->body->bytes, conn->body->size, H2O_STRLIT("hello html\n")));
        h2o_loopback_destroy(conn);
    }
    {
        h2o_loopback_conn_t *conn = h2o_loopback_create(&ctx, ctx.globalconf->hosts);
        conn->req.input.method = h2o_iovec_init(H2O_STRLIT("HEAD"));
        conn->req.input.path = h2o_iovec_init(H2O_STRLIT("/index.html"));
        h2o_loopback_run_loop(conn);
        ok(conn->req.res.status == 200);
        ok(check_header(&conn->req.res, H2O_TOKEN_CONTENT_TYPE, "text/html"));
        ok(conn->body->size == 0);
        h2o_loopback_destroy(conn);
    }
    {
        h2o_loopback_conn_t *conn = h2o_loopback_create(&ctx, ctx.globalconf->hosts);
        conn->req.input.method = h2o_iovec_init(H2O_STRLIT("GET"));
        conn->req.input.path = h2o_iovec_init(H2O_STRLIT("/index.html"));
        h2o_loopback_run_loop(conn);
        ok(conn->req.res.status == 200);
        ok(check_header(&conn->req.res, H2O_TOKEN_CONTENT_TYPE, "text/html"));
        ok(h2o_memis(conn->body->bytes, conn->body->size, H2O_STRLIT("hello html\n")));
        h2o_loopback_destroy(conn);
    }
    {
        h2o_loopback_conn_t *conn = h2o_loopback_create(&ctx, ctx.globalconf->hosts);
        conn->req.input.method = h2o_iovec_init(H2O_STRLIT("HEAD"));
        conn->req.input.path = h2o_iovec_init(H2O_STRLIT("/1000.txt"));
        h2o_loopback_run_loop(conn);
        ok(conn->req.res.status == 200);
        ok(check_header(&conn->req.res, H2O_TOKEN_CONTENT_TYPE, "text/plain"));
        ok(conn->body->size == 0);
        h2o_loopback_destroy(conn);
    }
    {
        h2o_loopback_conn_t *conn = h2o_loopback_create(&ctx, ctx.globalconf->hosts);
        conn->req.input.method = h2o_iovec_init(H2O_STRLIT("GET"));
        conn->req.input.path = h2o_iovec_init(H2O_STRLIT("/1000.txt"));
        h2o_loopback_run_loop(conn);
        ok(conn->req.res.status == 200);
        ok(check_header(&conn->req.res, H2O_TOKEN_CONTENT_TYPE, "text/plain"));
        ok(conn->body->size == 1000);
        ok(strcmp(sha1sum(conn->body->bytes, conn->body->size), "dfd3ae1f5c475555fad62efe42e07309fa45f2ed") == 0);
        h2o_loopback_destroy(conn);
    }
    {
        h2o_loopback_conn_t *conn = h2o_loopback_create(&ctx, ctx.globalconf->hosts);
        conn->req.input.method = h2o_iovec_init(H2O_STRLIT("HEAD"));
        conn->req.input.path = h2o_iovec_init(H2O_STRLIT("/1000000.txt"));
        h2o_loopback_run_loop(conn);
        ok(conn->req.res.status == 200);
        ok(check_header(&conn->req.res, H2O_TOKEN_CONTENT_TYPE, "text/plain"));
        ok(conn->body->size == 0);
        h2o_loopback_destroy(conn);
    }
    {
        h2o_loopback_conn_t *conn = h2o_loopback_create(&ctx, ctx.globalconf->hosts);
        conn->req.input.method = h2o_iovec_init(H2O_STRLIT("GET"));
        conn->req.input.path = h2o_iovec_init(H2O_STRLIT("/1000000.txt"));
        h2o_loopback_run_loop(conn);
        ok(conn->req.res.status == 200);
        ok(check_header(&conn->req.res, H2O_TOKEN_CONTENT_TYPE, "text/plain"));
        ok(conn->body->size == 1000000);
        ok(strcmp(sha1sum(conn->body->bytes, conn->body->size), "00c8ab71d0914dce6a1ec2eaa0fda0df7044b2a2") == 0);
        h2o_loopback_destroy(conn);
    }
    {
        h2o_loopback_conn_t *conn = h2o_loopback_create(&ctx, ctx.globalconf->hosts);
        conn->req.input.method = h2o_iovec_init(H2O_STRLIT("HEAD"));
        conn->req.input.path = h2o_iovec_init(H2O_STRLIT("/index_txt/"));
        h2o_loopback_run_loop(conn);
        ok(conn->req.res.status == 200);
        ok(check_header(&conn->req.res, H2O_TOKEN_CONTENT_TYPE, "text/plain"));
        ok(conn->body->size == 0);
        h2o_loopback_destroy(conn);
    }
    {
        h2o_loopback_conn_t *conn = h2o_loopback_create(&ctx, ctx.globalconf->hosts);
        conn->req.input.method = h2o_iovec_init(H2O_STRLIT("GET"));
        conn->req.input.path = h2o_iovec_init(H2O_STRLIT("/index_txt/"));
        h2o_loopback_run_loop(conn);
        ok(conn->req.res.status == 200);
        ok(check_header(&conn->req.res, H2O_TOKEN_CONTENT_TYPE, "text/plain"));
        ok(h2o_memis(conn->body->bytes, conn->body->size, H2O_STRLIT("hello text\n")));
        h2o_loopback_destroy(conn);
    }
    {
        h2o_loopback_conn_t *conn = h2o_loopback_create(&ctx, ctx.globalconf->hosts);
        conn->req.input.method = h2o_iovec_init(H2O_STRLIT("HEAD"));
        conn->req.input.path = h2o_iovec_init(H2O_STRLIT("/index_txt"));
        h2o_loopback_run_loop(conn);
        ok(conn->req.res.status == 301);
        ok(check_header(&conn->req.res, H2O_TOKEN_LOCATION, "/index_txt/"));
        h2o_loopback_destroy(conn);
    }
    {
        h2o_loopback_conn_t *conn = h2o_loopback_create(&ctx, ctx.globalconf->hosts);
        conn->req.input.method = h2o_iovec_init(H2O_STRLIT("GET"));
        conn->req.input.path = h2o_iovec_init(H2O_STRLIT("/index_txt"));
        h2o_loopback_run_loop(conn);
        ok(conn->req.res.status == 301);
        ok(check_header(&conn->req.res, H2O_TOKEN_LOCATION, "/index_txt/"));
        h2o_loopback_destroy(conn);
    }
    {
        h2o_loopback_conn_t *conn = h2o_loopback_create(&ctx, ctx.globalconf->hosts);
        conn->req.input.method = h2o_iovec_init(H2O_STRLIT("HEAD"));
        conn->req.input.path = h2o_iovec_init(H2O_STRLIT("/index_txt_as_dir/"));
        h2o_loopback_run_loop(conn);
        ok(conn->req.res.status == 301);
        ok(check_header(&conn->req.res, H2O_TOKEN_LOCATION, "/index_txt_as_dir/index.txt/"));
        h2o_loopback_destroy(conn);
    }
    {
        h2o_loopback_conn_t *conn = h2o_loopback_create(&ctx, ctx.globalconf->hosts);
        conn->req.input.method = h2o_iovec_init(H2O_STRLIT("GET"));
        conn->req.input.path = h2o_iovec_init(H2O_STRLIT("/index_txt_as_dir/"));
        h2o_loopback_run_loop(conn);
        ok(conn->req.res.status == 301);
        ok(check_header(&conn->req.res, H2O_TOKEN_LOCATION, "/index_txt_as_dir/index.txt/"));
        h2o_loopback_destroy(conn);
    }
    subtest("if-modified-since", test_if_modified_since);
    subtest("if-match", test_if_match);
    subtest("process_range()", test_process_range);
    subtest("range request", test_range_req);
    subtest("if-range", test_if_range);
    subtest("strong etag comparison", test_strong_etag_cmp);

    h2o_context_dispose(&ctx);
    h2o_config_dispose(&globalconf);
}