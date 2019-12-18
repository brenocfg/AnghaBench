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
typedef  int uint32_t ;
struct tegra_pcib_softc {int /*<<< orphan*/  msi_intr_cookie; int /*<<< orphan*/  msi_irq_res; int /*<<< orphan*/  msi_page; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AFI_INTR_MASK ; 
 int AFI_INTR_MASK_MSI_MASK ; 
 int /*<<< orphan*/  AFI_MSI_EN_VEC (int) ; 
 int AFI_MSI_REGS ; 
 int /*<<< orphan*/  AFI_MSI_VEC (int) ; 
 int AFI_RD4 (struct tegra_pcib_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AFI_WR4 (struct tegra_pcib_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int ENXIO ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_BIO ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  VM_MEMATTR_DEFAULT ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct tegra_pcib_softc*,int /*<<< orphan*/ *) ; 
 struct tegra_pcib_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kmem_alloc_contig (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ tegra_pcib_msi_attach (struct tegra_pcib_softc*) ; 
 int /*<<< orphan*/  tegra_pcib_msi_detach (struct tegra_pcib_softc*) ; 
 int /*<<< orphan*/  tegra_pcib_msi_intr ; 
 int /*<<< orphan*/  tegra_pcib_set_bar (struct tegra_pcib_softc*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtophys (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tegra_pcib_attach_msi(device_t dev)
{
	struct tegra_pcib_softc *sc;
	uint32_t reg;
	int i, rv;

	sc = device_get_softc(dev);

	sc->msi_page = kmem_alloc_contig(PAGE_SIZE, M_WAITOK, 0,
	    BUS_SPACE_MAXADDR, PAGE_SIZE, 0, VM_MEMATTR_DEFAULT);

	/* MSI BAR */
	tegra_pcib_set_bar(sc, 9, vtophys(sc->msi_page), vtophys(sc->msi_page),
	    PAGE_SIZE, 0);

	/* Disble and clear all interrupts. */
	for (i = 0; i < AFI_MSI_REGS; i++) {
		AFI_WR4(sc, AFI_MSI_EN_VEC(i), 0);
		AFI_WR4(sc, AFI_MSI_VEC(i), 0xFFFFFFFF);
	}
	rv = bus_setup_intr(dev, sc->msi_irq_res, INTR_TYPE_BIO | INTR_MPSAFE,
	    tegra_pcib_msi_intr, NULL, sc, &sc->msi_intr_cookie);
	if (rv != 0) {
		device_printf(dev, "cannot setup MSI interrupt handler\n");
		rv = ENXIO;
		goto out;
	}

	if (tegra_pcib_msi_attach(sc) != 0) {
		device_printf(dev, "WARNING: unable to attach PIC\n");
		tegra_pcib_msi_detach(sc);
		goto out;
	}

	/* Unmask  MSI interrupt. */
	reg = AFI_RD4(sc, AFI_INTR_MASK);
	reg |= AFI_INTR_MASK_MSI_MASK;
	AFI_WR4(sc, AFI_INTR_MASK, reg);

out:
	return (rv);
}