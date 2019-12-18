#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {scalar_t__ size; void** entries; } ;
struct TYPE_12__ {int size; } ;
struct TYPE_14__ {TYPE_8__ _loggers; TYPE_1__ handlers; } ;
typedef  TYPE_3__ h2o_pathconf_t ;
struct TYPE_15__ {int /*<<< orphan*/  on_context_dispose; int /*<<< orphan*/  on_context_init; int /*<<< orphan*/  log_access; scalar_t__ _config_slot; } ;
typedef  TYPE_4__ h2o_logger_t ;
struct TYPE_13__ {int size; TYPE_3__* entries; } ;
struct TYPE_16__ {TYPE_2__ paths; } ;
typedef  TYPE_5__ h2o_hostconf_t ;
struct TYPE_17__ {TYPE_5__** hosts; int /*<<< orphan*/  _num_config_slots; } ;
typedef  TYPE_6__ h2o_globalconf_t ;

/* Variables and functions */
 TYPE_4__* durations_logger ; 
 TYPE_4__* h2o_mem_alloc (int) ; 
 int /*<<< orphan*/  h2o_vector_reserve (int /*<<< orphan*/ *,TYPE_8__*,scalar_t__) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  on_context_dispose ; 
 int /*<<< orphan*/  on_context_init ; 
 int /*<<< orphan*/  stat_access ; 

void h2o_duration_stats_register(h2o_globalconf_t *conf)
{
    int i, k;
    h2o_logger_t *logger;
    h2o_hostconf_t *hconf;

    durations_logger = logger = h2o_mem_alloc(sizeof(*logger));
    memset(logger, 0, sizeof(*logger));
    logger->_config_slot = conf->_num_config_slots++;
    logger->log_access = stat_access;
    logger->on_context_init = on_context_init;
    logger->on_context_dispose = on_context_dispose;

    for (k = 0; conf->hosts[k]; k++) {
        hconf = conf->hosts[k];
        for (i = 0; i < hconf->paths.size; i++) {
            int j;
            for (j = 0; j < hconf->paths.entries[i].handlers.size; j++) {
                h2o_pathconf_t *pathconf = &hconf->paths.entries[i];
                h2o_vector_reserve(NULL, &pathconf->_loggers, pathconf->_loggers.size + 1);
                pathconf->_loggers.entries[pathconf->_loggers.size++] = (void *)logger;
            }
        }
    }
}