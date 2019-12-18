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
typedef  int /*<<< orphan*/  ACPI_TABLE_LPIT ;
typedef  int /*<<< orphan*/  ACPI_TABLE_HEADER ;

/* Variables and functions */
 char* BEGIN_COMMENT ; 
 char* END_COMMENT ; 
 int /*<<< orphan*/  acpi_print_lpit ; 
 int /*<<< orphan*/  acpi_print_sdt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_walk_lpit (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void
acpi_handle_lpit(ACPI_TABLE_HEADER *sdp)
{
	ACPI_TABLE_LPIT *lpit;

	printf(BEGIN_COMMENT);
	acpi_print_sdt(sdp);
	lpit = (ACPI_TABLE_LPIT *)sdp;
	acpi_walk_lpit(sdp, (lpit + 1), acpi_print_lpit);

	printf(END_COMMENT);
}