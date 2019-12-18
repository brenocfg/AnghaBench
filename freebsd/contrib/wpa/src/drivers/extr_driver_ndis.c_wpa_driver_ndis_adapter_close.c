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
struct wpa_driver_ndis_data {scalar_t__ ndisuio; scalar_t__ adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  PacketCloseAdapter (scalar_t__) ; 
 scalar_t__ driver_ndis_ndisuio_handle ; 

__attribute__((used)) static void wpa_driver_ndis_adapter_close(struct wpa_driver_ndis_data *drv)
{
#ifdef CONFIG_USE_NDISUIO
	driver_ndis_ndisuio_handle = INVALID_HANDLE_VALUE;
	if (drv->ndisuio != INVALID_HANDLE_VALUE)
		CloseHandle(drv->ndisuio);
#else /* CONFIG_USE_NDISUIO */
	if (drv->adapter)
		PacketCloseAdapter(drv->adapter);
#endif /* CONFIG_USE_NDISUIO */
}