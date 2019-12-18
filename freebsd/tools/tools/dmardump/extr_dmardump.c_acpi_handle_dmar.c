#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int Length; } ;
typedef  TYPE_1__ ACPI_TABLE_HEADER ;
typedef  int /*<<< orphan*/  ACPI_TABLE_DMAR ;

/* Variables and functions */
 int acpi_handle_dmar_remapping_structure (char*,int) ; 

__attribute__((used)) static void
acpi_handle_dmar(ACPI_TABLE_HEADER *sdp)
{
	char *cp;
	int remaining, consumed;
	ACPI_TABLE_DMAR *dmar;

	dmar = (ACPI_TABLE_DMAR *)sdp;
	remaining = sdp->Length - sizeof(ACPI_TABLE_DMAR);
	while (remaining > 0) {
		cp = (char *)sdp + sdp->Length - remaining;
		consumed = acpi_handle_dmar_remapping_structure(cp, remaining);
		if (consumed <= 0)
			break;
		else
			remaining -= consumed;
	}
}