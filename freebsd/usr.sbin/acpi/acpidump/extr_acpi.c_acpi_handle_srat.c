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
struct TYPE_3__ {int TableRevision; } ;
typedef  TYPE_1__ ACPI_TABLE_SRAT ;
typedef  int /*<<< orphan*/  ACPI_TABLE_HEADER ;

/* Variables and functions */
 char* BEGIN_COMMENT ; 
 char* END_COMMENT ; 
 int /*<<< orphan*/  acpi_print_sdt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_print_srat ; 
 int /*<<< orphan*/  acpi_walk_subtables (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
acpi_handle_srat(ACPI_TABLE_HEADER *sdp)
{
	ACPI_TABLE_SRAT *srat;

	printf(BEGIN_COMMENT);
	acpi_print_sdt(sdp);
	srat = (ACPI_TABLE_SRAT *)sdp;
	printf("\tTable Revision=%d\n", srat->TableRevision);
	acpi_walk_subtables(sdp, (srat + 1), acpi_print_srat);
	printf(END_COMMENT);
}