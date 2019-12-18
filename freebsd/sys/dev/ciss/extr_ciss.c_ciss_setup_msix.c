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
struct ciss_softc {int ciss_msi; int* ciss_irq_rid; int /*<<< orphan*/  ciss_dev; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int CISS_BOARD_NOMSI ; 
 int CISS_MSI_COUNT ; 
 int EINVAL ; 
 int MIN (int,int) ; 
 scalar_t__ bootverbose ; 
 int ciss_lookup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ciss_printf (struct ciss_softc*,char*,int,char*) ; 
 TYPE_1__* ciss_vendor_data ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ pci_alloc_msi (int /*<<< orphan*/ ,int*) ; 
 scalar_t__ pci_alloc_msix (int /*<<< orphan*/ ,int*) ; 
 int pci_msi_count (int /*<<< orphan*/ ) ; 
 int pci_msix_count (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ciss_setup_msix(struct ciss_softc *sc)
{
    int val, i;

    /* Weed out devices that don't actually support MSI */
    i = ciss_lookup(sc->ciss_dev);
    if (ciss_vendor_data[i].flags & CISS_BOARD_NOMSI)
	return (EINVAL);

    /*
     * Only need to use the minimum number of MSI vectors, as the driver
     * doesn't support directed MSIX interrupts.
     */
    val = pci_msix_count(sc->ciss_dev);
    if (val < CISS_MSI_COUNT) {
	val = pci_msi_count(sc->ciss_dev);
	device_printf(sc->ciss_dev, "got %d MSI messages]\n", val);
	if (val < CISS_MSI_COUNT)
	    return (EINVAL);
    }
    val = MIN(val, CISS_MSI_COUNT);
    if (pci_alloc_msix(sc->ciss_dev, &val) != 0) {
	if (pci_alloc_msi(sc->ciss_dev, &val) != 0)
	    return (EINVAL);
    }

    sc->ciss_msi = val;
    if (bootverbose)
	ciss_printf(sc, "Using %d MSIX interrupt%s\n", val,
	    (val != 1) ? "s" : "");

    for (i = 0; i < val; i++)
	sc->ciss_irq_rid[i] = i + 1;

    return (0);

}