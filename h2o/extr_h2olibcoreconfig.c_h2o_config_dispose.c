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
typedef  int /*<<< orphan*/  h2o_hostconf_t ;
struct TYPE_5__ {int /*<<< orphan*/  global_socketpool; } ;
struct TYPE_6__ {int /*<<< orphan*/  mimemap; TYPE_1__ proxy; int /*<<< orphan*/ ** hosts; } ;
typedef  TYPE_2__ h2o_globalconf_t ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_hostconf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  h2o_configurator__dispose_configurators (TYPE_2__*) ; 
 int /*<<< orphan*/  h2o_mem_release_shared (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_socketpool_dispose (int /*<<< orphan*/ *) ; 

void h2o_config_dispose(h2o_globalconf_t *config)
{
    size_t i;

    for (i = 0; config->hosts[i] != NULL; ++i) {
        h2o_hostconf_t *hostconf = config->hosts[i];
        destroy_hostconf(hostconf);
    }
    free(config->hosts);

    h2o_socketpool_dispose(&config->proxy.global_socketpool);
    h2o_mem_release_shared(config->mimemap);
    h2o_configurator__dispose_configurators(config);
}