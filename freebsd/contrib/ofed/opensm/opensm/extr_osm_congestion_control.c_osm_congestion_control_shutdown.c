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
struct TYPE_3__ {scalar_t__ bind_handle; int /*<<< orphan*/  log; int /*<<< orphan*/  cc_disp_h; } ;
typedef  TYPE_1__ osm_congestion_control_t ;

/* Variables and functions */
 scalar_t__ OSM_BIND_INVALID_HANDLE ; 
 int /*<<< orphan*/  OSM_LOG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  OSM_LOG_ENTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSM_LOG_ERROR ; 
 int /*<<< orphan*/  OSM_LOG_EXIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_disp_unregister (int /*<<< orphan*/ ) ; 

void osm_congestion_control_shutdown(osm_congestion_control_t * p_cc)
{
	OSM_LOG_ENTER(p_cc->log);
	if (p_cc->bind_handle == OSM_BIND_INVALID_HANDLE) {
		OSM_LOG(p_cc->log, OSM_LOG_ERROR,
			"ERR C108: No previous bind\n");
		goto Exit;
	}
	cl_disp_unregister(p_cc->cc_disp_h);
Exit:
	OSM_LOG_EXIT(p_cc->log);
}