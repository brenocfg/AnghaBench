#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  scalar; } ;
struct TYPE_11__ {TYPE_2__ data; } ;
typedef  TYPE_3__ yoml_t ;
struct proxy_configurator_t {TYPE_1__* vars; } ;
typedef  int /*<<< orphan*/  h2o_configurator_context_t ;
struct TYPE_12__ {scalar_t__ configurator; } ;
typedef  TYPE_4__ h2o_configurator_command_t ;
typedef  int /*<<< orphan*/  X509_STORE ;
struct TYPE_9__ {int /*<<< orphan*/  ssl_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_print_errors_fp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_STORE_free (int /*<<< orphan*/ *) ; 
 int X509_STORE_load_locations (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_STORE_new () ; 
 int /*<<< orphan*/  h2o_configurator_errprintf (TYPE_4__*,TYPE_3__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  update_ssl_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int on_config_ssl_cafile(h2o_configurator_command_t *cmd, h2o_configurator_context_t *ctx, yoml_t *node)
{
    struct proxy_configurator_t *self = (void *)cmd->configurator;
    X509_STORE *store = X509_STORE_new();
    int ret = -1;

    if (X509_STORE_load_locations(store, node->data.scalar, NULL) == 1) {
        update_ssl_ctx(&self->vars->ssl_ctx, store, -1, NULL);
        ret = 0;
    } else {
        h2o_configurator_errprintf(cmd, node, "failed to load certificates file:%s", node->data.scalar);
        ERR_print_errors_fp(stderr);
    }

    X509_STORE_free(store);
    return ret;
}