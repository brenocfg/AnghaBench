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

/* Variables and functions */
 int /*<<< orphan*/  ACPI_SERIAL_BEGIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_SERIAL_END (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_cmbat_get_bif (void*) ; 
 int /*<<< orphan*/  cmbat ; 

__attribute__((used)) static void
acpi_cmbat_get_bif_task(void *arg)
{

    ACPI_SERIAL_BEGIN(cmbat);
    acpi_cmbat_get_bif(arg);
    ACPI_SERIAL_END(cmbat);
}