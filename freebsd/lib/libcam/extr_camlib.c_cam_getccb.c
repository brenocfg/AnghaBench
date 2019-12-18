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
struct TYPE_2__ {int /*<<< orphan*/  target_lun; int /*<<< orphan*/  target_id; int /*<<< orphan*/  path_id; } ;
union ccb {TYPE_1__ ccb_h; } ;
struct ccb_hdr {int dummy; } ;
struct cam_device {int /*<<< orphan*/  target_lun; int /*<<< orphan*/  target_id; int /*<<< orphan*/  path_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 scalar_t__ malloc (int) ; 

union ccb *
cam_getccb(struct cam_device *dev)
{
	union ccb *ccb;

	ccb = (union ccb *)malloc(sizeof(union ccb));
	if (ccb != NULL) {
		bzero(&ccb->ccb_h, sizeof(struct ccb_hdr));
		ccb->ccb_h.path_id = dev->path_id;
		ccb->ccb_h.target_id = dev->target_id;
		ccb->ccb_h.target_lun = dev->target_lun;
	}

	return(ccb);
}