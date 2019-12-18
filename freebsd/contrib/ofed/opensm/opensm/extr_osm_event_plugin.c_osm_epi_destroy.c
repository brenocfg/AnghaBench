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
struct TYPE_6__ {struct TYPE_6__* plugin_name; int /*<<< orphan*/  handle; int /*<<< orphan*/  plugin_data; TYPE_1__* impl; } ;
typedef  TYPE_2__ osm_epi_plugin_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* delete ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dlclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void osm_epi_destroy(osm_epi_plugin_t * plugin)
{
	if (plugin) {
		if (plugin->impl->delete)
			plugin->impl->delete(plugin->plugin_data);
		dlclose(plugin->handle);
		free(plugin->plugin_name);
		free(plugin);
	}
}