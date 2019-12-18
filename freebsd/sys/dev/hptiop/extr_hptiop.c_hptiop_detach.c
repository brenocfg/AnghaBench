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
struct hpt_iop_hba {int max_devices; int /*<<< orphan*/  pciunit; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  IOPMU_INBOUND_MSG0_STOP_BACKGROUND_TASK ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hptiop_lock_adapter (struct hpt_iop_hba*) ; 
 scalar_t__ hptiop_os_query_remove_device (struct hpt_iop_hba*,int) ; 
 int /*<<< orphan*/  hptiop_release_resource (struct hpt_iop_hba*) ; 
 scalar_t__ hptiop_send_sync_msg (struct hpt_iop_hba*,int /*<<< orphan*/ ,int) ; 
 int hptiop_shutdown (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hptiop_unlock_adapter (struct hpt_iop_hba*) ; 

__attribute__((used)) static int hptiop_detach(device_t dev)
{
	struct hpt_iop_hba * hba = (struct hpt_iop_hba *)device_get_softc(dev);
	int i;
	int error = EBUSY;

	hptiop_lock_adapter(hba);
	for (i = 0; i < hba->max_devices; i++)
		if (hptiop_os_query_remove_device(hba, i)) {
			device_printf(dev, "%d file system is busy. id=%d",
						hba->pciunit, i);
			goto out;
		}

	if ((error = hptiop_shutdown(dev)) != 0)
		goto out;
	if (hptiop_send_sync_msg(hba,
		IOPMU_INBOUND_MSG0_STOP_BACKGROUND_TASK, 60000))
		goto out;
	hptiop_unlock_adapter(hba);

	hptiop_release_resource(hba);
	return (0);
out:
	hptiop_unlock_adapter(hba);
	return error;
}