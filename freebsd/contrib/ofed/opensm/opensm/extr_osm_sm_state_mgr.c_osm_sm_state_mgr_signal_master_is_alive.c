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
struct TYPE_3__ {int /*<<< orphan*/  p_log; scalar_t__ retry_number; } ;
typedef  TYPE_1__ osm_sm_t ;

/* Variables and functions */
 int /*<<< orphan*/  OSM_LOG_ENTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSM_LOG_EXIT (int /*<<< orphan*/ ) ; 

void osm_sm_state_mgr_signal_master_is_alive(osm_sm_t * sm)
{
	OSM_LOG_ENTER(sm->p_log);
	sm->retry_number = 0;
	OSM_LOG_EXIT(sm->p_log);
}