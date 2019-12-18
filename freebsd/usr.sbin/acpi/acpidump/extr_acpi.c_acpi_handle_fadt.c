#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int Length; int /*<<< orphan*/  Signature; } ;
struct TYPE_11__ {int /*<<< orphan*/  XDsdt; int /*<<< orphan*/  Dsdt; int /*<<< orphan*/  XFacs; int /*<<< orphan*/  Facs; } ;
struct TYPE_10__ {int /*<<< orphan*/  Length; } ;
typedef  TYPE_1__ ACPI_TABLE_HEADER ;
typedef  TYPE_2__ ACPI_TABLE_FADT ;
typedef  TYPE_3__ ACPI_TABLE_FACS ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_SIG_FACS ; 
 scalar_t__ acpi_checksum (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int acpi_get_fadt_revision (TYPE_2__*) ; 
 scalar_t__ acpi_map_sdt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_print_dsdt (TYPE_1__*) ; 
 int /*<<< orphan*/  acpi_print_facs (TYPE_3__*) ; 
 int /*<<< orphan*/  acpi_print_fadt (TYPE_1__*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
acpi_handle_fadt(ACPI_TABLE_HEADER *sdp)
{
	ACPI_TABLE_HEADER *dsdp;
	ACPI_TABLE_FACS	*facs;
	ACPI_TABLE_FADT *fadt;
	int		fadt_revision;

	fadt = (ACPI_TABLE_FADT *)sdp;
	acpi_print_fadt(sdp);

	fadt_revision = acpi_get_fadt_revision(fadt);
	if (fadt_revision == 1)
		facs = (ACPI_TABLE_FACS *)acpi_map_sdt(fadt->Facs);
	else
		facs = (ACPI_TABLE_FACS *)acpi_map_sdt(fadt->XFacs);
	if (memcmp(facs->Signature, ACPI_SIG_FACS, 4) != 0 || facs->Length < 64)
		errx(1, "FACS is corrupt");
	acpi_print_facs(facs);

	if (fadt_revision == 1)
		dsdp = (ACPI_TABLE_HEADER *)acpi_map_sdt(fadt->Dsdt);
	else
		dsdp = (ACPI_TABLE_HEADER *)acpi_map_sdt(fadt->XDsdt);
	if (acpi_checksum(dsdp, dsdp->Length))
		errx(1, "DSDT is corrupt");
	acpi_print_dsdt(dsdp);
}