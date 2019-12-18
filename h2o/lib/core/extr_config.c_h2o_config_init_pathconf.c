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
struct TYPE_5__ {int emit_request_errors; } ;
struct TYPE_6__ {TYPE_1__ error_log; int /*<<< orphan*/ * mimemap; int /*<<< orphan*/  path; int /*<<< orphan*/ * global; } ;
typedef  TYPE_2__ h2o_pathconf_t ;
typedef  int /*<<< orphan*/  h2o_mimemap_t ;
typedef  int /*<<< orphan*/  h2o_globalconf_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIZE_MAX ; 
 int /*<<< orphan*/  h2o_mem_addref_shared (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_strdup (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

void h2o_config_init_pathconf(h2o_pathconf_t *pathconf, h2o_globalconf_t *globalconf, const char *path, h2o_mimemap_t *mimemap)
{
    memset(pathconf, 0, sizeof(*pathconf));
    pathconf->global = globalconf;
    if (path != NULL)
        pathconf->path = h2o_strdup(NULL, path, SIZE_MAX);
    h2o_mem_addref_shared(mimemap);
    pathconf->mimemap = mimemap;
    pathconf->error_log.emit_request_errors = 1;
}