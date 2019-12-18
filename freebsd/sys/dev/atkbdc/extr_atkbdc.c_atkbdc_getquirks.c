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
struct TYPE_2__ {scalar_t__ quirk; int /*<<< orphan*/  product; int /*<<< orphan*/  maker; int /*<<< orphan*/  bios_vendor; } ;

/* Variables and functions */
 scalar_t__ QUIRK_STR_MATCH (int /*<<< orphan*/ ,char*) ; 
 char* kern_getenv (char*) ; 
 TYPE_1__* quirks ; 

__attribute__((used)) static int
atkbdc_getquirks(void)
{
    int i;
    char* bios_vendor = kern_getenv("smbios.bios.vendor");
    char* maker = kern_getenv("smbios.system.maker");
    char* product = kern_getenv("smbios.system.product");

    for (i=0; quirks[i].quirk != 0; ++i)
	if (QUIRK_STR_MATCH(quirks[i].bios_vendor, bios_vendor) &&
	    QUIRK_STR_MATCH(quirks[i].maker, maker) &&
	    QUIRK_STR_MATCH(quirks[i].product, product))
		return (quirks[i].quirk);

    return (0);
}