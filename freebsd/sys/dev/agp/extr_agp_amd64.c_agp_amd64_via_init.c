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
struct agp_amd64_softc {TYPE_1__* gatt; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int ag_physical; } ;

/* Variables and functions */
 int /*<<< orphan*/  AGP3_VIA_ATTBASE ; 
 int /*<<< orphan*/  AGP3_VIA_GARTCTRL ; 
 int /*<<< orphan*/  agp_amd64_apbase_fixup (int /*<<< orphan*/ ) ; 
 struct agp_amd64_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int pci_cfgregread (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_cfgregwrite (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
agp_amd64_via_init(device_t dev)
{
	struct agp_amd64_softc *sc = device_get_softc(dev);

	agp_amd64_apbase_fixup(dev);
	pci_cfgregwrite(0, 1, 0, AGP3_VIA_ATTBASE, sc->gatt->ag_physical, 4);
	pci_cfgregwrite(0, 1, 0, AGP3_VIA_GARTCTRL,
	    pci_cfgregread(0, 1, 0, AGP3_VIA_ATTBASE, 4) | 0x180, 4);
}