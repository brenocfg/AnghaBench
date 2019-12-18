#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  yoml_t ;
struct proxy_configurator_t {TYPE_4__* vars; scalar_t__ first_byte_timeout_set; scalar_t__ connect_timeout_set; } ;
typedef  int /*<<< orphan*/  h2o_configurator_t ;
struct TYPE_7__ {int /*<<< orphan*/ * hostconf; int /*<<< orphan*/ * pathconf; } ;
typedef  TYPE_2__ h2o_configurator_context_t ;
typedef  int /*<<< orphan*/  h2o_cache_t ;
struct TYPE_6__ {int /*<<< orphan*/ * headers_cmds; } ;
struct TYPE_8__ {int /*<<< orphan*/  ssl_ctx; TYPE_1__ conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_DEFAULT_PROXY_SSL_SESSION_CACHE_CAPACITY ; 
 int /*<<< orphan*/  H2O_DEFAULT_PROXY_SSL_SESSION_CACHE_DURATION ; 
 int SSL_CTX_load_verify_locations (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_set_verify (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_up_ref (int /*<<< orphan*/ ) ; 
 int SSL_VERIFY_FAIL_IF_NO_PEER_CERT ; 
 int SSL_VERIFY_PEER ; 
 int /*<<< orphan*/  create_ssl_ctx () ; 
 int /*<<< orphan*/ * create_ssl_session_cache (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* h2o_configurator_get_cmd_path (char*) ; 
 int /*<<< orphan*/  h2o_error_printf (char*,char*) ; 
 int /*<<< orphan*/  h2o_mem_addref_shared (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_socket_ssl_set_session_cache (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (TYPE_4__*,TYPE_4__*,int) ; 

__attribute__((used)) static int on_config_enter(h2o_configurator_t *_self, h2o_configurator_context_t *ctx, yoml_t *node)
{
    struct proxy_configurator_t *self = (void *)_self;

    memcpy(self->vars + 1, self->vars, sizeof(*self->vars));
    if (self->vars[1].conf.headers_cmds != NULL)
        h2o_mem_addref_shared(self->vars[1].conf.headers_cmds);
    ++self->vars;
    self->connect_timeout_set = 0;
    self->first_byte_timeout_set = 0;

    if (ctx->pathconf == NULL && ctx->hostconf == NULL) {
        /* is global conf, setup the default SSL context */
        self->vars->ssl_ctx = create_ssl_ctx();
        char *ca_bundle = h2o_configurator_get_cmd_path("share/h2o/ca-bundle.crt");
        if (SSL_CTX_load_verify_locations(self->vars->ssl_ctx, ca_bundle, NULL) != 1)
            h2o_error_printf("Warning: failed to load the default certificates file at %s. Proxying to HTTPS servers may fail.\n",
                             ca_bundle);
        free(ca_bundle);
        SSL_CTX_set_verify(self->vars->ssl_ctx, SSL_VERIFY_PEER | SSL_VERIFY_FAIL_IF_NO_PEER_CERT, NULL);
        h2o_cache_t *ssl_session_cache =
            create_ssl_session_cache(H2O_DEFAULT_PROXY_SSL_SESSION_CACHE_CAPACITY, H2O_DEFAULT_PROXY_SSL_SESSION_CACHE_DURATION);
        h2o_socket_ssl_set_session_cache(self->vars->ssl_ctx, ssl_session_cache);
    } else {
        SSL_CTX_up_ref(self->vars->ssl_ctx);
    }

    return 0;
}