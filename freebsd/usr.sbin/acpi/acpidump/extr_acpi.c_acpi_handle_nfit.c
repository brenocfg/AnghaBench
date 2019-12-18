#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ACPI_TABLE_NFIT ;
typedef  int /*<<< orphan*/  ACPI_TABLE_HEADER ;

/* Variables and functions */
 char* BEGIN_COMMENT ; 
 char* END_COMMENT ; 
 int /*<<< orphan*/  acpi_print_nfit ; 
 int /*<<< orphan*/  acpi_print_sdt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_walk_nfit (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void
acpi_handle_nfit(ACPI_TABLE_HEADER *sdp)
{
	ACPI_TABLE_NFIT *nfit;

	printf(BEGIN_COMMENT);
	acpi_print_sdt(sdp);
	nfit = (ACPI_TABLE_NFIT *)sdp;
	acpi_walk_nfit(sdp, (nfit + 1), acpi_print_nfit);
	printf(END_COMMENT);
}