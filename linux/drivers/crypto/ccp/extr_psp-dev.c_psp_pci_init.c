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
struct sp_device {int /*<<< orphan*/  dev; TYPE_1__* psp_data; } ;
struct TYPE_2__ {scalar_t__ sev_state; int /*<<< orphan*/  build; int /*<<< orphan*/  api_minor; int /*<<< orphan*/  api_major; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ SEV_STATE_UNINIT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* psp_master ; 
 int /*<<< orphan*/  psp_probe_timeout ; 
 int /*<<< orphan*/  psp_timeout ; 
 scalar_t__ sev_get_api_version () ; 
 int sev_platform_init (int*) ; 
 int /*<<< orphan*/  sev_platform_shutdown (int /*<<< orphan*/ *) ; 
 scalar_t__ sev_update_firmware (int /*<<< orphan*/ ) ; 
 scalar_t__ sev_version_greater_or_equal (int /*<<< orphan*/ ,int) ; 
 struct sp_device* sp_get_psp_master_device () ; 

void psp_pci_init(void)
{
	struct sp_device *sp;
	int error, rc;

	sp = sp_get_psp_master_device();
	if (!sp)
		return;

	psp_master = sp->psp_data;

	psp_timeout = psp_probe_timeout;

	if (sev_get_api_version())
		goto err;

	/*
	 * If platform is not in UNINIT state then firmware upgrade and/or
	 * platform INIT command will fail. These command require UNINIT state.
	 *
	 * In a normal boot we should never run into case where the firmware
	 * is not in UNINIT state on boot. But in case of kexec boot, a reboot
	 * may not go through a typical shutdown sequence and may leave the
	 * firmware in INIT or WORKING state.
	 */

	if (psp_master->sev_state != SEV_STATE_UNINIT) {
		sev_platform_shutdown(NULL);
		psp_master->sev_state = SEV_STATE_UNINIT;
	}

	if (sev_version_greater_or_equal(0, 15) &&
	    sev_update_firmware(psp_master->dev) == 0)
		sev_get_api_version();

	/* Initialize the platform */
	rc = sev_platform_init(&error);
	if (rc) {
		dev_err(sp->dev, "SEV: failed to INIT error %#x\n", error);
		return;
	}

	dev_info(sp->dev, "SEV API:%d.%d build:%d\n", psp_master->api_major,
		 psp_master->api_minor, psp_master->build);

	return;

err:
	psp_master = NULL;
}