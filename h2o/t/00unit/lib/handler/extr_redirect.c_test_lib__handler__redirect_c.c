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
struct TYPE_16__ {void* path; void* method; } ;
struct TYPE_17__ {TYPE_13__ res; TYPE_2__ input; } ;
struct TYPE_19__ {TYPE_4__* body; TYPE_3__ req; } ;
typedef  TYPE_5__ h2o_loopback_conn_t ;
typedef  int /*<<< orphan*/  h2o_hostconf_t ;
typedef  int /*<<< orphan*/  h2o_globalconf_t ;
struct TYPE_20__ {TYPE_1__* globalconf; } ;
struct TYPE_18__ {scalar_t__ size; } ;
struct TYPE_15__ {int /*<<< orphan*/  hosts; } ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_STRLIT (char*) ; 
 int /*<<< orphan*/  H2O_TOKEN_LOCATION ; 
 int check_header (TYPE_13__*,int /*<<< orphan*/ ,char*) ; 
 TYPE_9__ ctx ; 
 int /*<<< orphan*/  h2o_config_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_config_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * h2o_config_register_host (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/ * h2o_config_register_path (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_context_dispose (TYPE_9__*) ; 
 int /*<<< orphan*/  h2o_context_init (TYPE_9__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* h2o_iovec_init (int /*<<< orphan*/ ) ; 
 TYPE_5__* h2o_loopback_create (TYPE_9__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_loopback_destroy (TYPE_5__*) ; 
 int /*<<< orphan*/  h2o_loopback_run_loop (TYPE_5__*) ; 
 int /*<<< orphan*/  h2o_redirect_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  ok (int) ; 
 int /*<<< orphan*/  test_loop ; 

void test_lib__handler__redirect_c()
{
    h2o_globalconf_t globalconf;
    h2o_hostconf_t *hostconf;
    h2o_pathconf_t *pathconf;

    h2o_config_init(&globalconf);
    hostconf = h2o_config_register_host(&globalconf, h2o_iovec_init(H2O_STRLIT("default")), 65535);
    pathconf = h2o_config_register_path(hostconf, "/", 0);
    h2o_redirect_register(pathconf, 0, 301, "https://example.com/bar/");

    h2o_context_init(&ctx, test_loop, &globalconf);

    {
        h2o_loopback_conn_t *conn = h2o_loopback_create(&ctx, ctx.globalconf->hosts);
        conn->req.input.method = h2o_iovec_init(H2O_STRLIT("GET"));
        conn->req.input.path = h2o_iovec_init(H2O_STRLIT("/"));
        h2o_loopback_run_loop(conn);
        ok(conn->req.res.status == 301);
        ok(check_header(&conn->req.res, H2O_TOKEN_LOCATION, "https://example.com/bar/"));
        ok(conn->body->size != 0);
        h2o_loopback_destroy(conn);
    }
    {
        h2o_loopback_conn_t *conn = h2o_loopback_create(&ctx, ctx.globalconf->hosts);
        conn->req.input.method = h2o_iovec_init(H2O_STRLIT("GET"));
        conn->req.input.path = h2o_iovec_init(H2O_STRLIT("/abc"));
        h2o_loopback_run_loop(conn);
        ok(conn->req.res.status == 301);
        ok(check_header(&conn->req.res, H2O_TOKEN_LOCATION, "https://example.com/bar/abc"));
        ok(conn->body->size != 0);
        h2o_loopback_destroy(conn);
    }
    {
        h2o_loopback_conn_t *conn = h2o_loopback_create(&ctx, ctx.globalconf->hosts);
        conn->req.input.method = h2o_iovec_init(H2O_STRLIT("HEAD"));
        conn->req.input.path = h2o_iovec_init(H2O_STRLIT("/"));
        h2o_loopback_run_loop(conn);
        ok(conn->req.res.status == 301);
        ok(check_header(&conn->req.res, H2O_TOKEN_LOCATION, "https://example.com/bar/"));
        ok(conn->body->size == 0);
        h2o_loopback_destroy(conn);
    }

    h2o_context_dispose(&ctx);
    h2o_config_dispose(&globalconf);
}