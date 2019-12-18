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
typedef  int /*<<< orphan*/  uintmax_t ;
struct TYPE_3__ {int Length; int HardwareSignature; int FirmwareWakingVector; int GlobalLock; int Flags; scalar_t__ XFirmwareWakingVector; int Version; } ;
typedef  TYPE_1__ ACPI_TABLE_FACS ;

/* Variables and functions */
 int ACPI_FACS_S4_BIOS_PRESENT ; 
 int ACPI_GLOCK_OWNED ; 
 int ACPI_GLOCK_PENDING ; 
 char* BEGIN_COMMENT ; 
 char* END_COMMENT ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
acpi_print_facs(ACPI_TABLE_FACS *facs)
{
	printf(BEGIN_COMMENT);
	printf("  FACS:\tLength=%u, ", facs->Length);
	printf("HwSig=0x%08x, ", facs->HardwareSignature);
	printf("Firm_Wake_Vec=0x%08x\n", facs->FirmwareWakingVector);

	printf("\tGlobal_Lock=");
	if (facs->GlobalLock != 0) {
		if (facs->GlobalLock & ACPI_GLOCK_PENDING)
			printf("PENDING,");
		if (facs->GlobalLock & ACPI_GLOCK_OWNED)
			printf("OWNED");
	}
	printf("\n");

	printf("\tFlags=");
	if (facs->Flags & ACPI_FACS_S4_BIOS_PRESENT)
		printf("S4BIOS");
	printf("\n");

	if (facs->XFirmwareWakingVector != 0)
		printf("\tX_Firm_Wake_Vec=%016jx\n",
		    (uintmax_t)facs->XFirmwareWakingVector);
	printf("\tVersion=%u\n", facs->Version);

	printf(END_COMMENT);
}