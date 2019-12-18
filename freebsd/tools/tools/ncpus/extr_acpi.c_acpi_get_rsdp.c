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
typedef  int /*<<< orphan*/  u_long ;
struct ACPIrsdp {scalar_t__ revision; size_t length; int /*<<< orphan*/  signature; } ;
typedef  int /*<<< orphan*/  rsdp ;

/* Variables and functions */
 scalar_t__ acpi_checksum (struct ACPIrsdp*,int) ; 
 struct ACPIrsdp* acpi_map_physical (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  acpi_mem_fd ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  pread (int /*<<< orphan*/ ,struct ACPIrsdp*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ACPIrsdp *
acpi_get_rsdp(u_long addr)
{
	struct ACPIrsdp rsdp;
	size_t len;

	/* Read in the table signature and check it. */
	pread(acpi_mem_fd, &rsdp, 8, addr);
	if (memcmp(rsdp.signature, "RSD PTR ", 8))
		return (NULL);

	/* Read the entire table. */
	pread(acpi_mem_fd, &rsdp, sizeof(rsdp), addr);

	/* Run the checksum only over the version 1 header. */
	if (acpi_checksum(&rsdp, 20))
		return (NULL);

	/* If the revision is 0, assume a version 1 length. */
	if (rsdp.revision == 0)
		len = 20;
	else
		len = rsdp.length;

	/* XXX Should handle ACPI 2.0 RSDP extended checksum here. */

	return (acpi_map_physical(addr, len));
}