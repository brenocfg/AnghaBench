#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct mbox_reorder   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct bge_softc {int /*<<< orphan*/  bge_dev; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  scalar_t__ devclass_t ;
struct mbox_reorder {scalar_t__ const vendor; scalar_t__ const device; char const* desc; } ;

/* Variables and functions */
 scalar_t__ devclass_find (char*) ; 
 scalar_t__ device_get_devclass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,char const*) ; 
 int nitems (TYPE_1__ const*) ; 
 scalar_t__ pci_get_device (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_vendor (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bge_mbox_reorder(struct bge_softc *sc)
{
	/* Lists of PCI bridges that are known to reorder mailbox writes. */
	static const struct mbox_reorder {
		const uint16_t vendor;
		const uint16_t device;
		const char *desc;
	} mbox_reorder_lists[] = {
		{ 0x1022, 0x7450, "AMD-8131 PCI-X Bridge" },
	};
	devclass_t pci, pcib;
	device_t bus, dev;
	int i;

	pci = devclass_find("pci");
	pcib = devclass_find("pcib");
	dev = sc->bge_dev;
	bus = device_get_parent(dev);
	for (;;) {
		dev = device_get_parent(bus);
		bus = device_get_parent(dev);
		if (device_get_devclass(dev) != pcib)
			break;
		if (device_get_devclass(bus) != pci)
			break;
		for (i = 0; i < nitems(mbox_reorder_lists); i++) {
			if (pci_get_vendor(dev) ==
			    mbox_reorder_lists[i].vendor &&
			    pci_get_device(dev) ==
			    mbox_reorder_lists[i].device) {
				device_printf(sc->bge_dev,
				    "enabling MBOX workaround for %s\n",
				    mbox_reorder_lists[i].desc);
				return (1);
			}
		}
	}
	return (0);
}