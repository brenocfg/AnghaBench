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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  (* ivhd_iter_t ) (TYPE_2__*,void*) ;
struct TYPE_6__ {scalar_t__ Length; } ;
struct TYPE_8__ {TYPE_1__ Header; } ;
struct TYPE_7__ {int Length; int Type; } ;
typedef  TYPE_3__ ACPI_TABLE_IVRS ;
typedef  int /*<<< orphan*/  ACPI_TABLE_HEADER ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_2__ ACPI_IVRS_HEADER ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
#define  ACPI_IVRS_TYPE_MEMORY1 133 
#define  ACPI_IVRS_TYPE_MEMORY2 132 
#define  ACPI_IVRS_TYPE_MEMORY3 131 
 int /*<<< orphan*/  ACPI_SIG_IVRS ; 
 int /*<<< orphan*/  AcpiGetTable (int /*<<< orphan*/ ,int,int /*<<< orphan*/ **) ; 
#define  IVRS_TYPE_HARDWARE_EFR 130 
#define  IVRS_TYPE_HARDWARE_LEGACY 129 
#define  IVRS_TYPE_HARDWARE_MIXED 128 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static void
ivrs_hdr_iterate_tbl(ivhd_iter_t iter, void *arg)
{
	ACPI_TABLE_IVRS *ivrs;
	ACPI_IVRS_HEADER *ivrs_hdr, *end;
	ACPI_STATUS status;

	status = AcpiGetTable(ACPI_SIG_IVRS, 1, (ACPI_TABLE_HEADER **)&ivrs);
	if (ACPI_FAILURE(status))
		return;

	if (ivrs->Header.Length == 0) {
		return;
	}

	ivrs_hdr = (ACPI_IVRS_HEADER *)(ivrs + 1);
	end = (ACPI_IVRS_HEADER *)((char *)ivrs + ivrs->Header.Length);

	while (ivrs_hdr < end) {
		if ((uint8_t *)ivrs_hdr + ivrs_hdr->Length > (uint8_t *)end) {
			printf("AMD-Vi:IVHD/IVMD is corrupted, length : %d\n",
			    ivrs_hdr->Length);
			break;
		}

		switch (ivrs_hdr->Type) {
		case IVRS_TYPE_HARDWARE_LEGACY:	/* Legacy */
		case IVRS_TYPE_HARDWARE_EFR:
		case IVRS_TYPE_HARDWARE_MIXED:
			if (!iter(ivrs_hdr, arg))
				return;
			break;

		case ACPI_IVRS_TYPE_MEMORY1:
		case ACPI_IVRS_TYPE_MEMORY2:
		case ACPI_IVRS_TYPE_MEMORY3:
			if (!iter(ivrs_hdr, arg))
				return;

			break;

		default:
			printf("AMD-Vi:Not IVHD/IVMD type(%d)", ivrs_hdr->Type);

		}

		ivrs_hdr = (ACPI_IVRS_HEADER *)((uint8_t *)ivrs_hdr +
			ivrs_hdr->Length);
	}
}