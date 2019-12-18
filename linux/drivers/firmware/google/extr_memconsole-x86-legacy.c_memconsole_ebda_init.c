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
typedef  size_t u8 ;
struct biosmemcon_ebda {scalar_t__ signature; } ;

/* Variables and functions */
 scalar_t__ BIOS_MEMCONSOLE_V1_MAGIC ; 
 scalar_t__ BIOS_MEMCONSOLE_V2_MAGIC ; 
 int /*<<< orphan*/  found_v1_header (struct biosmemcon_ebda*) ; 
 int /*<<< orphan*/  found_v2_header (struct biosmemcon_ebda*) ; 
 unsigned int get_bios_ebda () ; 
 struct biosmemcon_ebda* phys_to_virt (unsigned int) ; 
 int /*<<< orphan*/  pr_info (char*) ; 

__attribute__((used)) static bool memconsole_ebda_init(void)
{
	unsigned int address;
	size_t length, cur;

	address = get_bios_ebda();
	if (!address) {
		pr_info("memconsole: BIOS EBDA non-existent.\n");
		return false;
	}

	/* EBDA length is byte 0 of EBDA (in KB) */
	length = *(u8 *)phys_to_virt(address);
	length <<= 10; /* convert to bytes */

	/*
	 * Search through EBDA for BIOS memory console structure
	 * note: signature is not necessarily dword-aligned
	 */
	for (cur = 0; cur < length; cur++) {
		struct biosmemcon_ebda *hdr = phys_to_virt(address + cur);

		/* memconsole v1 */
		if (hdr->signature == BIOS_MEMCONSOLE_V1_MAGIC) {
			found_v1_header(hdr);
			return true;
		}

		/* memconsole v2 */
		if (hdr->signature == BIOS_MEMCONSOLE_V2_MAGIC) {
			found_v2_header(hdr);
			return true;
		}
	}

	pr_info("memconsole: BIOS console EBDA structure not found!\n");
	return false;
}