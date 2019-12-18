#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  num_loggers; int /*<<< orphan*/  loggers; int /*<<< orphan*/  num_filters; int /*<<< orphan*/  filters; TYPE_4__* pathconf; int /*<<< orphan*/ * hostconf; } ;
typedef  TYPE_3__ h2o_req_t ;
struct TYPE_8__ {int /*<<< orphan*/  size; int /*<<< orphan*/  entries; } ;
struct TYPE_9__ {int /*<<< orphan*/  size; int /*<<< orphan*/  entries; } ;
struct TYPE_11__ {int /*<<< orphan*/ * env; TYPE_1__ _loggers; TYPE_2__ _filters; } ;
typedef  TYPE_4__ h2o_pathconf_t ;
typedef  int /*<<< orphan*/  h2o_hostconf_t ;

/* Variables and functions */
 int /*<<< orphan*/  apply_env (TYPE_3__*,int /*<<< orphan*/ *) ; 

void h2o_req_bind_conf(h2o_req_t *req, h2o_hostconf_t *hostconf, h2o_pathconf_t *pathconf)
{
    req->hostconf = hostconf;
    req->pathconf = pathconf;

    /* copy filters and loggers */
    req->filters = pathconf->_filters.entries;
    req->num_filters = pathconf->_filters.size;
    req->loggers = pathconf->_loggers.entries;
    req->num_loggers = pathconf->_loggers.size;

    if (pathconf->env != NULL)
        apply_env(req, pathconf->env);
}