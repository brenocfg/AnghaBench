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
struct agp_amd64_softc {int apbase; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AGP_AMD64_NVIDIA_0_APBASE ; 
 int /*<<< orphan*/  AGP_AMD64_NVIDIA_1_APBASE1 ; 
 int /*<<< orphan*/  AGP_AMD64_NVIDIA_1_APBASE2 ; 
 int /*<<< orphan*/  agp_amd64_apbase_fixup (int /*<<< orphan*/ ) ; 
 struct agp_amd64_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_cfgregwrite (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
agp_amd64_nvidia_init(device_t dev)
{
	struct agp_amd64_softc *sc = device_get_softc(dev);

	agp_amd64_apbase_fixup(dev);
	pci_write_config(dev, AGP_AMD64_NVIDIA_0_APBASE,
	    (pci_read_config(dev, AGP_AMD64_NVIDIA_0_APBASE, 4) & 0x0000000f) |
	    sc->apbase, 4);
	pci_cfgregwrite(0, 11, 0, AGP_AMD64_NVIDIA_1_APBASE1, sc->apbase, 4);
	pci_cfgregwrite(0, 11, 0, AGP_AMD64_NVIDIA_1_APBASE2, sc->apbase, 4);
}