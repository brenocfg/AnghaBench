#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  p_log; int /*<<< orphan*/  cache_valid; } ;
typedef  TYPE_2__ osm_ucast_mgr_t ;
struct TYPE_10__ {TYPE_1__* p_remote_physp; } ;
typedef  TYPE_3__ osm_physp_t ;
struct TYPE_8__ {scalar_t__ p_remote_physp; } ;

/* Variables and functions */
 int /*<<< orphan*/  CL_ASSERT (int) ; 
 int /*<<< orphan*/  OSM_LOG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  OSM_LOG_DEBUG ; 
 int /*<<< orphan*/  OSM_LOG_ENTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSM_LOG_EXIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osm_ucast_cache_invalidate (TYPE_2__*) ; 

__attribute__((used)) static void
cache_check_link_change(osm_ucast_mgr_t * p_mgr,
			osm_physp_t * p_physp_1, osm_physp_t * p_physp_2)
{
	OSM_LOG_ENTER(p_mgr->p_log);
	CL_ASSERT(p_physp_1 && p_physp_2);

	if (!p_mgr->cache_valid)
		goto Exit;

	if (!p_physp_1->p_remote_physp && !p_physp_2->p_remote_physp)
		/* both ports were down - new link */
		goto Exit;

	/* unicast cache cannot tolerate any link location change */

	if ((p_physp_1->p_remote_physp &&
	     p_physp_1->p_remote_physp->p_remote_physp) ||
	    (p_physp_2->p_remote_physp &&
	     p_physp_2->p_remote_physp->p_remote_physp)) {
		OSM_LOG(p_mgr->p_log, OSM_LOG_DEBUG,
			"Link location change discovered\n");
		osm_ucast_cache_invalidate(p_mgr);
		goto Exit;
	}
Exit:
	OSM_LOG_EXIT(p_mgr->p_log);
}