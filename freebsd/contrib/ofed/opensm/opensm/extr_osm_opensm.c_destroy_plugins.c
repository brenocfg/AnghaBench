#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  plugin_list; } ;
typedef  TYPE_1__ osm_opensm_t ;
typedef  int /*<<< orphan*/  osm_epi_plugin_t ;

/* Variables and functions */
 int /*<<< orphan*/  cl_is_qlist_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ cl_qlist_remove_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  osm_epi_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void destroy_plugins(osm_opensm_t *osm)
{
	osm_epi_plugin_t *p;
	/* remove from the list, and destroy it */
	while (!cl_is_qlist_empty(&osm->plugin_list)){
		p = (osm_epi_plugin_t *)cl_qlist_remove_head(&osm->plugin_list);
		/* plugin is responsible for freeing its own resources */
		osm_epi_destroy(p);
	}
}