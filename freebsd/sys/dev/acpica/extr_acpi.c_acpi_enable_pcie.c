#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ PciSegment; int /*<<< orphan*/  EndBusNumber; int /*<<< orphan*/  StartBusNumber; int /*<<< orphan*/  Address; } ;
struct TYPE_4__ {int Length; } ;
typedef  int /*<<< orphan*/  ACPI_TABLE_MCFG ;
typedef  TYPE_1__ ACPI_TABLE_HEADER ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_2__ ACPI_MCFG_ALLOCATION ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_SIG_MCFG ; 
 int /*<<< orphan*/  AcpiGetTable (int /*<<< orphan*/ ,int,TYPE_1__**) ; 
 int /*<<< orphan*/  pcie_cfgregopen (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
acpi_enable_pcie(void)
{
#if defined(__i386__) || defined(__amd64__)
	ACPI_TABLE_HEADER *hdr;
	ACPI_MCFG_ALLOCATION *alloc, *end;
	ACPI_STATUS status;

	status = AcpiGetTable(ACPI_SIG_MCFG, 1, &hdr);
	if (ACPI_FAILURE(status))
		return;

	end = (ACPI_MCFG_ALLOCATION *)((char *)hdr + hdr->Length);
	alloc = (ACPI_MCFG_ALLOCATION *)((ACPI_TABLE_MCFG *)hdr + 1);
	while (alloc < end) {
		if (alloc->PciSegment == 0) {
			pcie_cfgregopen(alloc->Address, alloc->StartBusNumber,
			    alloc->EndBusNumber);
			return;
		}
		alloc++;
	}
#endif
}