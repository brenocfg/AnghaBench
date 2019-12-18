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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  u_int ;
struct mv_pcib_softc {int /*<<< orphan*/  sc_enable_find_root_slot; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ MV_DEV_ARMADA38X ; 
 scalar_t__ MV_DEV_FAMILY_MASK ; 
 int /*<<< orphan*/  PCIR_DEVICE ; 
 int /*<<< orphan*/  PCIR_DEVICE_LENGTH ; 
 int /*<<< orphan*/  PCIR_VENDOR ; 
 int /*<<< orphan*/  PCIR_VENDOR_LENGTH ; 
 scalar_t__ PCI_VENDORID_MRVL ; 
 struct mv_pcib_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ mv_pcib_hw_cfgread (struct mv_pcib_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mv_pcib_root_slot(device_t dev, u_int bus, u_int slot, u_int func)
{
	struct mv_pcib_softc *sc = device_get_softc(dev);
	uint32_t vendor, device;

	/* On platforms other than Armada38x, root link is always at slot 0 */
	if (!sc->sc_enable_find_root_slot)
		return (slot == 0);

	vendor = mv_pcib_hw_cfgread(sc, bus, slot, func, PCIR_VENDOR,
	    PCIR_VENDOR_LENGTH);
	device = mv_pcib_hw_cfgread(sc, bus, slot, func, PCIR_DEVICE,
	    PCIR_DEVICE_LENGTH) & MV_DEV_FAMILY_MASK;

	return (vendor == PCI_VENDORID_MRVL && device == MV_DEV_ARMADA38X);
}