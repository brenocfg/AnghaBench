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
typedef  int /*<<< orphan*/  driver_t ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  devclass_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_ADD_CHILD (int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  M_TEMP ; 
 int PCIM_HDRTYPE ; 
 int PCIM_MFDEV ; 
 int /*<<< orphan*/  PCIR_CLASS ; 
 int /*<<< orphan*/  PCIR_DEVVENDOR ; 
 int /*<<< orphan*/  PCIR_HDRTYPE ; 
 int /*<<< orphan*/  PCIR_SUBCLASS ; 
 int PCI_FUNCMAX ; 
 int PCI_MAXHDRTYPE ; 
 int PCI_SLOTMAX ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  devclass_find (char*) ; 
 scalar_t__ devclass_get_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ device_get_children (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int legacy_get_pcibus (int /*<<< orphan*/ ) ; 
 char* legacy_pcib_is_host_bridge (int,int,int,int,int,int,int*) ; 
 int legacy_pcib_read_config (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  legacy_set_pcibus (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  legacy_set_pcifunc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  legacy_set_pcislot (int /*<<< orphan*/ ,int) ; 
 scalar_t__ pci_cfgregopen () ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
legacy_pcib_identify(driver_t *driver, device_t parent)
{
	int bus, slot, func;
	uint8_t  hdrtype;
	int found = 0;
	int pcifunchigh;
	int found824xx = 0;
	int found_orion = 0;
	device_t child;
	devclass_t pci_devclass;

	if (pci_cfgregopen() == 0)
		return;
	/*
	 * Check to see if we haven't already had a PCI bus added
	 * via some other means.  If we have, bail since otherwise
	 * we're going to end up duplicating it.
	 */
	if ((pci_devclass = devclass_find("pci")) &&
		devclass_get_device(pci_devclass, 0))
		return;


	bus = 0;
 retry:
	for (slot = 0; slot <= PCI_SLOTMAX; slot++) {
		func = 0;
		hdrtype = legacy_pcib_read_config(0, bus, slot, func,
						 PCIR_HDRTYPE, 1);
		/*
		 * When enumerating bus devices, the standard says that
		 * one should check the header type and ignore the slots whose
		 * header types that the software doesn't know about.  We use
		 * this to filter out devices.
		 */
		if ((hdrtype & PCIM_HDRTYPE) > PCI_MAXHDRTYPE)
			continue;
		if ((hdrtype & PCIM_MFDEV) &&
		    (!found_orion || hdrtype != 0xff))
			pcifunchigh = PCI_FUNCMAX;
		else
			pcifunchigh = 0;
		for (func = 0; func <= pcifunchigh; func++) {
			/*
			 * Read the IDs and class from the device.
			 */
			uint32_t id;
			uint8_t class, subclass, busnum;
			const char *s;
			device_t *devs;
			int ndevs, i;

			id = legacy_pcib_read_config(0, bus, slot, func,
						    PCIR_DEVVENDOR, 4);
			if (id == -1)
				continue;
			class = legacy_pcib_read_config(0, bus, slot, func,
						       PCIR_CLASS, 1);
			subclass = legacy_pcib_read_config(0, bus, slot, func,
							  PCIR_SUBCLASS, 1);

			s = legacy_pcib_is_host_bridge(bus, slot, func,
						      id, class, subclass,
						      &busnum);
			if (s == NULL)
				continue;

			/*
			 * Check to see if the physical bus has already
			 * been seen.  Eg: hybrid 32 and 64 bit host
			 * bridges to the same logical bus.
			 */
			if (device_get_children(parent, &devs, &ndevs) == 0) {
				for (i = 0; s != NULL && i < ndevs; i++) {
					if (strcmp(device_get_name(devs[i]),
					    "pcib") != 0)
						continue;
					if (legacy_get_pcibus(devs[i]) == busnum)
						s = NULL;
				}
				free(devs, M_TEMP);
			}

			if (s == NULL)
				continue;
			/*
			 * Add at priority 100 to make sure we
			 * go after any motherboard resources
			 */
			child = BUS_ADD_CHILD(parent, 100,
					      "pcib", busnum);
			device_set_desc(child, s);
			legacy_set_pcibus(child, busnum);
			legacy_set_pcislot(child, slot);
			legacy_set_pcifunc(child, func);

			found = 1;
			if (id == 0x12258086)
				found824xx = 1;
			if (id == 0x84c48086)
				found_orion = 1;
		}
	}
	if (found824xx && bus == 0) {
		bus++;
		goto retry;
	}

	/*
	 * Make sure we add at least one bridge since some old
	 * hardware doesn't actually have a host-pci bridge device.
	 * Note that pci_cfgregopen() thinks we have PCI devices..
	 */
	if (!found) {
		if (bootverbose)
			printf(
	"legacy_pcib_identify: no bridge found, adding pcib0 anyway\n");
		child = BUS_ADD_CHILD(parent, 100, "pcib", 0);
		legacy_set_pcibus(child, 0);
	}
}