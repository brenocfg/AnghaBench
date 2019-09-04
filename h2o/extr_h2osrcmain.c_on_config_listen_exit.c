#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  yoml_t ;
struct listener_config_t {int /*<<< orphan*/ * hosts; } ;
typedef  int /*<<< orphan*/  h2o_configurator_t ;
struct TYPE_6__ {int /*<<< orphan*/ * pathconf; int /*<<< orphan*/ * hostconf; } ;
typedef  TYPE_2__ h2o_configurator_context_t ;
struct TYPE_5__ {int /*<<< orphan*/ * hosts; } ;
struct TYPE_7__ {size_t num_listeners; TYPE_1__ globalconf; struct listener_config_t** listeners; } ;

/* Variables and functions */
 TYPE_4__ conf ; 
 int /*<<< orphan*/  h2o_configurator_errprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int on_config_listen_exit(h2o_configurator_t *_configurator, h2o_configurator_context_t *ctx, yoml_t *node)
{
    if (ctx->pathconf != NULL) {
        /* skip */
    } else if (ctx->hostconf == NULL) {
        /* at global level: bind all hostconfs to the global-level listeners */
        size_t i;
        for (i = 0; i != conf.num_listeners; ++i) {
            struct listener_config_t *listener = conf.listeners[i];
            if (listener->hosts == NULL)
                listener->hosts = conf.globalconf.hosts;
        }
    } else if (ctx->pathconf == NULL) {
        /* at host-level */
        if (conf.num_listeners == 0) {
            h2o_configurator_errprintf(
                NULL, node,
                "mandatory configuration directive `listen` does not exist, neither at global level or at this host level");
            return -1;
        }
    }

    return 0;
}