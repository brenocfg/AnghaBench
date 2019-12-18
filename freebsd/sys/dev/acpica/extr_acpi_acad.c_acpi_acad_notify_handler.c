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
typedef  scalar_t__ device_t ;
typedef  int UINT32 ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;

/* Variables and functions */
#define  ACPI_NOTIFY_BUS_CHECK 130 
#define  ACPI_NOTIFY_DEVICE_CHECK 129 
#define  ACPI_POWERSOURCE_STAT_CHANGE 128 
 int /*<<< orphan*/  AcpiOsExecute (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  OSL_NOTIFY_HANDLER ; 
 int /*<<< orphan*/  acpi_acad_get_status ; 
 int /*<<< orphan*/  device_printf (scalar_t__,char*,int) ; 

__attribute__((used)) static void
acpi_acad_notify_handler(ACPI_HANDLE h, UINT32 notify, void *context)
{
    device_t dev;

    dev = (device_t)context;
    switch (notify) {
    case ACPI_NOTIFY_BUS_CHECK:
    case ACPI_NOTIFY_DEVICE_CHECK:
    case ACPI_POWERSOURCE_STAT_CHANGE:
	/* Temporarily.  It is better to notify policy manager */
	AcpiOsExecute(OSL_NOTIFY_HANDLER, acpi_acad_get_status, context);
	break;
    default:
	device_printf(dev, "unknown notify %#x\n", notify);
	break;
    }
}