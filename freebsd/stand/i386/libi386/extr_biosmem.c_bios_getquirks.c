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
 TYPE_1__* quirks ; 
 scalar_t__ smbios_match (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bios_getquirks(void)
{
	int i;

	for (i = 0; quirks[i].quirk != 0; ++i) {
		if (smbios_match(quirks[i].bios_vendor, quirks[i].maker,
		    quirks[i].product))
			return (quirks[i].quirk);
	}

	return (0);
}