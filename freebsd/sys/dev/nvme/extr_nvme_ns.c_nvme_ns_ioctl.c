#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u_long ;
typedef  int /*<<< orphan*/  u_int ;
struct thread {int dummy; } ;
struct nvme_pt_command {int dummy; } ;
struct nvme_namespace {int /*<<< orphan*/  id; struct nvme_controller* ctrlr; } ;
struct nvme_get_nsid {int /*<<< orphan*/  nsid; int /*<<< orphan*/  cdev; } ;
struct nvme_controller {int /*<<< orphan*/  dev; } ;
struct cdev {struct nvme_namespace* si_drv1; } ;
typedef  int /*<<< orphan*/  off_t ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
#define  DIOCGMEDIASIZE 133 
#define  DIOCGSECTORSIZE 132 
 int ENOTTY ; 
#define  NVME_BIO_TEST 131 
#define  NVME_GET_NSID 130 
#define  NVME_IO_TEST 129 
#define  NVME_PASSTHROUGH_CMD 128 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int nvme_ctrlr_passthrough_cmd (struct nvme_controller*,struct nvme_pt_command*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_ns_get_sector_size (struct nvme_namespace*) ; 
 int /*<<< orphan*/  nvme_ns_get_size (struct nvme_namespace*) ; 
 int /*<<< orphan*/  nvme_ns_test (struct nvme_namespace*,int,scalar_t__) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
nvme_ns_ioctl(struct cdev *cdev, u_long cmd, caddr_t arg, int flag,
    struct thread *td)
{
	struct nvme_namespace			*ns;
	struct nvme_controller			*ctrlr;
	struct nvme_pt_command			*pt;

	ns = cdev->si_drv1;
	ctrlr = ns->ctrlr;

	switch (cmd) {
	case NVME_IO_TEST:
	case NVME_BIO_TEST:
		nvme_ns_test(ns, cmd, arg);
		break;
	case NVME_PASSTHROUGH_CMD:
		pt = (struct nvme_pt_command *)arg;
		return (nvme_ctrlr_passthrough_cmd(ctrlr, pt, ns->id, 
		    1 /* is_user_buffer */, 0 /* is_admin_cmd */));
	case NVME_GET_NSID:
	{
		struct nvme_get_nsid *gnsid = (struct nvme_get_nsid *)arg;
		strncpy(gnsid->cdev, device_get_nameunit(ctrlr->dev),
		    sizeof(gnsid->cdev));
		gnsid->nsid = ns->id;
		break;
	}
	case DIOCGMEDIASIZE:
		*(off_t *)arg = (off_t)nvme_ns_get_size(ns);
		break;
	case DIOCGSECTORSIZE:
		*(u_int *)arg = nvme_ns_get_sector_size(ns);
		break;
	default:
		return (ENOTTY);
	}

	return (0);
}