#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  union ccb {int dummy; } ccb ;
struct TYPE_2__ {scalar_t__ status; int /*<<< orphan*/  flags; int /*<<< orphan*/  func_code; } ;
struct ccb_relsim {TYPE_1__ ccb_h; int /*<<< orphan*/  openings; int /*<<< orphan*/  release_flags; } ;
struct cam_path {int dummy; } ;
typedef  int /*<<< orphan*/  bit32 ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DEV_QFREEZE ; 
 scalar_t__ CAM_REQ_CMP ; 
 int /*<<< orphan*/  RELSIM_ADJUST_OPENINGS ; 
 int /*<<< orphan*/  XPT_REL_SIMQ ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  xpt_action (union ccb*) ; 
 int /*<<< orphan*/  xpt_setup_ccb (TYPE_1__*,struct cam_path*,int) ; 

void agtiapi_adjust_queue_depth(struct cam_path *path, bit32 QueueDepth)
{
  struct ccb_relsim crs;
  xpt_setup_ccb(&crs.ccb_h, path, 5);
  crs.ccb_h.func_code = XPT_REL_SIMQ;
  crs.ccb_h.flags = CAM_DEV_QFREEZE;
  crs.release_flags = RELSIM_ADJUST_OPENINGS;
  crs.openings = QueueDepth;
  xpt_action((union ccb *)&crs);
  if(crs.ccb_h.status != CAM_REQ_CMP) {
                 printf("XPT_REL_SIMQ failed\n");
  }
}