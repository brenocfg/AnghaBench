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
struct TYPE_2__ {int PartitionNumber; } ;
typedef  TYPE_1__ HARDDRIVE_DEVICE_PATH ;
typedef  int /*<<< orphan*/  EFI_DEVICE_PATH ;

/* Variables and functions */
 scalar_t__ DevicePathSubType (int /*<<< orphan*/ *) ; 
 scalar_t__ MEDIA_HARDDRIVE_DP ; 
 int /*<<< orphan*/ * efi_devpath_last_node (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
partition_number(EFI_DEVICE_PATH *devpath)
{
	EFI_DEVICE_PATH *md;
	HARDDRIVE_DEVICE_PATH *hd;

	md = efi_devpath_last_node(devpath);
	if (md == NULL)
		return (-1);
	if (DevicePathSubType(md) != MEDIA_HARDDRIVE_DP)
		return (-1);
	hd = (HARDDRIVE_DEVICE_PATH *)md;
	return (hd->PartitionNumber);
}