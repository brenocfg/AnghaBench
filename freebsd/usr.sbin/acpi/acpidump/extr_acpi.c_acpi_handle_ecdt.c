#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int Uid; int Gpe; char* Id; int /*<<< orphan*/  Data; int /*<<< orphan*/  Control; } ;
typedef  int /*<<< orphan*/  ACPI_TABLE_HEADER ;
typedef  TYPE_1__ ACPI_TABLE_ECDT ;

/* Variables and functions */
 char* BEGIN_COMMENT ; 
 char* END_COMMENT ; 
 int /*<<< orphan*/  acpi_print_gas (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_print_sdt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
acpi_handle_ecdt(ACPI_TABLE_HEADER *sdp)
{
	ACPI_TABLE_ECDT *ecdt;

	printf(BEGIN_COMMENT);
	acpi_print_sdt(sdp);
	ecdt = (ACPI_TABLE_ECDT *)sdp;
	printf("\tEC_CONTROL=");
	acpi_print_gas(&ecdt->Control);
	printf("\n\tEC_DATA=");
	acpi_print_gas(&ecdt->Data);
	printf("\n\tUID=%#x, ", ecdt->Uid);
	printf("GPE_BIT=%#x\n", ecdt->Gpe);
	printf("\tEC_ID=%s\n", ecdt->Id);
	printf(END_COMMENT);
}