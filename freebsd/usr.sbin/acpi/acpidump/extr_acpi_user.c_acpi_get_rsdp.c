#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
typedef  int /*<<< orphan*/  rsdp ;
struct TYPE_6__ {int Revision; size_t Length; int /*<<< orphan*/  Signature; } ;
typedef  TYPE_1__ ACPI_TABLE_RSDP ;
typedef  int /*<<< orphan*/  ACPI_RSDP_COMMON ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_RSDP_CHECKSUM_LENGTH ; 
 int /*<<< orphan*/  ACPI_RSDP_XCHECKSUM_LENGTH ; 
 scalar_t__ acpi_checksum (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* acpi_map_physical (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  acpi_mem_fd ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  pread (int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ACPI_TABLE_RSDP *
acpi_get_rsdp(u_long addr)
{
	ACPI_TABLE_RSDP rsdp;
	size_t len;

	/* Read in the table signature and check it. */
	pread(acpi_mem_fd, &rsdp, 8, addr);
	if (memcmp(rsdp.Signature, "RSD PTR ", 8))
		return (NULL);

	/* Read the entire table. */
	pread(acpi_mem_fd, &rsdp, sizeof(rsdp), addr);

	/* Check the standard checksum. */
	if (acpi_checksum(&rsdp, ACPI_RSDP_CHECKSUM_LENGTH) != 0)
		return (NULL);

	/* Check extended checksum if table version >= 2. */
	if (rsdp.Revision >= 2 &&
	    acpi_checksum(&rsdp, ACPI_RSDP_XCHECKSUM_LENGTH) != 0)
		return (NULL);

	/* If the revision is 0, assume a version 1 length. */
	if (rsdp.Revision == 0)
		len = sizeof(ACPI_RSDP_COMMON);
	else
		len = rsdp.Length;

	return (acpi_map_physical(addr, len));
}