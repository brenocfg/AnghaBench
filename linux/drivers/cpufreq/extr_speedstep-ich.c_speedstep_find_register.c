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
 int ENODEV ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int,int*) ; 
 int pmbase ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  speedstep_chipset_dev ; 

__attribute__((used)) static int speedstep_find_register(void)
{
	if (!speedstep_chipset_dev)
		return -ENODEV;

	/* get PMBASE */
	pci_read_config_dword(speedstep_chipset_dev, 0x40, &pmbase);
	if (!(pmbase & 0x01)) {
		pr_err("could not find speedstep register\n");
		return -ENODEV;
	}

	pmbase &= 0xFFFFFFFE;
	if (!pmbase) {
		pr_err("could not find speedstep register\n");
		return -ENODEV;
	}

	pr_debug("pmbase is 0x%x\n", pmbase);
	return 0;
}