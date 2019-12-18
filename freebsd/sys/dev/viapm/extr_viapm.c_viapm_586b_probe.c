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
typedef  int u_int8_t ;
typedef  int u_int32_t ;
typedef  int u_int16_t ;
struct viapm_softc {int base; int /*<<< orphan*/  iorid; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  VIAPM_586B_3040E_ACTIV ; 
 int /*<<< orphan*/  VIAPM_586B_3040E_BASE ; 
 int /*<<< orphan*/  VIAPM_586B_3040F_ACTIV ; 
 int /*<<< orphan*/  VIAPM_586B_3040F_BASE ; 
 int VIAPM_586B_BA_MASK ; 
#define  VIAPM_586B_OEM_REV_E 131 
#define  VIAPM_586B_OEM_REV_F 130 
#define  VIAPM_586B_PROD_REV_A 129 
 int /*<<< orphan*/  VIAPM_586B_REVID ; 
 int /*<<< orphan*/  VIAPM_TYP_586B_3040E ; 
 int /*<<< orphan*/  VIAPM_TYP_586B_3040F ; 
#define  VIA_586B_PMU_ID 128 
 int /*<<< orphan*/  bus_set_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  bzero (struct viapm_softc*,int) ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int pci_get_devid (int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
viapm_586b_probe(device_t dev)
{
	struct viapm_softc *viapm = (struct viapm_softc *)device_get_softc(dev);
	u_int32_t l;
	u_int16_t s;
	u_int8_t c;

	switch (pci_get_devid(dev)) {
	case VIA_586B_PMU_ID:

		bzero(viapm, sizeof(struct viapm_softc));

		l = pci_read_config(dev, VIAPM_586B_REVID, 1);
		switch (l) {
		case VIAPM_586B_OEM_REV_E:
			viapm->type = VIAPM_TYP_586B_3040E;
			viapm->iorid = VIAPM_586B_3040E_BASE;

			/* Activate IO block access */
			s = pci_read_config(dev, VIAPM_586B_3040E_ACTIV, 2);
			pci_write_config(dev, VIAPM_586B_3040E_ACTIV, s | 0x1, 2);
			break;

		case VIAPM_586B_OEM_REV_F:
		case VIAPM_586B_PROD_REV_A:
		default:
			viapm->type = VIAPM_TYP_586B_3040F;
			viapm->iorid = VIAPM_586B_3040F_BASE;

			/* Activate IO block access */
			c = pci_read_config(dev, VIAPM_586B_3040F_ACTIV, 1);
			pci_write_config(dev, VIAPM_586B_3040F_ACTIV, c | 0x80, 1);
			break;
		}

		viapm->base = pci_read_config(dev, viapm->iorid, 4) &
				VIAPM_586B_BA_MASK;

		/*
		 * We have to set the I/O resources by hand because it is
		 * described outside the viapmope of the traditional maps
		 */
		if (bus_set_resource(dev, SYS_RES_IOPORT, viapm->iorid,
							viapm->base, 256)) {
			device_printf(dev, "could not set bus resource\n");
			return ENXIO;
		}
		device_set_desc(dev, "VIA VT82C586B Power Management Unit");
		return (BUS_PROBE_DEFAULT);

	default:
		break;
	}

	return ENXIO;
}