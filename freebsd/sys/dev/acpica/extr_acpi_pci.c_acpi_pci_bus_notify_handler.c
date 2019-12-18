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
typedef  void* device_t ;
typedef  int UINT32 ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;

/* Variables and functions */
#define  ACPI_NOTIFY_BUS_CHECK 128 
 int /*<<< orphan*/  BUS_RESCAN (void*) ; 
 int /*<<< orphan*/  Giant ; 
 int /*<<< orphan*/  device_printf (void*,char*,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
acpi_pci_bus_notify_handler(ACPI_HANDLE h, UINT32 notify, void *context)
{
	device_t dev;

	dev = context;

	switch (notify) {
	case ACPI_NOTIFY_BUS_CHECK:
		mtx_lock(&Giant);
		BUS_RESCAN(dev);
		mtx_unlock(&Giant);
		break;
	default:
		device_printf(dev, "unknown notify %#x\n", notify);
		break;
	}
}