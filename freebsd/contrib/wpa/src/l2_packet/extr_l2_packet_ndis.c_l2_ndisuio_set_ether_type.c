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
typedef  int /*<<< orphan*/  proto ;
typedef  int /*<<< orphan*/  USHORT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  DeviceIoControl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  IOCTL_NDISUIO_SET_ETHER_TYPE ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  driver_ndis_get_ndisuio_handle () ; 
 int /*<<< orphan*/  htons (unsigned short) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int l2_ndisuio_set_ether_type(unsigned short protocol)
{
	USHORT proto = htons(protocol);
	DWORD written;

	if (!DeviceIoControl(driver_ndis_get_ndisuio_handle(),
			     IOCTL_NDISUIO_SET_ETHER_TYPE, &proto,
			     sizeof(proto), NULL, 0, &written, NULL)) {
		wpa_printf(MSG_ERROR, "L2(NDISUIO): "
			   "IOCTL_NDISUIO_SET_ETHER_TYPE failed: %d",
			   (int) GetLastError());
		return -1;
	}

	return 0;
}