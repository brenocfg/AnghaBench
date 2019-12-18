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
struct TYPE_15__ {int status; } ;
struct TYPE_14__ {void* path; void* method; } ;
struct TYPE_16__ {TYPE_3__ res; TYPE_2__ input; } ;
struct TYPE_17__ {TYPE_4__ req; } ;
typedef  TYPE_5__ h2o_loopback_conn_t ;
typedef  int /*<<< orphan*/  h2o_globalconf_t ;
struct TYPE_18__ {TYPE_1__* globalconf; } ;
typedef  TYPE_6__ h2o_context_t ;
struct TYPE_13__ {int /*<<< orphan*/  hosts; } ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_STRLIT (char*) ; 
 int /*<<< orphan*/  h2o_config_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_config_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_config_register_host (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  h2o_context_dispose (TYPE_6__*) ; 
 int /*<<< orphan*/  h2o_context_init (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* h2o_iovec_init (int /*<<< orphan*/ ) ; 
 TYPE_5__* h2o_loopback_create (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_loopback_destroy (TYPE_5__*) ; 
 int /*<<< orphan*/  h2o_loopback_run_loop (TYPE_5__*) ; 
 int /*<<< orphan*/  ok (int) ; 
 int /*<<< orphan*/  test_loop ; 

__attribute__((used)) static void test_loopback(void)
{
    h2o_globalconf_t conf;
    h2o_context_t ctx;
    h2o_loopback_conn_t *conn;

    h2o_config_init(&conf);
    h2o_config_register_host(&conf, h2o_iovec_init(H2O_STRLIT("default")), 65535);
    h2o_context_init(&ctx, test_loop, &conf);

    conn = h2o_loopback_create(&ctx, ctx.globalconf->hosts);
    conn->req.input.method = h2o_iovec_init(H2O_STRLIT("GET"));
    conn->req.input.path = h2o_iovec_init(H2O_STRLIT("/"));
    h2o_loopback_run_loop(conn);

    ok(conn->req.res.status == 404);

    h2o_loopback_destroy(conn);

    h2o_context_dispose(&ctx);
    h2o_config_dispose(&conf);
}