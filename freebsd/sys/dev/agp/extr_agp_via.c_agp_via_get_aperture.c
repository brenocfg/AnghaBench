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
struct agp_via_softc {int /*<<< orphan*/ * regs; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 size_t REG_APSIZE ; 
 struct agp_via_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * via_v2_regs ; 

__attribute__((used)) static u_int32_t
agp_via_get_aperture(device_t dev)
{
	struct agp_via_softc *sc = device_get_softc(dev);
	u_int32_t apsize;

	if (sc->regs == via_v2_regs) {
		apsize = pci_read_config(dev, sc->regs[REG_APSIZE], 1);

		/*
		 * The size is determined by the number of low bits of
		 * register APBASE which are forced to zero. The low 20 bits
		 * are always forced to zero and each zero bit in the apsize
		 * field just read forces the corresponding bit in the 27:20
		 * to be zero. We calculate the aperture size accordingly.
		 */
		return (((apsize ^ 0xff) << 20) | ((1 << 20) - 1)) + 1;
	} else {
		apsize = pci_read_config(dev, sc->regs[REG_APSIZE], 2) & 0xfff;
		switch (apsize) {
		case 0x800:
			return 0x80000000;
		case 0xc00:
			return 0x40000000;
		case 0xe00:
			return 0x20000000;
		case 0xf00:
			return 0x10000000;
		case 0xf20:
			return 0x08000000;
		case 0xf30:
			return 0x04000000;
		case 0xf38:
			return 0x02000000;
		case 0xf3c:
			return 0x01000000;
		case 0xf3e:
			return 0x00800000;
		case 0xf3f:
			return 0x00400000;
		default:
			device_printf(dev, "Invalid aperture setting 0x%x\n",
			    pci_read_config(dev, sc->regs[REG_APSIZE], 2));
			return 0;
		}
	}
}