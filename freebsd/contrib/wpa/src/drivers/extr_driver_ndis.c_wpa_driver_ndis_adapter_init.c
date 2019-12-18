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
struct wpa_driver_ndis_data {scalar_t__ ndisuio; } ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFile (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  DeviceIoControl (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int FILE_ATTRIBUTE_NORMAL ; 
 int FILE_FLAG_OVERLAPPED ; 
 int GENERIC_READ ; 
 int GENERIC_WRITE ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  IOCTL_NDISUIO_BIND_WAIT ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  NDISUIO_DEVICE_NAME ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 scalar_t__ driver_ndis_ndisuio_handle ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int wpa_driver_ndis_adapter_init(struct wpa_driver_ndis_data *drv)
{
#ifdef CONFIG_USE_NDISUIO
#ifndef _WIN32_WCE
#define NDISUIO_DEVICE_NAME TEXT("\\\\.\\\\Ndisuio")
	DWORD written;
#endif /* _WIN32_WCE */
	drv->ndisuio = CreateFile(NDISUIO_DEVICE_NAME,
				  GENERIC_READ | GENERIC_WRITE, 0, NULL,
				  OPEN_EXISTING,
				  FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
				  INVALID_HANDLE_VALUE);
	if (drv->ndisuio == INVALID_HANDLE_VALUE) {
		wpa_printf(MSG_ERROR, "NDIS: Failed to open connection to "
			   "NDISUIO: %d", (int) GetLastError());
		return -1;
	}
	driver_ndis_ndisuio_handle = drv->ndisuio;

#ifndef _WIN32_WCE
	if (!DeviceIoControl(drv->ndisuio, IOCTL_NDISUIO_BIND_WAIT, NULL, 0,
			     NULL, 0, &written, NULL)) {
		wpa_printf(MSG_ERROR, "NDIS: IOCTL_NDISUIO_BIND_WAIT failed: "
			   "%d", (int) GetLastError());
		CloseHandle(drv->ndisuio);
		drv->ndisuio = INVALID_HANDLE_VALUE;
		return -1;
	}
#endif /* _WIN32_WCE */

	return 0;
#else /* CONFIG_USE_NDISUIO */
	return 0;
#endif /* CONFIG_USE_NDISUIO */
}