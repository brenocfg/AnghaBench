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
typedef  int /*<<< orphan*/ * caddr_t ;
struct TYPE_2__ {int probed; int ver; int major; int minor; void* product; void* maker; void* bios_vendor; int /*<<< orphan*/ * addr; void* count; void* length; } ;

/* Variables and functions */
 int /*<<< orphan*/ * const PTOV (uintptr_t) ; 
 void* SMBIOS_GET16 (int /*<<< orphan*/ *,int) ; 
 uintptr_t SMBIOS_GET32 (int /*<<< orphan*/ *,int) ; 
 void* SMBIOS_GET8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SMBIOS_LENGTH ; 
 uintptr_t SMBIOS_START ; 
 TYPE_1__ smbios ; 
 int /*<<< orphan*/ * smbios_find_struct (int) ; 
 void* smbios_getstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * smbios_sigsearch (int /*<<< orphan*/ * const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
smbios_probe(const caddr_t addr)
{
	caddr_t		saddr, info;
	uintptr_t	paddr;

	if (smbios.probed)
		return;
	smbios.probed = 1;

	/* Search signatures and validate checksums. */
	saddr = smbios_sigsearch(addr ? addr : PTOV(SMBIOS_START),
	    SMBIOS_LENGTH);
	if (saddr == NULL)
		return;

	smbios.length = SMBIOS_GET16(saddr, 0x16);	/* Structure Table Length */
	paddr = SMBIOS_GET32(saddr, 0x18);		/* Structure Table Address */
	smbios.count = SMBIOS_GET16(saddr, 0x1c);	/* No of SMBIOS Structures */
	smbios.ver = SMBIOS_GET8(saddr, 0x1e);		/* SMBIOS BCD Revision */

	if (smbios.ver != 0) {
		smbios.major = smbios.ver >> 4;
		smbios.minor = smbios.ver & 0x0f;
		if (smbios.major > 9 || smbios.minor > 9)
			smbios.ver = 0;
	}
	if (smbios.ver == 0) {
		smbios.major = SMBIOS_GET8(saddr, 0x06);/* SMBIOS Major Version */
		smbios.minor = SMBIOS_GET8(saddr, 0x07);/* SMBIOS Minor Version */
	}
	smbios.ver = (smbios.major << 8) | smbios.minor;
	smbios.addr = PTOV(paddr);

	/* Get system information from SMBIOS */
	info = smbios_find_struct(0x00);
	if (info != NULL) {
		smbios.bios_vendor = smbios_getstring(info, 0x04);
	}
	info = smbios_find_struct(0x01);
	if (info != NULL) {
		smbios.maker = smbios_getstring(info, 0x04);
		smbios.product = smbios_getstring(info, 0x05);
	}
}