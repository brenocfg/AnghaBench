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
typedef  size_t uint32_t ;
struct agp_amd64_softc {int /*<<< orphan*/ * mctrl; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AGP_AMD64_APCTRL ; 
 int AGP_AMD64_APCTRL_SIZE_MASK ; 
 size_t AGP_AMD64_TABLE_SIZE ; 
 size_t* agp_amd64_table ; 
 struct agp_amd64_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int pci_cfgregread (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static uint32_t
agp_amd64_get_aperture(device_t dev)
{
	struct agp_amd64_softc *sc = device_get_softc(dev);
	uint32_t i;

	i = (pci_cfgregread(0, sc->mctrl[0], 3, AGP_AMD64_APCTRL, 4) &
		AGP_AMD64_APCTRL_SIZE_MASK) >> 1;

	if (i >= AGP_AMD64_TABLE_SIZE)
		return (0);

	return (agp_amd64_table[i]);
}