#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uv_loop_t ;
typedef  int /*<<< orphan*/  h2o_pathconf_t ;
typedef  int /*<<< orphan*/  h2o_hostconf_t ;
typedef  int /*<<< orphan*/  h2o_access_log_filehandle_t ;
struct TYPE_10__ {int /*<<< orphan*/  hosts; TYPE_1__* ctx; } ;
struct TYPE_9__ {int /*<<< orphan*/  hosts; } ;
struct TYPE_8__ {int /*<<< orphan*/  loop; int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_LOGCONF_ESCAPE_APACHE ; 
 int /*<<< orphan*/  H2O_STRLIT (char*) ; 
 int /*<<< orphan*/  INT32_MAX ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIG_IGN ; 
 scalar_t__ USE_HTTPS ; 
 scalar_t__ USE_MEMCACHED ; 
 int /*<<< orphan*/  UV_RUN_DEFAULT ; 
 TYPE_7__ accept_ctx ; 
 int /*<<< orphan*/  chunked_test ; 
 TYPE_2__ config ; 
 scalar_t__ create_listener () ; 
 TYPE_1__ ctx ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/ * h2o_access_log_open_handle (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_access_log_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_config_init (TYPE_2__*) ; 
 int /*<<< orphan*/ * h2o_config_register_host (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * h2o_config_register_path (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_context_init (TYPE_1__*,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/ * h2o_evloop_create () ; 
 scalar_t__ h2o_evloop_run (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_file_register (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_iovec_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_memcached_receiver ; 
 int /*<<< orphan*/  h2o_multithread_register_receiver (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_reproxy_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libmemcached_receiver ; 
 int /*<<< orphan*/  post_test ; 
 int /*<<< orphan*/ * register_handler (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reproxy_test ; 
 scalar_t__ setup_ssl (char*,char*,char*) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv_loop_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_run (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int main(int argc, char **argv)
{
    h2o_hostconf_t *hostconf;
    h2o_access_log_filehandle_t *logfh = h2o_access_log_open_handle("/dev/stdout", NULL, H2O_LOGCONF_ESCAPE_APACHE);
    h2o_pathconf_t *pathconf;

    signal(SIGPIPE, SIG_IGN);

    h2o_config_init(&config);
    hostconf = h2o_config_register_host(&config, h2o_iovec_init(H2O_STRLIT("default")), 65535);

    pathconf = register_handler(hostconf, "/post-test", post_test);
    if (logfh != NULL)
        h2o_access_log_register(pathconf, logfh);

    pathconf = register_handler(hostconf, "/chunked-test", chunked_test);
    if (logfh != NULL)
        h2o_access_log_register(pathconf, logfh);

    pathconf = register_handler(hostconf, "/reproxy-test", reproxy_test);
    h2o_reproxy_register(pathconf);
    if (logfh != NULL)
        h2o_access_log_register(pathconf, logfh);

    pathconf = h2o_config_register_path(hostconf, "/", 0);
    h2o_file_register(pathconf, "examples/doc_root", NULL, NULL, 0);
    if (logfh != NULL)
        h2o_access_log_register(pathconf, logfh);

#if H2O_USE_LIBUV
    uv_loop_t loop;
    uv_loop_init(&loop);
    h2o_context_init(&ctx, &loop, &config);
#else
    h2o_context_init(&ctx, h2o_evloop_create(), &config);
#endif
    if (USE_MEMCACHED)
        h2o_multithread_register_receiver(ctx.queue, &libmemcached_receiver, h2o_memcached_receiver);

    if (USE_HTTPS && setup_ssl("examples/h2o/server.crt", "examples/h2o/server.key",
                               "DEFAULT:!MD5:!DSS:!DES:!RC4:!RC2:!SEED:!IDEA:!NULL:!ADH:!EXP:!SRP:!PSK") != 0)
        goto Error;

    accept_ctx.ctx = &ctx;
    accept_ctx.hosts = config.hosts;

    if (create_listener() != 0) {
        fprintf(stderr, "failed to listen to 127.0.0.1:7890:%s\n", strerror(errno));
        goto Error;
    }

#if H2O_USE_LIBUV
    uv_run(ctx.loop, UV_RUN_DEFAULT);
#else
    while (h2o_evloop_run(ctx.loop, INT32_MAX) == 0)
        ;
#endif

Error:
    return 1;
}