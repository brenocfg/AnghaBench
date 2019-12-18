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
struct TYPE_6__ {TYPE_1__* p_subn; int /*<<< orphan*/  p_log; } ;
typedef  TYPE_2__ osm_ucast_mgr_t ;
struct TYPE_5__ {int /*<<< orphan*/  sw_guid_tbl; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSM_LOG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  OSM_LOG_ERROR ; 
 int /*<<< orphan*/  add_sw_endports_to_order_list (void*,TYPE_2__*) ; 
 int cl_qmap_count (int /*<<< orphan*/ *) ; 
 void* cl_qmap_head (int /*<<< orphan*/ *) ; 
 void* cl_qmap_next (void*) ; 
 int /*<<< orphan*/  compar_sw_load ; 
 int /*<<< orphan*/  free (void**) ; 
 void** malloc (int) ; 
 int /*<<< orphan*/  qsort (void**,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sw_count_endport_links (void*) ; 

__attribute__((used)) static void sort_ports_by_switch_load(osm_ucast_mgr_t * m)
{
	int i, num = cl_qmap_count(&m->p_subn->sw_guid_tbl);
	void **s = malloc(num * sizeof(*s));
	if (!s) {
		OSM_LOG(m->p_log, OSM_LOG_ERROR, "ERR 3A0C: "
			"No memory, skip by switch load sorting.\n");
		return;
	}
	s[0] = cl_qmap_head(&m->p_subn->sw_guid_tbl);
	for (i = 1; i < num; i++)
		s[i] = cl_qmap_next(s[i - 1]);

	for (i = 0; i < num; i++)
		sw_count_endport_links(s[i]);

	qsort(s, num, sizeof(*s), compar_sw_load);

	for (i = 0; i < num; i++)
		add_sw_endports_to_order_list(s[i], m);
	free(s);
}