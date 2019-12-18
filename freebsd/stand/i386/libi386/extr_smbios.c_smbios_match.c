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
struct TYPE_2__ {int /*<<< orphan*/  product; int /*<<< orphan*/  maker; int /*<<< orphan*/  bios_vendor; } ;

/* Variables and functions */
 TYPE_1__ smbios ; 
 scalar_t__ smbios_match_str (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smbios_probe (int /*<<< orphan*/ *) ; 

int
smbios_match(const char* bios_vendor, const char* maker,
    const char* product)
{
	/* XXXRP currently, only called from non-EFI. */
	smbios_probe(NULL);
	return (smbios_match_str(bios_vendor, smbios.bios_vendor) &&
	    smbios_match_str(maker, smbios.maker) &&
	    smbios_match_str(product, smbios.product));
}