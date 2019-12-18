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
typedef  int /*<<< orphan*/  u_int ;
struct pci_dw_softc {int /*<<< orphan*/  dev; int /*<<< orphan*/ * dbi_res; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  MPASS (int /*<<< orphan*/ ) ; 
 int bus_read_1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int bus_read_2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int bus_read_4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct pci_dw_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static uint32_t
pci_dw_dbi_read(device_t dev, u_int reg, int width)
{
	struct pci_dw_softc *sc;

	sc = device_get_softc(dev);
	MPASS(sc->dbi_res != NULL);

	switch (width) {
	case 4:
		return (bus_read_4(sc->dbi_res, reg));
	case 2:
		return (bus_read_2(sc->dbi_res, reg));
	case 1:
		return (bus_read_1(sc->dbi_res, reg));
	default:
		device_printf(sc->dev, "Unsupported width: %d\n", width);
		return (0xFFFFFFFF);
	}
}