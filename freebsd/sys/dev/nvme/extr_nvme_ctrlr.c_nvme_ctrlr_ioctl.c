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
typedef  int u_long ;
struct thread {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  nsid; } ;
struct nvme_pt_command {TYPE_1__ cmd; } ;
struct nvme_get_nsid {int /*<<< orphan*/  nsid; int /*<<< orphan*/  cdev; } ;
struct nvme_controller {int /*<<< orphan*/  dev; } ;
struct cdev {struct nvme_controller* si_drv1; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int ENOTTY ; 
#define  NVME_GET_NSID 130 
#define  NVME_PASSTHROUGH_CMD 129 
#define  NVME_RESET_CONTROLLER 128 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32toh (int /*<<< orphan*/ ) ; 
 int nvme_ctrlr_passthrough_cmd (struct nvme_controller*,struct nvme_pt_command*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  nvme_ctrlr_reset (struct nvme_controller*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
nvme_ctrlr_ioctl(struct cdev *cdev, u_long cmd, caddr_t arg, int flag,
    struct thread *td)
{
	struct nvme_controller			*ctrlr;
	struct nvme_pt_command			*pt;

	ctrlr = cdev->si_drv1;

	switch (cmd) {
	case NVME_RESET_CONTROLLER:
		nvme_ctrlr_reset(ctrlr);
		break;
	case NVME_PASSTHROUGH_CMD:
		pt = (struct nvme_pt_command *)arg;
		return (nvme_ctrlr_passthrough_cmd(ctrlr, pt, le32toh(pt->cmd.nsid),
		    1 /* is_user_buffer */, 1 /* is_admin_cmd */));
	case NVME_GET_NSID:
	{
		struct nvme_get_nsid *gnsid = (struct nvme_get_nsid *)arg;
		strncpy(gnsid->cdev, device_get_nameunit(ctrlr->dev),
		    sizeof(gnsid->cdev));
		gnsid->nsid = 0;
		break;
	}
	default:
		return (ENOTTY);
	}

	return (0);
}