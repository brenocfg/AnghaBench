#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  cam_sim; int /*<<< orphan*/ * cam_path; } ;
typedef  TYPE_1__ isc_session_t ;

/* Variables and functions */
 int /*<<< orphan*/  AC_LOST_DEVICE ; 
 int /*<<< orphan*/  CAM_LOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  CAM_UNLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  XPT_RESET_BUS ; 
 int /*<<< orphan*/  cam_sim_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_sim_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_sim_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_sim_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  sdebug (int,char*,...) ; 
 int /*<<< orphan*/  xpt_async (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xpt_bus_deregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_free_path (int /*<<< orphan*/ *) ; 

void
ic_destroy(isc_session_t *sp )
{
     debug_called(8);

     if(sp->cam_path != NULL) {
	  sdebug(2, "name=%s unit=%d",
		 cam_sim_name(sp->cam_sim), cam_sim_unit(sp->cam_sim));
	  CAM_LOCK(sp);
#if 0
	  xpt_async(AC_LOST_DEVICE, sp->cam_path, NULL);
#else
	  xpt_async(XPT_RESET_BUS, sp->cam_path, NULL);
#endif
	  xpt_free_path(sp->cam_path);
	  xpt_bus_deregister(cam_sim_path(sp->cam_sim));
	  cam_sim_free(sp->cam_sim, TRUE /*free_devq*/);

	  CAM_UNLOCK(sp);
	  sdebug(2, "done");
     }
}