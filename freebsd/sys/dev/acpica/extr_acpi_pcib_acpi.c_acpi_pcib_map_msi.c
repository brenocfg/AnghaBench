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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct acpi_hpcib_softc {int ap_addr; int /*<<< orphan*/  ap_segment; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ADR_PCI_FUNC (int) ; 
 int /*<<< orphan*/  ACPI_ADR_PCI_SLOT (int) ; 
 int PCIB_MAP_MSI (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * device_get_parent (int /*<<< orphan*/ *) ; 
 struct acpi_hpcib_softc* device_get_softc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pci_find_dbsf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_ht_map_msi (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
acpi_pcib_map_msi(device_t pcib, device_t dev, int irq, uint64_t *addr,
    uint32_t *data)
{
	struct acpi_hpcib_softc *sc;
	device_t bus, hostb;
	int error;

	bus = device_get_parent(pcib);
	error = PCIB_MAP_MSI(device_get_parent(bus), dev, irq, addr, data);
	if (error)
		return (error);

	sc = device_get_softc(pcib);
	if (sc->ap_addr == -1)
		return (0);
	/* XXX: Assumes all bridges are on bus 0. */
	hostb = pci_find_dbsf(sc->ap_segment, 0, ACPI_ADR_PCI_SLOT(sc->ap_addr),
	    ACPI_ADR_PCI_FUNC(sc->ap_addr));
	if (hostb != NULL)
		pci_ht_map_msi(hostb, *addr);
	return (0);
}