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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_3__ {int /*<<< orphan*/  cache_sw_tbl; } ;
typedef  TYPE_1__ osm_ucast_mgr_t ;
typedef  int /*<<< orphan*/  cache_switch_t ;

/* Variables and functions */
 scalar_t__ cl_qmap_end (int /*<<< orphan*/ *) ; 
 scalar_t__ cl_qmap_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static cache_switch_t *cache_get_sw(osm_ucast_mgr_t * p_mgr, uint16_t lid_ho)
{
	cache_switch_t *p_cache_sw = (cache_switch_t *)
	    cl_qmap_get(&p_mgr->cache_sw_tbl, lid_ho);
	if (p_cache_sw == (cache_switch_t *)
	    cl_qmap_end(&p_mgr->cache_sw_tbl))
		p_cache_sw = NULL;

	return p_cache_sw;
}