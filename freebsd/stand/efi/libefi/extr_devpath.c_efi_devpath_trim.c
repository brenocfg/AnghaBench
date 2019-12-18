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
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int /*<<< orphan*/  EFI_DEVICE_PATH ;

/* Variables and functions */
 size_t DevicePathNodeLength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NextDevicePathNode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetDevicePathEndNode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * efi_devpath_last_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 

EFI_DEVICE_PATH *
efi_devpath_trim(EFI_DEVICE_PATH *devpath)
{
	EFI_DEVICE_PATH *node, *copy;
	size_t prefix, len;

	if ((node = efi_devpath_last_node(devpath)) == NULL)
		return (NULL);
	prefix = (UINT8 *)node - (UINT8 *)devpath;
	if (prefix == 0)
		return (NULL);
	len = prefix + DevicePathNodeLength(NextDevicePathNode(node));
	copy = malloc(len);
	if (copy != NULL) {
		memcpy(copy, devpath, prefix);
		node = (EFI_DEVICE_PATH *)((UINT8 *)copy + prefix);
		SetDevicePathEndNode(node);
	}
	return (copy);
}