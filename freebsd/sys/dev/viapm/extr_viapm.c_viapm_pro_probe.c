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
struct viapm_softc {int base; int iorid; void* type; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int VIAPM_8233_BASE ; 
 int VIAPM_BASE_ADDR ; 
 int VIAPM_PRO_BASE ; 
 int VIAPM_PRO_BA_MASK ; 
 int VIAPM_PRO_SMBCTRL ; 
 void* VIAPM_TYP_596B ; 
 void* VIAPM_TYP_686A ; 
 void* VIAPM_TYP_UNKNOWN ; 
#define  VIA_596A_PMU_ID 135 
#define  VIA_596B_PMU_ID 134 
#define  VIA_686A_PMU_ID 133 
#define  VIA_8233A_PMU_ID 132 
#define  VIA_8233_PMU_ID 131 
#define  VIA_8235_PMU_ID 130 
#define  VIA_8237_PMU_ID 129 
#define  VIA_CX700_PMU_ID 128 
 int /*<<< orphan*/  bootverbose ; 
 int /*<<< orphan*/  bus_set_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int pci_get_devid (int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int
viapm_pro_probe(device_t dev)
{
	struct viapm_softc *viapm = (struct viapm_softc *)device_get_softc(dev);
#ifdef VIAPM_BASE_ADDR
	u_int32_t l;
#endif
	u_int32_t base_cfgreg;
	char *desc;

	switch (pci_get_devid(dev)) {
	case VIA_596A_PMU_ID:
		desc = "VIA VT82C596A Power Management Unit";
		viapm->type = VIAPM_TYP_596B;
		base_cfgreg = VIAPM_PRO_BASE;
		goto viapro;

	case VIA_596B_PMU_ID:
		desc = "VIA VT82C596B Power Management Unit";
		viapm->type = VIAPM_TYP_596B;
		base_cfgreg = VIAPM_PRO_BASE;
		goto viapro;

	case VIA_686A_PMU_ID:
		desc = "VIA VT82C686A Power Management Unit";
		viapm->type = VIAPM_TYP_686A;
		base_cfgreg = VIAPM_PRO_BASE;
		goto viapro;

	case VIA_8233_PMU_ID:
	case VIA_8233A_PMU_ID:
		desc = "VIA VT8233 Power Management Unit";
		viapm->type = VIAPM_TYP_UNKNOWN;
		base_cfgreg = VIAPM_8233_BASE;
		goto viapro;

	case VIA_8235_PMU_ID:
		desc = "VIA VT8235 Power Management Unit";
		viapm->type = VIAPM_TYP_UNKNOWN;
		base_cfgreg = VIAPM_8233_BASE;
		goto viapro;

	case VIA_8237_PMU_ID:
		desc = "VIA VT8237 Power Management Unit";
		viapm->type = VIAPM_TYP_UNKNOWN;
		base_cfgreg = VIAPM_8233_BASE;
		goto viapro;

	case VIA_CX700_PMU_ID:
		desc = "VIA CX700 Power Management Unit";
		viapm->type = VIAPM_TYP_UNKNOWN;
		base_cfgreg = VIAPM_8233_BASE;
		goto viapro;

	viapro:

#ifdef VIAPM_BASE_ADDR
		/* force VIAPM I/O base address */

		/* enable the SMBus controller function */
		l = pci_read_config(dev, VIAPM_PRO_SMBCTRL, 1);
		pci_write_config(dev, VIAPM_PRO_SMBCTRL, l | 1, 1);

		/* write the base address */
		pci_write_config(dev, base_cfgreg,
				 VIAPM_BASE_ADDR & VIAPM_PRO_BA_MASK, 4);
#endif

		viapm->base = pci_read_config(dev, base_cfgreg, 4) & VIAPM_PRO_BA_MASK;

		/*
		 * We have to set the I/O resources by hand because it is
		 * described outside the viapmope of the traditional maps
		 */
		viapm->iorid = base_cfgreg;
		if (bus_set_resource(dev, SYS_RES_IOPORT, viapm->iorid,
				     viapm->base, 16)) {
			device_printf(dev, "could not set bus resource 0x%x\n",
					viapm->base);
			return ENXIO;
		}

		if (bootverbose) {
			device_printf(dev, "SMBus I/O base at 0x%x\n", viapm->base);
		}

		device_set_desc(dev, desc);
		return (BUS_PROBE_DEFAULT);

	default:
		break;
	}

	return ENXIO;
}