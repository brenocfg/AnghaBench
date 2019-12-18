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
typedef  scalar_t__ u_int32_t ;
struct ata_kauai_softc {int shasta; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {scalar_t__ kpd_devid; int /*<<< orphan*/ * kpd_desc; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int ata_probe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_set_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  bzero (struct ata_kauai_softc*,int) ; 
 struct ata_kauai_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* kauai_pci_devlist ; 
 char* ofw_bus_get_compat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_devid (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int
ata_kauai_probe(device_t dev)
{
	struct ata_kauai_softc *sc;
	u_int32_t devid;
	phandle_t node;
	const char *compatstring = NULL;
	int i, found;

	found = 0;
	devid = pci_get_devid(dev);
        for (i = 0; kauai_pci_devlist[i].kpd_desc != NULL; i++) {
                if (devid == kauai_pci_devlist[i].kpd_devid) {
			found = 1;
                        device_set_desc(dev, kauai_pci_devlist[i].kpd_desc);
		}
	}

	if (!found)
		return (ENXIO);

	node = ofw_bus_get_node(dev);
	sc = device_get_softc(dev);
	bzero(sc, sizeof(struct ata_kauai_softc));

	compatstring = ofw_bus_get_compat(dev);
	if (compatstring != NULL && strcmp(compatstring,"shasta-ata") == 0)
		sc->shasta = 1;

	/* Pre-K2 controllers apparently need this hack */
	if (!sc->shasta &&
	    (compatstring == NULL || strcmp(compatstring, "K2-UATA") != 0))
		bus_set_resource(dev, SYS_RES_IRQ, 0, 39, 1);

        return (ata_probe(dev));
}