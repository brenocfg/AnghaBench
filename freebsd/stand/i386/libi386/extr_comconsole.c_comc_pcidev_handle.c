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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIOSPCI_32BITS ; 
 int CMD_ERROR ; 
 int CMD_OK ; 
 int /*<<< orphan*/  EV_VOLATILE ; 
 int PCIM_BAR_IO_BASE ; 
 int /*<<< orphan*/  PCI_BAR_IO (int) ; 
 int biospci_read_config (int,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  comc_curspeed ; 
 int comc_locator ; 
 int /*<<< orphan*/  comc_port_set ; 
 int /*<<< orphan*/  comc_setup (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  env_nounset ; 
 int /*<<< orphan*/  env_setenv (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  unsetenv (char*) ; 

__attribute__((used)) static int
comc_pcidev_handle(uint32_t locator)
{
#ifdef EFI
	/* We don't support PCI in EFI yet */
	return (CMD_ERROR);
#else
	char intbuf[64];
	uint32_t port;

	if (biospci_read_config(locator & 0xffff,
	    (locator & 0xff0000) >> 16, BIOSPCI_32BITS, &port) == -1) {
		printf("Cannot read bar at 0x%x\n", locator);
		return (CMD_ERROR);
	}

	/* 
	 * biospci_read_config() sets port == 0xffffffff if the pcidev
	 * isn't found on the bus.  Check for 0xffffffff and return to not
	 * panic in BTX.
	 */
	if (port == 0xffffffff) {
		printf("Cannot find specified pcidev\n");
		return (CMD_ERROR);
	}
	if (!PCI_BAR_IO(port)) {
		printf("Memory bar at 0x%x\n", locator);
		return (CMD_ERROR);
	}
        port &= PCIM_BAR_IO_BASE;

	sprintf(intbuf, "%d", port);
	unsetenv("comconsole_port");
	env_setenv("comconsole_port", EV_VOLATILE, intbuf,
		   comc_port_set, env_nounset);

	comc_setup(comc_curspeed, port);
	comc_locator = locator;

	return (CMD_OK);
#endif
}