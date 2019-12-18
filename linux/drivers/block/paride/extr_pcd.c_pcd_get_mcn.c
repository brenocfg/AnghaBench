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
struct cdrom_mcn {scalar_t__* medium_catalog_number; } ;
struct cdrom_device_info {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int EIO ; 
 int GPCMD_READ_SUBCHANNEL ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,char*,int) ; 
 scalar_t__ pcd_atapi (int /*<<< orphan*/ ,char*,int,char*,char*) ; 

__attribute__((used)) static int pcd_get_mcn(struct cdrom_device_info *cdi, struct cdrom_mcn *mcn)
{
	char cmd[12] =
	    { GPCMD_READ_SUBCHANNEL, 0, 0x40, 2, 0, 0, 0, 0, 24, 0, 0, 0 };
	char buffer[32];

	if (pcd_atapi(cdi->handle, cmd, 24, buffer, "get mcn"))
		return -EIO;

	memcpy(mcn->medium_catalog_number, buffer + 9, 13);
	mcn->medium_catalog_number[13] = 0;

	return 0;
}