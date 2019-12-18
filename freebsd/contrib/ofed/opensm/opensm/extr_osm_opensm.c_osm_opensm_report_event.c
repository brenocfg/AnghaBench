#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  plugin_list; } ;
typedef  TYPE_2__ osm_opensm_t ;
struct TYPE_7__ {int /*<<< orphan*/  plugin_data; TYPE_1__* impl; } ;
typedef  TYPE_3__ osm_epi_plugin_t ;
typedef  int /*<<< orphan*/  osm_epi_event_id_t ;
typedef  int /*<<< orphan*/  cl_list_item_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* report ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/ * cl_qlist_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cl_qlist_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cl_qlist_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  osm_exit_flag ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

void osm_opensm_report_event(osm_opensm_t *osm, osm_epi_event_id_t event_id,
			     void *event_data)
{
	cl_list_item_t *item;

	for (item = cl_qlist_head(&osm->plugin_list);
	     !osm_exit_flag && item != cl_qlist_end(&osm->plugin_list);
	     item = cl_qlist_next(item)) {
		osm_epi_plugin_t *p = (osm_epi_plugin_t *)item;
		if (p->impl->report)
			p->impl->report(p->plugin_data, event_id, event_data);
	}
}