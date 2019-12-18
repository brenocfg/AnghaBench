#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct apc_tbl   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  scalar_t__ uint16_t ;
struct sge_softc {int /*<<< orphan*/  sge_flags; int /*<<< orphan*/  sge_dev; } ;
typedef  int /*<<< orphan*/ * device_t ;
typedef  int /*<<< orphan*/  devclass_t ;
struct apc_tbl {scalar_t__ vid; scalar_t__ did; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int EINVAL ; 
 int ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  M_TEMP ; 
 scalar_t__ PCIC_BRIDGE ; 
 scalar_t__ PCIS_BRIDGE_ISA ; 
 int /*<<< orphan*/  SGE_FLAG_RGMII ; 
 int /*<<< orphan*/  SIS_VENDORID ; 
 int /*<<< orphan*/  devclass_find (char*) ; 
 int /*<<< orphan*/ * devclass_get_device (int /*<<< orphan*/ ,int) ; 
 int devclass_get_maxunit (int /*<<< orphan*/ ) ; 
 scalar_t__ device_get_children (int /*<<< orphan*/ *,int /*<<< orphan*/ ***,int*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int inb (int) ; 
 int nitems (TYPE_1__*) ; 
 int /*<<< orphan*/  outb (int,int) ; 
 scalar_t__ pci_get_class (int /*<<< orphan*/ *) ; 
 scalar_t__ pci_get_device (int /*<<< orphan*/ *) ; 
 scalar_t__ pci_get_subclass (int /*<<< orphan*/ *) ; 
 scalar_t__ pci_get_vendor (int /*<<< orphan*/ *) ; 
 int pci_read_config (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ *,int,int,int) ; 

__attribute__((used)) static int
sge_get_mac_addr_apc(struct sge_softc *sc, uint8_t *dest)
{
#if defined(__amd64__) || defined(__i386__)
	devclass_t pci;
	device_t bus, dev = NULL;
	device_t *kids;
	struct apc_tbl {
		uint16_t vid;
		uint16_t did;
	} *tp, apc_tbls[] = {
		{ SIS_VENDORID, 0x0965 },
		{ SIS_VENDORID, 0x0966 },
		{ SIS_VENDORID, 0x0968 }
	};
	uint8_t reg;
	int busnum, i, j, numkids;

	pci = devclass_find("pci");
	for (busnum = 0; busnum < devclass_get_maxunit(pci); busnum++) {
		bus = devclass_get_device(pci, busnum);
		if (!bus)
			continue;
		if (device_get_children(bus, &kids, &numkids) != 0)
			continue;
		for (i = 0; i < numkids; i++) {
			dev = kids[i];
			if (pci_get_class(dev) == PCIC_BRIDGE &&
			    pci_get_subclass(dev) == PCIS_BRIDGE_ISA) {
				tp = apc_tbls;
				for (j = 0; j < nitems(apc_tbls); j++) {
					if (pci_get_vendor(dev) == tp->vid &&
					    pci_get_device(dev) == tp->did) {
						free(kids, M_TEMP);
						goto apc_found;
					}
					tp++;
				}
			}
                }
		free(kids, M_TEMP);
	}
	device_printf(sc->sge_dev, "couldn't find PCI-ISA bridge\n");
	return (EINVAL);
apc_found:
	/* Enable port 0x78 and 0x79 to access APC registers. */
	reg = pci_read_config(dev, 0x48, 1);
	pci_write_config(dev, 0x48, reg & ~0x02, 1);
	DELAY(50);
	pci_read_config(dev, 0x48, 1);
	/* Read stored ethernet address. */
	for (i = 0; i < ETHER_ADDR_LEN; i++) {
		outb(0x78, 0x09 + i);
		dest[i] = inb(0x79);
	}
	outb(0x78, 0x12);
	if ((inb(0x79) & 0x80) != 0)
		sc->sge_flags |= SGE_FLAG_RGMII;
	/* Restore access to APC registers. */
	pci_write_config(dev, 0x48, reg, 1);

	return (0);
#else
	return (EINVAL);
#endif
}