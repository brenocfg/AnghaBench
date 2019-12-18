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
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int ENOMEM ; 
 int M_NOWAIT ; 
 int /*<<< orphan*/  M_TEMP ; 
 int M_ZERO ; 
 int PCIB_MAXFUNCS (int /*<<< orphan*/ *) ; 
 int PCIB_MAXSLOTS (int /*<<< orphan*/ *) ; 
 int PCIM_HDRTYPE ; 
 int PCIM_MFDEV ; 
 int /*<<< orphan*/  PCIR_HDRTYPE ; 
 int /*<<< orphan*/  PCIR_VENDOR ; 
 int PCI_MAXHDRTYPE ; 
 int REG (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int device_get_children (int /*<<< orphan*/ *,int /*<<< orphan*/ ***,int*) ; 
 int /*<<< orphan*/ * device_get_parent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_probe_and_attach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** malloc (int,int /*<<< orphan*/ ,int) ; 
 int pci_get_function (int /*<<< orphan*/ *) ; 
 int pci_get_slot (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_identify_function (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int) ; 
 int pcib_get_bus (int /*<<< orphan*/ *) ; 
 int pcib_get_domain (int /*<<< orphan*/ *) ; 

int
pci_rescan_method(device_t dev)
{
#define	REG(n, w)	PCIB_READ_CONFIG(pcib, busno, s, f, n, w)
	device_t pcib = device_get_parent(dev);
	device_t child, *devlist, *unchanged;
	int devcount, error, i, j, maxslots, oldcount;
	int busno, domain, s, f, pcifunchigh;
	uint8_t hdrtype;

	/* No need to check for ARI on a rescan. */
	error = device_get_children(dev, &devlist, &devcount);
	if (error)
		return (error);
	if (devcount != 0) {
		unchanged = malloc(devcount * sizeof(device_t), M_TEMP,
		    M_NOWAIT | M_ZERO);
		if (unchanged == NULL) {
			free(devlist, M_TEMP);
			return (ENOMEM);
		}
	} else
		unchanged = NULL;

	domain = pcib_get_domain(dev);
	busno = pcib_get_bus(dev);
	maxslots = PCIB_MAXSLOTS(pcib);
	for (s = 0; s <= maxslots; s++) {
		/* If function 0 is not present, skip to the next slot. */
		f = 0;
		if (REG(PCIR_VENDOR, 2) == 0xffff)
			continue;
		pcifunchigh = 0;
		hdrtype = REG(PCIR_HDRTYPE, 1);
		if ((hdrtype & PCIM_HDRTYPE) > PCI_MAXHDRTYPE)
			continue;
		if (hdrtype & PCIM_MFDEV)
			pcifunchigh = PCIB_MAXFUNCS(pcib);
		for (f = 0; f <= pcifunchigh; f++) {
			if (REG(PCIR_VENDOR, 2) == 0xffff)
				continue;

			/*
			 * Found a valid function.  Check if a
			 * device_t for this device already exists.
			 */
			for (i = 0; i < devcount; i++) {
				child = devlist[i];
				if (child == NULL)
					continue;
				if (pci_get_slot(child) == s &&
				    pci_get_function(child) == f) {
					unchanged[i] = child;
					goto next_func;
				}
			}

			pci_identify_function(pcib, dev, domain, busno, s, f);
		next_func:;
		}
	}

	/* Remove devices that are no longer present. */
	for (i = 0; i < devcount; i++) {
		if (unchanged[i] != NULL)
			continue;
		device_delete_child(dev, devlist[i]);
	}

	free(devlist, M_TEMP);
	oldcount = devcount;

	/* Try to attach the devices just added. */
	error = device_get_children(dev, &devlist, &devcount);
	if (error) {
		free(unchanged, M_TEMP);
		return (error);
	}

	for (i = 0; i < devcount; i++) {
		for (j = 0; j < oldcount; j++) {
			if (devlist[i] == unchanged[j])
				goto next_device;
		}

		device_probe_and_attach(devlist[i]);
	next_device:;
	}

	free(unchanged, M_TEMP);
	free(devlist, M_TEMP);
	return (0);
#undef REG
}