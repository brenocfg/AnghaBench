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
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  efidp ;
typedef  size_t UINTN ;
typedef  int /*<<< orphan*/  EFI_DEVICE_PATH_PROTOCOL ;

/* Variables and functions */
 size_t GetDevicePathSize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * UefiDevicePathLibConvertTextToDevicePath (char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 

ssize_t
efidp_parse_device_path(char *path, efidp out, size_t max)
{
	EFI_DEVICE_PATH_PROTOCOL *dp;
	UINTN len;

	dp = UefiDevicePathLibConvertTextToDevicePath (path);
	if (dp == NULL)
		return -1;
	len = GetDevicePathSize(dp);
	if (len > max) {
		free(dp);
		return -1;
	}
	memcpy(out, dp, len);
	free(dp);

	return len;
}