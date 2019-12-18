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
typedef  int /*<<< orphan*/ * ACPI_HANDLE ;

/* Variables and functions */
 scalar_t__ ACPI_MATCHHID_NOMATCH ; 
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
 int /*<<< orphan*/  XHCI_HC_DEVSTR ; 
 scalar_t__ acpi_MatchHid (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * acpi_get_handle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
generic_xhci_acpi_probe(device_t dev)
{
	ACPI_HANDLE h;

	if ((h = acpi_get_handle(dev)) == NULL ||
	    acpi_MatchHid(h, "PNP0D10") == ACPI_MATCHHID_NOMATCH)
		return (ENXIO);

	device_set_desc(dev, XHCI_HC_DEVSTR);

	return (BUS_PROBE_DEFAULT);
}