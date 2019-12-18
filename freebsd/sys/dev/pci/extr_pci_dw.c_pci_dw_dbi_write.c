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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u_int ;
struct pci_dw_softc {int /*<<< orphan*/  dev; int /*<<< orphan*/ * dbi_res; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  MPASS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_write_1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_write_2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pci_dw_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
pci_dw_dbi_write(device_t dev, u_int reg, uint32_t val, int width)
{
	struct pci_dw_softc *sc;

	sc = device_get_softc(dev);
	MPASS(sc->dbi_res != NULL);

	switch (width) {
	case 4:
		bus_write_4(sc->dbi_res, reg, val);
		break;
	case 2:
		bus_write_2(sc->dbi_res, reg, val);
		break;
	case 1:
		bus_write_1(sc->dbi_res, reg, val);
		break;
	default:
		device_printf(sc->dev, "Unsupported width: %d\n", width);
		break;
	}
}