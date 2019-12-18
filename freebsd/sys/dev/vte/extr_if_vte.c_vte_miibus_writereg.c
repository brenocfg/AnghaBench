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
struct vte_softc {int /*<<< orphan*/  vte_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CSR_READ_2 (struct vte_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_2 (struct vte_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int MMDIO_PHY_ADDR_SHIFT ; 
 int MMDIO_REG_ADDR_SHIFT ; 
 int MMDIO_WRITE ; 
 int /*<<< orphan*/  VTE_MMDIO ; 
 int /*<<< orphan*/  VTE_MMWD ; 
 int VTE_PHY_TIMEOUT ; 
 struct vte_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
vte_miibus_writereg(device_t dev, int phy, int reg, int val)
{
	struct vte_softc *sc;
	int i;

	sc = device_get_softc(dev);

	CSR_WRITE_2(sc, VTE_MMWD, val);
	CSR_WRITE_2(sc, VTE_MMDIO, MMDIO_WRITE |
	    (phy << MMDIO_PHY_ADDR_SHIFT) | (reg << MMDIO_REG_ADDR_SHIFT));
	for (i = VTE_PHY_TIMEOUT; i > 0; i--) {
		DELAY(5);
		if ((CSR_READ_2(sc, VTE_MMDIO) & MMDIO_WRITE) == 0)
			break;
	}

	if (i == 0)
		device_printf(sc->vte_dev, "phy write timeout : %d\n", reg);

	return (0);
}