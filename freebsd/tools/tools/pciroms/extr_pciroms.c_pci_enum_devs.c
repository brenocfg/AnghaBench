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
typedef  int /*<<< orphan*/  uint16_t ;
struct pci_conf_io {int match_buf_len; scalar_t__ status; size_t num_matches; struct pci_conf* matches; } ;
struct TYPE_2__ {int pc_domain; int pc_bus; int pc_dev; int pc_func; } ;
struct pci_conf {int pc_hdr; int pc_device; int pc_vendor; TYPE_1__ pc_sel; } ;
typedef  int /*<<< orphan*/  pc ;
typedef  int /*<<< orphan*/  filename ;
typedef  int /*<<< orphan*/  devs ;
typedef  int action_t ;

/* Variables and functions */
 int MAX_PCI_DEVS ; 
 int /*<<< orphan*/  PCIOCGETCONF ; 
 scalar_t__ PCI_GETCONF_ERROR ; 
 scalar_t__ PCI_GETCONF_MORE_DEVS ; 
#define  PRINT 129 
#define  SAVE 128 
 int /*<<< orphan*/  bzero (struct pci_conf_io*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int ioctl (int,int /*<<< orphan*/ ,struct pci_conf_io*) ; 
 int /*<<< orphan*/  pci_disable_bars (int,struct pci_conf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_enable_bars (int,struct pci_conf*,int /*<<< orphan*/ *) ; 
 int pci_save_rom (char*,int) ; 
 int pci_testrombar (int,struct pci_conf*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
pci_enum_devs(int pci_fd, action_t action)
{
	struct pci_conf		 devs[MAX_PCI_DEVS];
	char			 filename[16];
	struct pci_conf_io	 pc;
	struct pci_conf		*p;
	int			 result;
	int			 romsize;
	uint16_t		 oldcmd;

	result = -1;
	romsize = 0;

	bzero(&pc, sizeof(pc));
	pc.match_buf_len = sizeof(devs);
	pc.matches = devs;

	if (ioctl(pci_fd, PCIOCGETCONF, &pc) == -1) {
		perror("ioctl PCIOCGETCONF");
		return;
	}

	if (pc.status == PCI_GETCONF_ERROR) {
		fprintf(stderr,
		    "Error fetching PCI device list from kernel.\r\n");
		return;
	}

	if (pc.status == PCI_GETCONF_MORE_DEVS) {
		fprintf(stderr,
"More than %d devices exist. Only the first %d will be inspected.\r\n",
		    MAX_PCI_DEVS, MAX_PCI_DEVS);
	}

	for (p = devs ; p < &devs[pc.num_matches]; p++) {

		/* No PCI bridges; only PCI devices. */
		if (p->pc_hdr != 0x00)
			continue;

		romsize = pci_testrombar(pci_fd, p);

		switch (action) {
		case PRINT:
			printf(
"Domain %04Xh Bus %02Xh Device %02Xh Function %02Xh: ",
				p->pc_sel.pc_domain, p->pc_sel.pc_bus,
				p->pc_sel.pc_dev, p->pc_sel.pc_func);
			printf((romsize ? "%dKB ROM aperture detected."
					: "No ROM present."), romsize/1024);
			printf("\r\n");
			break;
		case SAVE:
			if (romsize == 0)
				continue;	/* XXX */

			snprintf(filename, sizeof(filename), "%08X.rom",
			    ((p->pc_device << 16) | p->pc_vendor));

			fprintf(stderr, "Saving %dKB ROM image to %s...\r\n",
			    romsize, filename);

			if (pci_enable_bars(pci_fd, p, &oldcmd) == 0)
				result = pci_save_rom(filename, romsize);

			pci_disable_bars(pci_fd, p, &oldcmd);

			if (result == 0)  {
				fprintf(stderr, "Done.\r\n");
			} else  {
				fprintf(stderr,
"An error occurred whilst saving the ROM.\r\n");
			}
			break;
		} /* switch */
	} /* for */
}