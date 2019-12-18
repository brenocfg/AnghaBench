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
struct hpt_iop_hba {int flag; TYPE_1__* ops; int /*<<< orphan*/  pciunit; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* disable_intr ) (struct hpt_iop_hba*) ;} ;

/* Variables and functions */
 int EBUSY ; 
 int HPT_IOCTL_FLAG_OPEN ; 
 int /*<<< orphan*/  IOPMU_INBOUND_MSG0_SHUTDOWN ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ hptiop_send_sync_msg (struct hpt_iop_hba*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct hpt_iop_hba*) ; 

__attribute__((used)) static int hptiop_shutdown(device_t dev)
{
	struct hpt_iop_hba * hba = (struct hpt_iop_hba *)device_get_softc(dev);

	int error = 0;

	if (hba->flag & HPT_IOCTL_FLAG_OPEN) {
		device_printf(dev, "%d device is busy", hba->pciunit);
		return EBUSY;
	}

	hba->ops->disable_intr(hba);

	if (hptiop_send_sync_msg(hba, IOPMU_INBOUND_MSG0_SHUTDOWN, 60000))
		error = EBUSY;

	return error;
}