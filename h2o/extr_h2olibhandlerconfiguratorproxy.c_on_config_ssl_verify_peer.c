#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  yoml_t ;
struct proxy_configurator_t {TYPE_1__* vars; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  h2o_configurator_context_t ;
struct TYPE_6__ {scalar_t__ configurator; } ;
typedef  TYPE_2__ h2o_configurator_command_t ;
struct TYPE_5__ {int /*<<< orphan*/  ssl_ctx; } ;

/* Variables and functions */
 int SSL_VERIFY_FAIL_IF_NO_PEER_CERT ; 
 int SSL_VERIFY_NONE ; 
 int SSL_VERIFY_PEER ; 
 int h2o_configurator_get_one_of (TYPE_2__*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  update_ssl_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int on_config_ssl_verify_peer(h2o_configurator_command_t *cmd, h2o_configurator_context_t *ctx, yoml_t *node)
{
    struct proxy_configurator_t *self = (void *)cmd->configurator;
    ssize_t ret = h2o_configurator_get_one_of(cmd, node, "OFF,ON");
    if (ret == -1)
        return -1;

    update_ssl_ctx(&self->vars->ssl_ctx, NULL, ret != 0 ? SSL_VERIFY_PEER | SSL_VERIFY_FAIL_IF_NO_PEER_CERT : SSL_VERIFY_NONE,
                   NULL);

    return 0;
}