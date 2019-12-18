#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int priority; } ;
struct TYPE_6__ {int target_id; int timeout; int status; TYPE_2__ pinfo; scalar_t__ target_lun; int /*<<< orphan*/  func_code; int /*<<< orphan*/  path_id; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
union ccb {TYPE_3__ ccb_h; TYPE_1__ crcn; } ;
typedef  int /*<<< orphan*/  path_id_t ;
typedef  int /*<<< orphan*/  ccb ;

/* Variables and functions */
 int /*<<< orphan*/  CAMIOCOMMAND ; 
 int /*<<< orphan*/  CAM_FLAG_NONE ; 
 scalar_t__ CAM_LUN_WILDCARD ; 
 int CAM_REQ_CMP ; 
 int CAM_STATUS_MASK ; 
 int CAM_TARGET_WILDCARD ; 
 int EINVAL ; 
 int EIO ; 
 int ENXIO ; 
 int /*<<< orphan*/  XPT_SCAN_BUS ; 
 int /*<<< orphan*/  XPT_SCAN_LUN ; 
 int /*<<< orphan*/  bzero (union ccb*,int) ; 
 int errno ; 
 int fetch_path_id (int /*<<< orphan*/ *) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union ccb*) ; 
 int /*<<< orphan*/  warnx (char*,int) ; 
 scalar_t__ xpt_open () ; 
 int /*<<< orphan*/  xptfd ; 

int
mpt_rescan_bus(int bus, int id)
{
	union ccb ccb;
	path_id_t path_id;
	int error;

	/* mpt(4) only handles devices on bus 0. */
	if (bus != -1 && bus != 0)
		return (EINVAL);

	if (xpt_open() < 0)
		return (ENXIO);

	error = fetch_path_id(&path_id);
	if (error)
		return (error);

	/* Perform the actual rescan. */
	bzero(&ccb, sizeof(ccb));
	ccb.ccb_h.path_id = path_id;
	if (id == -1) {
		ccb.ccb_h.func_code = XPT_SCAN_BUS;
		ccb.ccb_h.target_id = CAM_TARGET_WILDCARD;
		ccb.ccb_h.target_lun = CAM_LUN_WILDCARD;
		ccb.ccb_h.timeout = 5000;
	} else {
		ccb.ccb_h.func_code = XPT_SCAN_LUN;
		ccb.ccb_h.target_id = id;
		ccb.ccb_h.target_lun = 0;
	}
	ccb.crcn.flags = CAM_FLAG_NONE;

	/* Run this at a low priority. */
	ccb.ccb_h.pinfo.priority = 5;

	if (ioctl(xptfd, CAMIOCOMMAND, &ccb) == -1)
		return (errno);

	if ((ccb.ccb_h.status & CAM_STATUS_MASK) != CAM_REQ_CMP) {
		warnx("mpt_rescan_bus rescan got CAM error %#x\n",
		    ccb.ccb_h.status & CAM_STATUS_MASK);
		return (EIO);
	}

	return (0);
}