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
typedef  int /*<<< orphan*/  u8 ;
struct wpa_driver_ndis_data {int /*<<< orphan*/ * adapter; scalar_t__* ifname; int /*<<< orphan*/  ndisuio; } ;
typedef  int /*<<< orphan*/  ifname ;
typedef  int WCHAR ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeviceIoControl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  IOCTL_NDISUIO_OPEN_DEVICE ; 
 int MAX_NDIS_DEVICE_NAME_LEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/ * PacketOpenAdapter (char*) ; 
 int /*<<< orphan*/  os_snprintf (char*,int,char*,scalar_t__*) ; 
 size_t os_strlen (scalar_t__*) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int wpa_driver_ndis_adapter_open(struct wpa_driver_ndis_data *drv)
{
#ifdef CONFIG_USE_NDISUIO
	DWORD written;
#define MAX_NDIS_DEVICE_NAME_LEN 256
	WCHAR ifname[MAX_NDIS_DEVICE_NAME_LEN];
	size_t len, i, pos;
	const char *prefix = "\\DEVICE\\";

#ifdef _WIN32_WCE
	pos = 0;
#else /* _WIN32_WCE */
	pos = 8;
#endif /* _WIN32_WCE */
	len = pos + os_strlen(drv->ifname);
	if (len >= MAX_NDIS_DEVICE_NAME_LEN)
		return -1;
	for (i = 0; i < pos; i++)
		ifname[i] = (WCHAR) prefix[i];
	for (i = pos; i < len; i++)
		ifname[i] = (WCHAR) drv->ifname[i - pos];
	ifname[i] = L'\0';

	if (!DeviceIoControl(drv->ndisuio, IOCTL_NDISUIO_OPEN_DEVICE,
			     ifname, len * sizeof(WCHAR), NULL, 0, &written,
			     NULL)) {
		wpa_printf(MSG_ERROR, "NDIS: IOCTL_NDISUIO_OPEN_DEVICE "
			   "failed: %d", (int) GetLastError());
		wpa_hexdump_ascii(MSG_DEBUG, "NDIS: ifname",
				  (const u8 *) ifname, len * sizeof(WCHAR));
		CloseHandle(drv->ndisuio);
		drv->ndisuio = INVALID_HANDLE_VALUE;
		return -1;
	}

	wpa_printf(MSG_DEBUG, "NDIS: Opened NDISUIO device successfully");

	return 0;
#else /* CONFIG_USE_NDISUIO */
	char ifname[128];
	os_snprintf(ifname, sizeof(ifname), "\\Device\\NPF_%s", drv->ifname);
	drv->adapter = PacketOpenAdapter(ifname);
	if (drv->adapter == NULL) {
		wpa_printf(MSG_DEBUG, "NDIS: PacketOpenAdapter failed for "
			   "'%s'", ifname);
		return -1;
	}
	return 0;
#endif /* CONFIG_USE_NDISUIO */
}