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
struct TYPE_8__ {TYPE_2__* p_subn; } ;
typedef  TYPE_3__ osm_sm_t ;
typedef  scalar_t__ osm_signal_t ;
struct TYPE_7__ {TYPE_1__* p_osm; } ;
struct TYPE_6__ {int /*<<< orphan*/  perfmgr; } ;

/* Variables and functions */
 scalar_t__ OSM_SIGNAL_PERFMGR_SWEEP ; 
 int /*<<< orphan*/  osm_perfmgr_process (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  osm_state_mgr_process (TYPE_3__*,scalar_t__) ; 

__attribute__((used)) static void sm_process(osm_sm_t * sm, osm_signal_t signal)
{
#ifdef ENABLE_OSM_PERF_MGR
	if (signal == OSM_SIGNAL_PERFMGR_SWEEP)
		osm_perfmgr_process(&sm->p_subn->p_osm->perfmgr);
	else
#endif
		osm_state_mgr_process(sm, signal);
}