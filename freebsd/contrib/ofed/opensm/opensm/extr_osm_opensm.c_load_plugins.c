#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  plugin_list; int /*<<< orphan*/  log; } ;
typedef  TYPE_1__ osm_opensm_t ;
struct TYPE_7__ {int /*<<< orphan*/  list; } ;
typedef  TYPE_2__ osm_epi_plugin_t ;

/* Variables and functions */
 int /*<<< orphan*/  FILE_ID ; 
 int /*<<< orphan*/  OSM_LOG_ERROR ; 
 int /*<<< orphan*/  cl_qlist_insert_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_2__* osm_epi_construct (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  osm_log_v2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 char* strdup (char const*) ; 
 char* strtok_r (char*,char*,char**) ; 

__attribute__((used)) static void load_plugins(osm_opensm_t *osm, const char *plugin_names)
{
	osm_epi_plugin_t *epi;
	char *p_names, *name, *p;

	p_names = strdup(plugin_names);
	name = strtok_r(p_names, ", \t\n", &p);
	while (name && *name) {
		epi = osm_epi_construct(osm, name);
		if (!epi)
			osm_log_v2(&osm->log, OSM_LOG_ERROR, FILE_ID,
				   "ERR 1000: cannot load plugin \'%s\'\n",
				   name);
		else
			cl_qlist_insert_tail(&osm->plugin_list, &epi->list);
		name = strtok_r(NULL, " \t\n", &p);
	}
	free(p_names);
}