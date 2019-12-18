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
struct TYPE_2__ {int /*<<< orphan*/  sc_mode; } ;
struct dwc_otg_fdt_softc {TYPE_1__ sc_otg; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_MODE_HOST ; 
 struct dwc_otg_fdt_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int dwc_otg_attach (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
hisi_dwc_otg_attach(device_t dev)
{
	struct dwc_otg_fdt_softc *sc;

	/* Set the default to host mode. */
	/* TODO: Use vbus to detect this. */
	sc = device_get_softc(dev);
	sc->sc_otg.sc_mode = DWC_MODE_HOST;

	return (dwc_otg_attach(dev));
}