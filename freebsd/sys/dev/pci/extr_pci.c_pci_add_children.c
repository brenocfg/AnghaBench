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
typedef  int uint8_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct pci_devinfo {TYPE_1__ cfg; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int PCIB_MAXFUNCS (int /*<<< orphan*/ ) ; 
 int PCIB_MAXSLOTS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCIB_TRY_ENABLE_ARI (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PCIM_HDRTYPE ; 
 int PCIM_MFDEV ; 
 int /*<<< orphan*/  PCIR_HDRTYPE ; 
 int PCI_MAXHDRTYPE ; 
 int REG (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_enable_ari ; 
 struct pci_devinfo* pci_identify_function (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int) ; 

void
pci_add_children(device_t dev, int domain, int busno)
{
#define	REG(n, w)	PCIB_READ_CONFIG(pcib, busno, s, f, n, w)
	device_t pcib = device_get_parent(dev);
	struct pci_devinfo *dinfo;
	int maxslots;
	int s, f, pcifunchigh;
	uint8_t hdrtype;
	int first_func;

	/*
	 * Try to detect a device at slot 0, function 0.  If it exists, try to
	 * enable ARI.  We must enable ARI before detecting the rest of the
	 * functions on this bus as ARI changes the set of slots and functions
	 * that are legal on this bus.
	 */
	dinfo = pci_identify_function(pcib, dev, domain, busno, 0, 0);
	if (dinfo != NULL && pci_enable_ari)
		PCIB_TRY_ENABLE_ARI(pcib, dinfo->cfg.dev);

	/*
	 * Start looking for new devices on slot 0 at function 1 because we
	 * just identified the device at slot 0, function 0.
	 */
	first_func = 1;

	maxslots = PCIB_MAXSLOTS(pcib);
	for (s = 0; s <= maxslots; s++, first_func = 0) {
		pcifunchigh = 0;
		f = 0;
		DELAY(1);
		hdrtype = REG(PCIR_HDRTYPE, 1);
		if ((hdrtype & PCIM_HDRTYPE) > PCI_MAXHDRTYPE)
			continue;
		if (hdrtype & PCIM_MFDEV)
			pcifunchigh = PCIB_MAXFUNCS(pcib);
		for (f = first_func; f <= pcifunchigh; f++)
			pci_identify_function(pcib, dev, domain, busno, s, f);
	}
#undef REG
}