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
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_SetInteger (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  acpi_get_handle (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
acpi_dock_execute_lck(device_t dev, int lock)
{
	ACPI_HANDLE	h;

	h = acpi_get_handle(dev);
	acpi_SetInteger(h, "_LCK", lock);
}