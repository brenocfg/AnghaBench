#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  h2o_pathconf_t ;
typedef  int /*<<< orphan*/  h2o_hostconf_t ;
struct TYPE_6__ {int /*<<< orphan*/  server_name; } ;
typedef  TYPE_1__ h2o_globalconf_t ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_STRLIT (char*) ; 
 int /*<<< orphan*/  ctx ; 
 int /*<<< orphan*/  h2o_config_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  h2o_config_init (TYPE_1__*) ; 
 int /*<<< orphan*/ * h2o_config_register_host (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * h2o_config_register_path (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_context_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_context_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  h2o_iovec_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  subtest (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_build_request ; 
 int /*<<< orphan*/  test_loop ; 

void test_lib__handler__fastcgi_c()
{
    h2o_globalconf_t globalconf;
    h2o_hostconf_t *hostconf;
    h2o_pathconf_t *pathconf;

    h2o_config_init(&globalconf);
    globalconf.server_name = h2o_iovec_init(H2O_STRLIT("h2o/1.2.1-alpha1"));
    hostconf = h2o_config_register_host(&globalconf, h2o_iovec_init(H2O_STRLIT("default")), 65535);
    pathconf = h2o_config_register_path(hostconf, "/", 0);

    h2o_context_init(&ctx, test_loop, &globalconf);

    subtest("build-request", test_build_request);

    h2o_context_dispose(&ctx);
    h2o_config_dispose(&globalconf);
}