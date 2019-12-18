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
typedef  int u_int32_t ;
struct agp_intel_softc {int aperture_mask; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AGP_INTEL_APSIZE ; 
 struct agp_intel_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u_int32_t
agp_intel_get_aperture(device_t dev)
{
	struct agp_intel_softc *sc;
	u_int32_t apsize;

	sc = device_get_softc(dev);

	apsize = pci_read_config(dev, AGP_INTEL_APSIZE, 1) & sc->aperture_mask;

	/*
	 * The size is determined by the number of low bits of
	 * register APBASE which are forced to zero. The low 22 bits
	 * are always forced to zero and each zero bit in the apsize
	 * field just read forces the corresponding bit in the 27:22
	 * to be zero. We calculate the aperture size accordingly.
	 */
	return ((((apsize ^ sc->aperture_mask) << 22) | ((1 << 22) - 1)) + 1);
}