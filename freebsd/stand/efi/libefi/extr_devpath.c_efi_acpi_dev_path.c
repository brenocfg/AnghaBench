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
typedef  int uint8_t ;
struct TYPE_2__ {int HID; int UID; } ;
typedef  int /*<<< orphan*/  EFI_DEVICE_PATH ;
typedef  TYPE_1__ ACPI_HID_DEVICE_PATH ;

/* Variables and functions */
#define  ACPI_DP 129 
#define  ACPI_EXTENDED_DP 128 
 int DevicePathSubType (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EISA_ID_TO_NUM (int) ; 
 int PNP_EISA_ID_CONST ; 
 int PNP_EISA_ID_MASK ; 
 int /*<<< orphan*/  asprintf (char**,char*,int,...) ; 
 char* efi_make_tail (char*) ; 
 int /*<<< orphan*/  free (char*) ; 

__attribute__((used)) static char *
efi_acpi_dev_path(EFI_DEVICE_PATH *node, char *suffix)
{
	uint8_t subtype = DevicePathSubType(node);
	ACPI_HID_DEVICE_PATH *acpi = (ACPI_HID_DEVICE_PATH *)node;
	char *name, *tail;

	tail = efi_make_tail(suffix);
	switch (subtype) {
	case ACPI_DP:
		if ((acpi->HID & PNP_EISA_ID_MASK) == PNP_EISA_ID_CONST) {
			switch (EISA_ID_TO_NUM (acpi->HID)) {
			case 0x0a03:
				if (asprintf(&name, "PciRoot(%x)%s",
				    acpi->UID, tail) < 0)
					name = NULL;
				break;
			case 0x0a08:
				if (asprintf(&name, "PcieRoot(%x)%s",
				    acpi->UID, tail) < 0)
					name = NULL;
				break;
			case 0x0604:
				if (asprintf(&name, "Floppy(%x)%s",
				    acpi->UID, tail) < 0)
					name = NULL;
				break;
			case 0x0301:
				if (asprintf(&name, "Keyboard(%x)%s",
				    acpi->UID, tail) < 0)
					name = NULL;
				break;
			case 0x0501:
				if (asprintf(&name, "Serial(%x)%s",
				    acpi->UID, tail) < 0)
					name = NULL;
				break;
			case 0x0401:
				if (asprintf(&name, "ParallelPort(%x)%s",
				    acpi->UID, tail) < 0)
					name = NULL;
				break;
			default:
				if (asprintf(&name, "Acpi(PNP%04x,%x)%s",
				    EISA_ID_TO_NUM(acpi->HID),
				    acpi->UID, tail) < 0)
					name = NULL;
				break;
			}
		} else {
			if (asprintf(&name, "Acpi(%08x,%x)%s",
			    acpi->HID, acpi->UID, tail) < 0)
				name = NULL;
		}
		break;
	case ACPI_EXTENDED_DP:
	default:
		if (asprintf(&name, "UnknownACPI(%x)%s", subtype, tail) < 0)
			name = NULL;
		break;
	}
	free(tail);
	return (name);
}