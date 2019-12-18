#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  cache_valid; } ;
typedef  TYPE_1__ osm_ucast_mgr_t ;
struct TYPE_8__ {int need_update; int /*<<< orphan*/ * hops; scalar_t__ num_hops; int /*<<< orphan*/ * new_lft; scalar_t__ max_lid_ho; } ;
typedef  TYPE_2__ osm_switch_t ;
struct TYPE_9__ {int /*<<< orphan*/ * hops; scalar_t__ num_hops; int /*<<< orphan*/ * lft; scalar_t__ max_lid_ho; } ;
typedef  TYPE_3__ cache_switch_t ;

/* Variables and functions */
 int /*<<< orphan*/  CL_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
cache_restore_ucast_info(osm_ucast_mgr_t * p_mgr,
			 cache_switch_t * p_cache_sw, osm_switch_t * p_sw)
{
	if (!p_mgr->cache_valid)
		return;

	/* when seting unicast info, the cached port
	   should have all the required info */
	CL_ASSERT(p_cache_sw->max_lid_ho && p_cache_sw->lft &&
		  p_cache_sw->num_hops && p_cache_sw->hops);

	p_sw->max_lid_ho = p_cache_sw->max_lid_ho;

	if (p_sw->new_lft)
		free(p_sw->new_lft);
	p_sw->new_lft = p_cache_sw->lft;
	p_cache_sw->lft = NULL;

	p_sw->num_hops = p_cache_sw->num_hops;
	p_cache_sw->num_hops = 0;
	if (p_sw->hops)
		free(p_sw->hops);
	p_sw->hops = p_cache_sw->hops;
	p_cache_sw->hops = NULL;

	p_sw->need_update = 2;
}