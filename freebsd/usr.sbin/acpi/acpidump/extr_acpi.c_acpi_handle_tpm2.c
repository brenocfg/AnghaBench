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
struct TYPE_2__ {int StartMethod; int /*<<< orphan*/  ControlAddress; } ;
typedef  TYPE_1__ ACPI_TABLE_TPM2 ;
typedef  int /*<<< orphan*/  ACPI_TABLE_HEADER ;

/* Variables and functions */
 char* BEGIN_COMMENT ; 
 char* END_COMMENT ; 
 int /*<<< orphan*/  acpi_print_sdt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void acpi_handle_tpm2(ACPI_TABLE_HEADER *sdp)
{
	ACPI_TABLE_TPM2 *tpm2;
	
	printf (BEGIN_COMMENT);
	acpi_print_sdt(sdp);
	tpm2 = (ACPI_TABLE_TPM2 *) sdp;
	printf ("\t\tControlArea=%jx\n", tpm2->ControlAddress);
	printf ("\t\tStartMethod=%x\n", tpm2->StartMethod);	
	printf (END_COMMENT);
}