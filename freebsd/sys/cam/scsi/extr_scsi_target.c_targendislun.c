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
struct TYPE_2__ {int status; int /*<<< orphan*/  func_code; } ;
struct ccb_en_lun {int grp6_len; int grp7_len; int enable; TYPE_1__ ccb_h; } ;
struct cam_path {int dummy; } ;
typedef  int cam_status ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_PRIORITY_NORMAL ; 
 int CAM_REQ_CMP ; 
 int CAM_STATUS_MASK ; 
 int /*<<< orphan*/  XPT_EN_LUN ; 
 int /*<<< orphan*/  xpt_action (union ccb*) ; 
 int /*<<< orphan*/  xpt_print (struct cam_path*,char*,char*,int) ; 
 int /*<<< orphan*/  xpt_setup_ccb (TYPE_1__*,struct cam_path*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static cam_status
targendislun(struct cam_path *path, int enable, int grp6_len, int grp7_len)
{
	struct ccb_en_lun en_ccb;
	cam_status	  status;

	/* Tell the lun to begin answering selects */
	xpt_setup_ccb(&en_ccb.ccb_h, path, CAM_PRIORITY_NORMAL);
	en_ccb.ccb_h.func_code = XPT_EN_LUN;
	/* Don't need support for any vendor specific commands */
	en_ccb.grp6_len = grp6_len;
	en_ccb.grp7_len = grp7_len;
	en_ccb.enable = enable ? 1 : 0;
	xpt_action((union ccb *)&en_ccb);
	status = en_ccb.ccb_h.status & CAM_STATUS_MASK;
	if (status != CAM_REQ_CMP) {
		xpt_print(path, "%sable lun CCB rejected, status %#x\n",
		    enable ? "en" : "dis", status);
	}
	return (status);
}