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
typedef  int /*<<< orphan*/  uint32_t ;
struct pci_subclass {int ps_subclass; struct pci_progif* ps_progif; } ;
struct pci_progif {scalar_t__ pi_code; } ;
struct pci_class {int pc_class; struct pci_subclass* pc_subclass; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIOSPCI_32BITS ; 
 int /*<<< orphan*/  biospci_addinfo (int /*<<< orphan*/ ,struct pci_class*,struct pci_subclass*,struct pci_progif*) ; 
 int biospci_find_devclass (scalar_t__,int,int /*<<< orphan*/ *) ; 
 int biospci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct pci_class* pci_classes ; 

__attribute__((used)) static void
biospci_enumerate(void)
{
    int			device_index, err;
    uint32_t		locator, devid;
    struct pci_class	*pc;
    struct pci_subclass *psc;
    struct pci_progif	*ppi;

    /* Iterate over known classes */
    for (pc = pci_classes; pc->pc_class >= 0; pc++) {
	/* Iterate over subclasses */
	for (psc = pc->pc_subclass; psc->ps_subclass >= 0; psc++) {
	    /* Iterate over programming interfaces */
	    for (ppi = psc->ps_progif; ppi->pi_code >= 0; ppi++) {

		/* Scan for matches */
		for (device_index = 0; ; device_index++) {
		    /* Look for a match */
		    err = biospci_find_devclass((pc->pc_class << 16)
			+ (psc->ps_subclass << 8) + ppi->pi_code,
			device_index, &locator);
		    if (err != 0)
			break;

		    /* Read the device identifier from the nominated device */
		    err = biospci_read_config(locator, 0, BIOSPCI_32BITS, &devid);
		    if (err != 0)
			break;
		    
		    /* We have the device ID, create a PnP object and save everything */
		    biospci_addinfo(devid, pc, psc, ppi);
		}
	    }
	}
    }
}