#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* index; int status; char* periph_name; int unit_number; int generation; } ;
struct TYPE_3__ {int retry_count; int /*<<< orphan*/  flags; int /*<<< orphan*/  func_code; } ;
union ccb {TYPE_2__ cgdl; TYPE_1__ ccb_h; } ;
struct cam_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DIR_NONE ; 
#define  CAM_GDEVLIST_ERROR 131 
#define  CAM_GDEVLIST_LAST_DEVICE 130 
#define  CAM_GDEVLIST_LIST_CHANGED 129 
#define  CAM_GDEVLIST_MORE_DEVS 128 
 int /*<<< orphan*/  XPT_GDEVLIST ; 
 int /*<<< orphan*/  cam_freeccb (union ccb*) ; 
 union ccb* cam_getccb (struct cam_device*) ; 
 scalar_t__ cam_send_ccb (struct cam_device*,union ccb*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int,int,char*,char*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static int
getdevlist(struct cam_device *device)
{
	union ccb *ccb;
	char status[32];
	int error = 0;

	ccb = cam_getccb(device);

	ccb->ccb_h.func_code = XPT_GDEVLIST;
	ccb->ccb_h.flags = CAM_DIR_NONE;
	ccb->ccb_h.retry_count = 1;
	ccb->cgdl.index = 0;
	ccb->cgdl.status = CAM_GDEVLIST_MORE_DEVS;
	while (ccb->cgdl.status == CAM_GDEVLIST_MORE_DEVS) {
		if (cam_send_ccb(device, ccb) < 0) {
			warn("error getting device list");
			cam_freeccb(ccb);
			return (1);
		}

		status[0] = '\0';

		switch (ccb->cgdl.status) {
			case CAM_GDEVLIST_MORE_DEVS:
				strcpy(status, "MORE");
				break;
			case CAM_GDEVLIST_LAST_DEVICE:
				strcpy(status, "LAST");
				break;
			case CAM_GDEVLIST_LIST_CHANGED:
				strcpy(status, "CHANGED");
				break;
			case CAM_GDEVLIST_ERROR:
				strcpy(status, "ERROR");
				error = 1;
				break;
		}

		fprintf(stdout, "%s%d:  generation: %d index: %d status: %s\n",
			ccb->cgdl.periph_name,
			ccb->cgdl.unit_number,
			ccb->cgdl.generation,
			ccb->cgdl.index,
			status);

		/*
		 * If the list has changed, we need to start over from the
		 * beginning.
		 */
		if (ccb->cgdl.status == CAM_GDEVLIST_LIST_CHANGED)
			ccb->cgdl.index = 0;
	}

	cam_freeccb(ccb);

	return (error);
}