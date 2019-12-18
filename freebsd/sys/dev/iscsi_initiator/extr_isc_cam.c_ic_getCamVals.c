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
struct TYPE_5__ {int /*<<< orphan*/  target_nluns; scalar_t__ target_id; int /*<<< orphan*/  path_id; } ;
typedef  TYPE_1__ iscsi_cam_t ;
struct TYPE_6__ {scalar_t__ cam_sim; } ;
typedef  TYPE_2__ isc_session_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  ISCSI_MAX_LUNS ; 
 int /*<<< orphan*/  cam_sim_path (scalar_t__) ; 
 int /*<<< orphan*/  debug_called (int) ; 

int
ic_getCamVals(isc_session_t *sp, iscsi_cam_t *cp)
{
     debug_called(8);

     if(sp && sp->cam_sim) {
	  cp->path_id = cam_sim_path(sp->cam_sim);
	  cp->target_id = 0;
	  cp->target_nluns = ISCSI_MAX_LUNS; // XXX: -1?
	  return 0;
     }
     return ENXIO;
}