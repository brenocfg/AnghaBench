#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  h2o_pathconf_t ;
struct TYPE_14__ {int /*<<< orphan*/  base; } ;
struct TYPE_11__ {int /*<<< orphan*/  lineno; int /*<<< orphan*/  path; TYPE_6__ source; } ;
struct TYPE_9__ {int /*<<< orphan*/  on_req; int /*<<< orphan*/  dispose; int /*<<< orphan*/  on_context_dispose; int /*<<< orphan*/  on_context_init; } ;
struct TYPE_12__ {int /*<<< orphan*/ * pathconf; TYPE_3__ config; TYPE_1__ super; } ;
typedef  TYPE_4__ h2o_mruby_handler_t ;
struct TYPE_10__ {int /*<<< orphan*/  len; int /*<<< orphan*/ * base; } ;
struct TYPE_13__ {int /*<<< orphan*/  lineno; int /*<<< orphan*/ * path; TYPE_2__ source; } ;
typedef  TYPE_5__ h2o_mruby_config_vars_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIZE_MAX ; 
 scalar_t__ h2o_create_handler (int /*<<< orphan*/ *,int) ; 
 TYPE_6__ h2o_strdup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  on_context_dispose ; 
 int /*<<< orphan*/  on_context_init ; 
 int /*<<< orphan*/  on_handler_dispose ; 
 int /*<<< orphan*/  on_req ; 

h2o_mruby_handler_t *h2o_mruby_register(h2o_pathconf_t *pathconf, h2o_mruby_config_vars_t *vars)
{
    h2o_mruby_handler_t *handler = (void *)h2o_create_handler(pathconf, sizeof(*handler));

    handler->super.on_context_init = on_context_init;
    handler->super.on_context_dispose = on_context_dispose;
    handler->super.dispose = on_handler_dispose;
    handler->super.on_req = on_req;
    handler->config.source = h2o_strdup(NULL, vars->source.base, vars->source.len);
    if (vars->path != NULL)
        handler->config.path = h2o_strdup(NULL, vars->path, SIZE_MAX).base;
    handler->config.lineno = vars->lineno;
    handler->pathconf = pathconf;

    return handler;
}