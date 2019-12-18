#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ PstateControl; int /*<<< orphan*/  SmiCommand; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_UNLOCK (int /*<<< orphan*/ ) ; 
 TYPE_1__ AcpiGbl_FADT ; 
 int /*<<< orphan*/  AcpiOsWritePort (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  acpi ; 

__attribute__((used)) static void
acpi_px_startup(void *arg)
{

	/* Signal to the platform that we are taking over CPU control. */
	if (AcpiGbl_FADT.PstateControl == 0)
		return;
	ACPI_LOCK(acpi);
	AcpiOsWritePort(AcpiGbl_FADT.SmiCommand, AcpiGbl_FADT.PstateControl, 8);
	ACPI_UNLOCK(acpi);
}