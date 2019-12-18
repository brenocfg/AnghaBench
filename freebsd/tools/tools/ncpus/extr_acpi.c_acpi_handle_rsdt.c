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
typedef  int /*<<< orphan*/  vm_offset_t ;
struct ACPIsdt {int len; int /*<<< orphan*/  signature; scalar_t__ body; } ;

/* Variables and functions */
 int SIZEOF_SDT_HDR ; 
 scalar_t__ acpi_checksum (struct ACPIsdt*,int) ; 
 int /*<<< orphan*/  acpi_handle_apic (struct ACPIsdt*) ; 
 scalar_t__ acpi_map_sdt (int /*<<< orphan*/ ) ; 
 int addr_size ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32dec (char*) ; 
 int /*<<< orphan*/  le64dec (char*) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  warnx (char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
acpi_handle_rsdt(struct ACPIsdt *rsdp)
{
	struct ACPIsdt *sdp;
	vm_offset_t addr;
	int entries, i;

	entries = (rsdp->len - SIZEOF_SDT_HDR) / addr_size;
	for (i = 0; i < entries; i++) {
		switch (addr_size) {
		case 4:
			addr = le32dec((char*)rsdp->body + i * addr_size);
			break;
		case 8:
			addr = le64dec((char*)rsdp->body + i * addr_size);
			break;
		default:
			assert((addr = 0));
		}

		sdp = (struct ACPIsdt *)acpi_map_sdt(addr);
		if (acpi_checksum(sdp, sdp->len)) {
#if 0
			warnx("RSDT entry %d (sig %.4s) has bad checksum", i,
			    sdp->signature);
#endif
			continue;
		}
		if (!memcmp(sdp->signature, "APIC", 4))
			acpi_handle_apic(sdp);
	}
}