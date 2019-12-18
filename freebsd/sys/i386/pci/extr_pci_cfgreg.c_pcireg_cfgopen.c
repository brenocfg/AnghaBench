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
typedef  int uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int CFGMECH_1 ; 
 int CFGMECH_2 ; 
 int CFGMECH_NONE ; 
 int /*<<< orphan*/  CONF1_ADDR_PORT ; 
 int CONF1_ENABLE_CHK ; 
 int CONF1_ENABLE_CHK1 ; 
 int CONF1_ENABLE_MSK1 ; 
 int CONF1_ENABLE_RES1 ; 
 int CONF2_ENABLE_CHK ; 
 int /*<<< orphan*/  CONF2_ENABLE_PORT ; 
 int CONF2_ENABLE_RES ; 
 int /*<<< orphan*/  DELAY (int) ; 
 scalar_t__ bootverbose ; 
 int cfgmech ; 
 int devmax ; 
 int inb (int /*<<< orphan*/ ) ; 
 int inl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  outl (int /*<<< orphan*/ ,int) ; 
 scalar_t__ pci_cfgcheck (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static int
pcireg_cfgopen(void)
{
	uint32_t mode1res, oldval1;
	uint8_t mode2res, oldval2;

	/* Check for type #1 first. */
	oldval1 = inl(CONF1_ADDR_PORT);

	if (bootverbose) {
		printf("pci_open(1):\tmode 1 addr port (0x0cf8) is 0x%08x\n",
		    oldval1);
	}

	cfgmech = CFGMECH_1;
	devmax = 32;

	outl(CONF1_ADDR_PORT, CONF1_ENABLE_CHK);
	DELAY(1);
	mode1res = inl(CONF1_ADDR_PORT);
	outl(CONF1_ADDR_PORT, oldval1);

	if (bootverbose)
		printf("pci_open(1a):\tmode1res=0x%08x (0x%08lx)\n",  mode1res,
		    CONF1_ENABLE_CHK);

	if (mode1res) {
		if (pci_cfgcheck(32)) 
			return (cfgmech);
	}

	outl(CONF1_ADDR_PORT, CONF1_ENABLE_CHK1);
	mode1res = inl(CONF1_ADDR_PORT);
	outl(CONF1_ADDR_PORT, oldval1);

	if (bootverbose)
		printf("pci_open(1b):\tmode1res=0x%08x (0x%08lx)\n",  mode1res,
		    CONF1_ENABLE_CHK1);

	if ((mode1res & CONF1_ENABLE_MSK1) == CONF1_ENABLE_RES1) {
		if (pci_cfgcheck(32)) 
			return (cfgmech);
	}

	/* Type #1 didn't work, so try type #2. */
	oldval2 = inb(CONF2_ENABLE_PORT);

	if (bootverbose) {
		printf("pci_open(2):\tmode 2 enable port (0x0cf8) is 0x%02x\n",
		    oldval2);
	}

	if ((oldval2 & 0xf0) == 0) {

		cfgmech = CFGMECH_2;
		devmax = 16;

		outb(CONF2_ENABLE_PORT, CONF2_ENABLE_CHK);
		mode2res = inb(CONF2_ENABLE_PORT);
		outb(CONF2_ENABLE_PORT, oldval2);

		if (bootverbose)
			printf("pci_open(2a):\tmode2res=0x%02x (0x%02x)\n", 
			    mode2res, CONF2_ENABLE_CHK);

		if (mode2res == CONF2_ENABLE_RES) {
			if (bootverbose)
				printf("pci_open(2a):\tnow trying mechanism 2\n");

			if (pci_cfgcheck(16)) 
				return (cfgmech);
		}
	}

	/* Nothing worked, so punt. */
	cfgmech = CFGMECH_NONE;
	devmax = 0;
	return (cfgmech);
}