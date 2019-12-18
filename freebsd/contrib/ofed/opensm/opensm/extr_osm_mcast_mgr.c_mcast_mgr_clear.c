#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_7__ {int /*<<< orphan*/  map_item; } ;
typedef  TYPE_2__ osm_switch_t ;
struct TYPE_8__ {int /*<<< orphan*/  p_log; TYPE_1__* p_subn; } ;
typedef  TYPE_3__ osm_sm_t ;
typedef  int /*<<< orphan*/  osm_mcast_tbl_t ;
typedef  int /*<<< orphan*/  cl_qmap_t ;
struct TYPE_6__ {int /*<<< orphan*/  sw_guid_tbl; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSM_LOG_ENTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSM_LOG_EXIT (int /*<<< orphan*/ ) ; 
 scalar_t__ cl_qmap_end (int /*<<< orphan*/ *) ; 
 scalar_t__ cl_qmap_head (int /*<<< orphan*/ *) ; 
 scalar_t__ cl_qmap_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  osm_mcast_tbl_clear_mlid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * osm_switch_get_mcast_tbl_ptr (TYPE_2__*) ; 

__attribute__((used)) static void mcast_mgr_clear(osm_sm_t * sm, uint16_t mlid)
{
	osm_switch_t *p_sw;
	cl_qmap_t *p_sw_tbl;
	osm_mcast_tbl_t *p_mcast_tbl;

	OSM_LOG_ENTER(sm->p_log);

	/* Walk the switches and clear the routing entries for this MLID. */
	p_sw_tbl = &sm->p_subn->sw_guid_tbl;
	p_sw = (osm_switch_t *) cl_qmap_head(p_sw_tbl);
	while (p_sw != (osm_switch_t *) cl_qmap_end(p_sw_tbl)) {
		p_mcast_tbl = osm_switch_get_mcast_tbl_ptr(p_sw);
		osm_mcast_tbl_clear_mlid(p_mcast_tbl, mlid);
		p_sw = (osm_switch_t *) cl_qmap_next(&p_sw->map_item);
	}

	OSM_LOG_EXIT(sm->p_log);
}