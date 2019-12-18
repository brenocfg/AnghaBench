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
struct TYPE_5__ {int /*<<< orphan*/  p_log; int /*<<< orphan*/  cache_sw_tbl; scalar_t__ cache_valid; } ;
typedef  TYPE_1__ osm_ucast_mgr_t ;
struct TYPE_6__ {int /*<<< orphan*/  map_item; } ;
typedef  TYPE_2__ cache_switch_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  OSM_LOG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  OSM_LOG_ENTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSM_LOG_EXIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSM_LOG_VERBOSE ; 
 int /*<<< orphan*/  cache_sw_destroy (TYPE_2__*) ; 
 scalar_t__ cl_qmap_end (int /*<<< orphan*/ *) ; 
 scalar_t__ cl_qmap_head (int /*<<< orphan*/ *) ; 
 scalar_t__ cl_qmap_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_qmap_remove_all (int /*<<< orphan*/ *) ; 

void osm_ucast_cache_invalidate(osm_ucast_mgr_t * p_mgr)
{
	cache_switch_t *p_sw;
	cache_switch_t *p_next_sw;

	OSM_LOG_ENTER(p_mgr->p_log);

	if (!p_mgr->cache_valid)
		goto Exit;

	p_mgr->cache_valid = FALSE;

	p_next_sw = (cache_switch_t *) cl_qmap_head(&p_mgr->cache_sw_tbl);
	while (p_next_sw !=
	       (cache_switch_t *) cl_qmap_end(&p_mgr->cache_sw_tbl)) {
		p_sw = p_next_sw;
		p_next_sw = (cache_switch_t *) cl_qmap_next(&p_sw->map_item);
		cache_sw_destroy(p_sw);
	}
	cl_qmap_remove_all(&p_mgr->cache_sw_tbl);

	OSM_LOG(p_mgr->p_log, OSM_LOG_VERBOSE, "Unicast Cache invalidated\n");
Exit:
	OSM_LOG_EXIT(p_mgr->p_log);
}