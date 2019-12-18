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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u_long ;
struct ACPIsdt {int /*<<< orphan*/  len; int /*<<< orphan*/  signature; } ;
struct ACPIrsdp {int revision; int /*<<< orphan*/  xsdt_addr; int /*<<< orphan*/  rsdt_addr; } ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
 int /*<<< orphan*/  acpi0_present () ; 
 scalar_t__ acpi_checksum (struct ACPIsdt*,int /*<<< orphan*/ ) ; 
 struct ACPIrsdp* acpi_get_rsdp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_handle_rsdt (struct ACPIsdt*) ; 
 scalar_t__ acpi_map_sdt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_user_init () ; 
 int addr_size ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  machdep_acpi_root ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char*,int) ; 
 int ncpu ; 
 scalar_t__ sysctlbyname (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

int
acpi_detect(void)
{
	struct ACPIrsdp *rp;
	struct ACPIsdt *rsdp;
	u_long addr;
	size_t len;

	if (!acpi0_present()) {
		warnx("no acpi0 device located");
		return -1;
	}

	acpi_user_init();

	/* Attempt to use sysctl to find RSD PTR record. */
	len = sizeof(addr);
	if (sysctlbyname(machdep_acpi_root, &addr, &len, NULL, 0) != 0) {
		warnx("cannot find ACPI information");
		return -1;
	}
	rp = acpi_get_rsdp(addr);
	if (rp == NULL) {
		warnx("cannot find ACPI information: sysctl %s does not point to RSDP",
			machdep_acpi_root);
		return -1;
	}
	if (rp->revision < 2) {
		rsdp = (struct ACPIsdt *)acpi_map_sdt(rp->rsdt_addr);
		if (memcmp(rsdp->signature, "RSDT", 4) != 0 ||
		    acpi_checksum(rsdp, rsdp->len) != 0)
			errx(1, "RSDT is corrupted");
		addr_size = sizeof(uint32_t);
	} else {
		rsdp = (struct ACPIsdt *)acpi_map_sdt(rp->xsdt_addr);
		if (memcmp(rsdp->signature, "XSDT", 4) != 0 ||
		    acpi_checksum(rsdp, rsdp->len) != 0)
			errx(1, "XSDT is corrupted");
		addr_size = sizeof(uint64_t);
	}
	ncpu = 0;
	acpi_handle_rsdt(rsdp);
	return (ncpu == 0 ? 1 : ncpu);
}