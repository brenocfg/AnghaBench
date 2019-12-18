#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_offset_t ;
struct TYPE_23__ {int Length; int /*<<< orphan*/  Signature; } ;
struct TYPE_22__ {int /*<<< orphan*/ * TableOffsetEntry; } ;
struct TYPE_21__ {int /*<<< orphan*/ * TableOffsetEntry; } ;
typedef  TYPE_1__ ACPI_TABLE_XSDT ;
typedef  TYPE_2__ ACPI_TABLE_RSDT ;
typedef  TYPE_3__ ACPI_TABLE_HEADER ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_SIG_DMAR ; 
 int /*<<< orphan*/  ACPI_SIG_ECDT ; 
 int /*<<< orphan*/  ACPI_SIG_FADT ; 
 int /*<<< orphan*/  ACPI_SIG_HPET ; 
 int /*<<< orphan*/  ACPI_SIG_LPIT ; 
 int /*<<< orphan*/  ACPI_SIG_MADT ; 
 int /*<<< orphan*/  ACPI_SIG_MCFG ; 
 int /*<<< orphan*/  ACPI_SIG_NFIT ; 
 int /*<<< orphan*/  ACPI_SIG_SLIT ; 
 int /*<<< orphan*/  ACPI_SIG_SRAT ; 
 int /*<<< orphan*/  ACPI_SIG_TCPA ; 
 int /*<<< orphan*/  ACPI_SIG_TPM2 ; 
 int /*<<< orphan*/  ACPI_SIG_WDDT ; 
 char* BEGIN_COMMENT ; 
 char* END_COMMENT ; 
 scalar_t__ acpi_checksum (TYPE_3__*,int) ; 
 int /*<<< orphan*/  acpi_handle_dmar (TYPE_3__*) ; 
 int /*<<< orphan*/  acpi_handle_ecdt (TYPE_3__*) ; 
 int /*<<< orphan*/  acpi_handle_fadt (TYPE_3__*) ; 
 int /*<<< orphan*/  acpi_handle_hpet (TYPE_3__*) ; 
 int /*<<< orphan*/  acpi_handle_lpit (TYPE_3__*) ; 
 int /*<<< orphan*/  acpi_handle_madt (TYPE_3__*) ; 
 int /*<<< orphan*/  acpi_handle_mcfg (TYPE_3__*) ; 
 int /*<<< orphan*/  acpi_handle_nfit (TYPE_3__*) ; 
 int /*<<< orphan*/  acpi_handle_slit (TYPE_3__*) ; 
 int /*<<< orphan*/  acpi_handle_srat (TYPE_3__*) ; 
 int /*<<< orphan*/  acpi_handle_tcpa (TYPE_3__*) ; 
 int /*<<< orphan*/  acpi_handle_tpm2 (TYPE_3__*) ; 
 int /*<<< orphan*/  acpi_handle_wddt (TYPE_3__*) ; 
 scalar_t__ acpi_map_sdt (scalar_t__) ; 
 int /*<<< orphan*/  acpi_print_rsdt (TYPE_3__*) ; 
 int /*<<< orphan*/  acpi_print_sdt (TYPE_3__*) ; 
 int addr_size ; 
 scalar_t__ le32toh (int /*<<< orphan*/ ) ; 
 scalar_t__ le64toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  warnx (char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
acpi_handle_rsdt(ACPI_TABLE_HEADER *rsdp)
{
	ACPI_TABLE_HEADER *sdp;
	ACPI_TABLE_RSDT *rsdt;
	ACPI_TABLE_XSDT *xsdt;
	vm_offset_t addr;
	int entries, i;

	acpi_print_rsdt(rsdp);
	rsdt = (ACPI_TABLE_RSDT *)rsdp;
	xsdt = (ACPI_TABLE_XSDT *)rsdp;
	entries = (rsdp->Length - sizeof(ACPI_TABLE_HEADER)) / addr_size;
	for (i = 0; i < entries; i++) {
		if (addr_size == 4)
			addr = le32toh(rsdt->TableOffsetEntry[i]);
		else
			addr = le64toh(xsdt->TableOffsetEntry[i]);
		if (addr == 0)
			continue;
		sdp = (ACPI_TABLE_HEADER *)acpi_map_sdt(addr);
		if (acpi_checksum(sdp, sdp->Length)) {
			warnx("RSDT entry %d (sig %.4s) is corrupt", i,
			    sdp->Signature);
			continue;
		}
		if (!memcmp(sdp->Signature, ACPI_SIG_FADT, 4))
			acpi_handle_fadt(sdp);
		else if (!memcmp(sdp->Signature, ACPI_SIG_MADT, 4))
			acpi_handle_madt(sdp);
		else if (!memcmp(sdp->Signature, ACPI_SIG_HPET, 4))
			acpi_handle_hpet(sdp);
		else if (!memcmp(sdp->Signature, ACPI_SIG_ECDT, 4))
			acpi_handle_ecdt(sdp);
		else if (!memcmp(sdp->Signature, ACPI_SIG_MCFG, 4))
			acpi_handle_mcfg(sdp);
		else if (!memcmp(sdp->Signature, ACPI_SIG_SLIT, 4))
			acpi_handle_slit(sdp);
		else if (!memcmp(sdp->Signature, ACPI_SIG_SRAT, 4))
			acpi_handle_srat(sdp);
		else if (!memcmp(sdp->Signature, ACPI_SIG_TCPA, 4))
			acpi_handle_tcpa(sdp);
		else if (!memcmp(sdp->Signature, ACPI_SIG_DMAR, 4))
			acpi_handle_dmar(sdp);
		else if (!memcmp(sdp->Signature, ACPI_SIG_NFIT, 4))
			acpi_handle_nfit(sdp);
		else if (!memcmp(sdp->Signature, ACPI_SIG_WDDT, 4))
			acpi_handle_wddt(sdp);
		else if (!memcmp(sdp->Signature, ACPI_SIG_LPIT, 4))
			acpi_handle_lpit(sdp);
		else if (!memcmp(sdp->Signature, ACPI_SIG_TPM2, 4))
			acpi_handle_tpm2(sdp);
		else {
			printf(BEGIN_COMMENT);
			acpi_print_sdt(sdp);
			printf(END_COMMENT);
		}
	}
}