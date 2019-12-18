#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_9__ {int Length; scalar_t__ Checksum; } ;
typedef  TYPE_1__ ACPI_TABLE_HEADER ;

/* Variables and functions */
 char* ACPI_SIG_SSDT ; 
 scalar_t__ acpi_checksum (TYPE_1__*,int) ; 
 TYPE_1__* sdt_from_rsdt (TYPE_1__*,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  write (int,TYPE_1__*,int) ; 

__attribute__((used)) static int
write_dsdt(int fd, ACPI_TABLE_HEADER *rsdt, ACPI_TABLE_HEADER *dsdt)
{
	ACPI_TABLE_HEADER sdt;
	ACPI_TABLE_HEADER *ssdt;
	uint8_t sum;

	/* Create a new checksum to account for the DSDT and any SSDTs. */
	sdt = *dsdt;
	if (rsdt != NULL) {
		sdt.Checksum = 0;
		sum = acpi_checksum(dsdt + 1, dsdt->Length -
		    sizeof(ACPI_TABLE_HEADER));
		ssdt = sdt_from_rsdt(rsdt, ACPI_SIG_SSDT, NULL);
		while (ssdt != NULL) {
			sdt.Length += ssdt->Length - sizeof(ACPI_TABLE_HEADER);
			sum += acpi_checksum(ssdt + 1,
			    ssdt->Length - sizeof(ACPI_TABLE_HEADER));
			ssdt = sdt_from_rsdt(rsdt, ACPI_SIG_SSDT, ssdt);
		}
		sum += acpi_checksum(&sdt, sizeof(ACPI_TABLE_HEADER));
		sdt.Checksum -= sum;
	}

	/* Write out the DSDT header and body. */
	write(fd, &sdt, sizeof(ACPI_TABLE_HEADER));
	write(fd, dsdt + 1, dsdt->Length - sizeof(ACPI_TABLE_HEADER));

	/* Write out any SSDTs (if present.) */
	if (rsdt != NULL) {
		ssdt = sdt_from_rsdt(rsdt, "SSDT", NULL);
		while (ssdt != NULL) {
			write(fd, ssdt + 1, ssdt->Length -
			    sizeof(ACPI_TABLE_HEADER));
			ssdt = sdt_from_rsdt(rsdt, "SSDT", ssdt);
		}
	}
	return (0);
}