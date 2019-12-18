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
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int /*<<< orphan*/ * ACPI_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_TYPE_DEVICE ; 
 int /*<<< orphan*/  AE_ERROR ; 
 int /*<<< orphan*/  AcpiWalkNamespace (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * acpi_get_handle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_uhub_find_rh_cb ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ACPI_STATUS
acpi_uhub_find_rh(device_t dev, ACPI_HANDLE *ah)
{
	device_t grand;
	ACPI_HANDLE gah;

	*ah = NULL;
	grand = device_get_parent(device_get_parent(dev));

	if ((gah = acpi_get_handle(grand)) == NULL)
		return (AE_ERROR);

	return (AcpiWalkNamespace(ACPI_TYPE_DEVICE, gah, 1,
	    acpi_uhub_find_rh_cb, NULL, dev, ah));
}