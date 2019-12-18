#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  osm_switch_t ;
struct TYPE_4__ {int /*<<< orphan*/  p_log; } ;
typedef  TYPE_1__ osm_sm_t ;
typedef  int /*<<< orphan*/  cl_qlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  OSM_LOG_ENTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSM_LOG_EXIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mcast_mgr_find_optimal_switch (TYPE_1__*,int /*<<< orphan*/ *) ; 

osm_switch_t *osm_mcast_mgr_find_root_switch(osm_sm_t * sm, cl_qlist_t *list)
{
	osm_switch_t *p_sw = NULL;

	OSM_LOG_ENTER(sm->p_log);

	/*
	   We always look for the best multicast tree root switch.
	   Otherwise since we always start with a a single join
	   the root will be always on the first switch attached to it.
	   - Very bad ...
	 */
	p_sw = mcast_mgr_find_optimal_switch(sm, list);

	OSM_LOG_EXIT(sm->p_log);
	return p_sw;
}