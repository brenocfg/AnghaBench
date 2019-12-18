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
typedef  int /*<<< orphan*/  u_long ;
typedef  int /*<<< orphan*/  ACPI_PHYSICAL_ADDRESS ;

/* Variables and functions */
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiFindRootPointer (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u_long
acpi_get_root_from_memory(void)
{
	ACPI_PHYSICAL_ADDRESS acpi_root;

	if (ACPI_SUCCESS(AcpiFindRootPointer(&acpi_root)))
		return (acpi_root);

	return (0);
}