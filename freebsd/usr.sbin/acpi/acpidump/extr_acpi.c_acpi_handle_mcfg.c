#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int u_int ;
struct TYPE_6__ {int PciSegment; int StartBusNumber; int EndBusNumber; scalar_t__ Address; } ;
struct TYPE_5__ {int Length; } ;
typedef  int /*<<< orphan*/  ACPI_TABLE_MCFG ;
typedef  TYPE_1__ ACPI_TABLE_HEADER ;
typedef  TYPE_2__ ACPI_MCFG_ALLOCATION ;

/* Variables and functions */
 char* BEGIN_COMMENT ; 
 char* END_COMMENT ; 
 int /*<<< orphan*/  acpi_print_sdt (TYPE_1__*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
acpi_handle_mcfg(ACPI_TABLE_HEADER *sdp)
{
	ACPI_TABLE_MCFG *mcfg;
	ACPI_MCFG_ALLOCATION *alloc;
	u_int i, entries;

	printf(BEGIN_COMMENT);
	acpi_print_sdt(sdp);
	mcfg = (ACPI_TABLE_MCFG *)sdp;
	entries = (sdp->Length - sizeof(ACPI_TABLE_MCFG)) /
	    sizeof(ACPI_MCFG_ALLOCATION);
	alloc = (ACPI_MCFG_ALLOCATION *)(mcfg + 1);
	for (i = 0; i < entries; i++, alloc++) {
		printf("\n");
		printf("\tBase Address=0x%016jx\n", (uintmax_t)alloc->Address);
		printf("\tSegment Group=0x%04x\n", alloc->PciSegment);
		printf("\tStart Bus=%d\n", alloc->StartBusNumber);
		printf("\tEnd Bus=%d\n", alloc->EndBusNumber);
	}
	printf(END_COMMENT);
}