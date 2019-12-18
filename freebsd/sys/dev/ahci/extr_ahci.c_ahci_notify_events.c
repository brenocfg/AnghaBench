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
typedef  int u_int32_t ;
struct cam_path {int dummy; } ;
struct ahci_channel {int caps; int /*<<< orphan*/  path; int /*<<< orphan*/  dev; int /*<<< orphan*/  r_mem; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_SCSI_AEN ; 
 int AHCI_CAP_SSNTF ; 
 int /*<<< orphan*/  AHCI_P_SNTF ; 
 int /*<<< orphan*/  ATA_OUTL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ CAM_REQ_CMP ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  xpt_async (int /*<<< orphan*/ ,struct cam_path*,int /*<<< orphan*/ *) ; 
 scalar_t__ xpt_create_path (struct cam_path**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_free_path (struct cam_path*) ; 
 int /*<<< orphan*/  xpt_path_path_id (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ahci_notify_events(struct ahci_channel *ch, u_int32_t status)
{
	struct cam_path *dpath;
	int i;

	if (ch->caps & AHCI_CAP_SSNTF)
		ATA_OUTL(ch->r_mem, AHCI_P_SNTF, status);
	if (bootverbose)
		device_printf(ch->dev, "SNTF 0x%04x\n", status);
	for (i = 0; i < 16; i++) {
		if ((status & (1 << i)) == 0)
			continue;
		if (xpt_create_path(&dpath, NULL,
		    xpt_path_path_id(ch->path), i, 0) == CAM_REQ_CMP) {
			xpt_async(AC_SCSI_AEN, dpath, NULL);
			xpt_free_path(dpath);
		}
	}
}