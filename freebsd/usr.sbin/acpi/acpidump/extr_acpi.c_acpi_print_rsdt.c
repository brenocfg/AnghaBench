#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uintmax_t ;
struct TYPE_8__ {int Length; } ;
struct TYPE_7__ {int /*<<< orphan*/ * TableOffsetEntry; } ;
struct TYPE_6__ {int /*<<< orphan*/ * TableOffsetEntry; } ;
typedef  TYPE_1__ ACPI_TABLE_XSDT ;
typedef  TYPE_2__ ACPI_TABLE_RSDT ;
typedef  TYPE_3__ ACPI_TABLE_HEADER ;

/* Variables and functions */
 char* BEGIN_COMMENT ; 
 char* END_COMMENT ; 
 int /*<<< orphan*/  acpi_print_sdt (TYPE_3__*) ; 
 int addr_size ; 
 int le32toh (int /*<<< orphan*/ ) ; 
 scalar_t__ le64toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
acpi_print_rsdt(ACPI_TABLE_HEADER *rsdp)
{
	ACPI_TABLE_RSDT *rsdt;
	ACPI_TABLE_XSDT *xsdt;
	int	i, entries;

	rsdt = (ACPI_TABLE_RSDT *)rsdp;
	xsdt = (ACPI_TABLE_XSDT *)rsdp;
	printf(BEGIN_COMMENT);
	acpi_print_sdt(rsdp);
	entries = (rsdp->Length - sizeof(ACPI_TABLE_HEADER)) / addr_size;
	printf("\tEntries={ ");
	for (i = 0; i < entries; i++) {
		if (i > 0)
			printf(", ");
		if (addr_size == 4)
			printf("0x%08x", le32toh(rsdt->TableOffsetEntry[i]));
		else
			printf("0x%016jx",
			    (uintmax_t)le64toh(xsdt->TableOffsetEntry[i]));
	}
	printf(" }\n");
	printf(END_COMMENT);
}