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

/* Variables and functions */
#define  CFGMECH_1 130 
#define  CFGMECH_2 129 
#define  CFGMECH_PCIE 128 
 int /*<<< orphan*/  CONF2_ENABLE_PORT ; 
 int cfgmech ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pci_cfgdisable(void)
{
	switch (cfgmech) {
	case CFGMECH_PCIE:
	case CFGMECH_1:
		/*
		 * Do nothing for the config mechanism 1 case.
		 * Writing a 0 to the address port can apparently
		 * confuse some bridges and cause spurious
		 * access failures.
		 */
		break;
	case CFGMECH_2:
		outb(CONF2_ENABLE_PORT, 0);
		break;
	}
}