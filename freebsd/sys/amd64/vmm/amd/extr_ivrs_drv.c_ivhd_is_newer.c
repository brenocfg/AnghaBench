#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ DeviceId; scalar_t__ Type; } ;
typedef  TYPE_1__ ACPI_IVRS_HEADER ;

/* Variables and functions */
 scalar_t__ IVRS_TYPE_HARDWARE_EFR ; 
 scalar_t__ IVRS_TYPE_HARDWARE_LEGACY ; 
 scalar_t__ IVRS_TYPE_HARDWARE_MIXED ; 

__attribute__((used)) static bool
ivhd_is_newer(ACPI_IVRS_HEADER *old, ACPI_IVRS_HEADER  *new)
{
	/*
	 * Newer IVRS header type take precedence.
	 */
	if ((old->DeviceId == new->DeviceId) &&
		(old->Type == IVRS_TYPE_HARDWARE_LEGACY) &&
		((new->Type == IVRS_TYPE_HARDWARE_EFR) ||
		(new->Type == IVRS_TYPE_HARDWARE_MIXED))) {
		return (true);
	}

	return (false);
}