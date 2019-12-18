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
struct TYPE_3__ {int /*<<< orphan*/  max_transfer_size; } ;
struct pqisrc_softstate {TYPE_1__ pqi_cap; int /*<<< orphan*/  max_io_for_scsi_ml; } ;
struct cdev {struct pqisrc_softstate* si_drv1; } ;
typedef  TYPE_2__* pdriver_info ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_4__ {int /*<<< orphan*/  max_transfer_length; int /*<<< orphan*/  max_io; scalar_t__ max_targets; int /*<<< orphan*/  build_revision; int /*<<< orphan*/  release_version; int /*<<< orphan*/  minor_version; int /*<<< orphan*/  major_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_FUNC (char*,...) ; 
 int /*<<< orphan*/  PQISRC_DRIVER_MAJOR ; 
 int /*<<< orphan*/  PQISRC_DRIVER_MINOR ; 
 int /*<<< orphan*/  PQISRC_DRIVER_RELEASE ; 
 int /*<<< orphan*/  PQISRC_DRIVER_REVISION ; 
 scalar_t__ PQI_MAX_DEVICES ; 

__attribute__((used)) static void smartpqi_get_driver_info_ioctl(caddr_t udata, struct cdev *cdev)
{
	struct pqisrc_softstate *softs = cdev->si_drv1;
	pdriver_info driver_info = (pdriver_info)udata;

	DBG_FUNC("IN udata = %p cdev = %p\n", udata, cdev);

	driver_info->major_version = PQISRC_DRIVER_MAJOR;
	driver_info->minor_version = PQISRC_DRIVER_MINOR;
	driver_info->release_version = PQISRC_DRIVER_RELEASE;
	driver_info->build_revision = PQISRC_DRIVER_REVISION;
	driver_info->max_targets = PQI_MAX_DEVICES - 1;
	driver_info->max_io = softs->max_io_for_scsi_ml;
	driver_info->max_transfer_length = softs->pqi_cap.max_transfer_size;

	DBG_FUNC("OUT\n");
}