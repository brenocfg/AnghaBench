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
struct TYPE_3__ {int /*<<< orphan*/  Address; int /*<<< orphan*/  Segment; } ;
typedef  TYPE_1__ ACPI_DMAR_HARDWARE_UNIT ;

/* Variables and functions */
 int /*<<< orphan*/  handle_drhd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
acpi_handle_dmar_drhd(ACPI_DMAR_HARDWARE_UNIT *drhd)
{

	handle_drhd(drhd->Segment, drhd->Address);
}