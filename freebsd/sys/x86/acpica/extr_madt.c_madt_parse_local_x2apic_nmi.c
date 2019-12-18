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
struct TYPE_3__ {int /*<<< orphan*/  IntiFlags; int /*<<< orphan*/  Lint; int /*<<< orphan*/  Uid; } ;
typedef  TYPE_1__ ACPI_MADT_LOCAL_X2APIC_NMI ;

/* Variables and functions */
 int /*<<< orphan*/  madt_handle_local_nmi (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
madt_parse_local_x2apic_nmi(ACPI_MADT_LOCAL_X2APIC_NMI *nmi)
{

	madt_handle_local_nmi(nmi->Uid, nmi->Lint, nmi->IntiFlags);
}