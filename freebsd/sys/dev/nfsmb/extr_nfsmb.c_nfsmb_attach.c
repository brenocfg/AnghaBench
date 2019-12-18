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
struct nfsmb_softc {int rid; int /*<<< orphan*/ * subdev; void* smbus; int /*<<< orphan*/  lock; int /*<<< orphan*/ * res; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int NF2PCI_SMBASE_1 ; 
#define  NFSMB_DEVICEID_NF2_SMB 141 
#define  NFSMB_DEVICEID_NF2_ULTRA_SMB 140 
#define  NFSMB_DEVICEID_NF3_250GB_SMB 139 
#define  NFSMB_DEVICEID_NF3_PRO150_SMB 138 
#define  NFSMB_DEVICEID_NF4_04_SMB 137 
#define  NFSMB_DEVICEID_NF4_51_SMB 136 
#define  NFSMB_DEVICEID_NF4_55_SMB 135 
#define  NFSMB_DEVICEID_NF4_61_SMB 134 
#define  NFSMB_DEVICEID_NF4_65_SMB 133 
#define  NFSMB_DEVICEID_NF4_67_SMB 132 
#define  NFSMB_DEVICEID_NF4_73_SMB 131 
#define  NFSMB_DEVICEID_NF4_78S_SMB 130 
#define  NFSMB_DEVICEID_NF4_79_SMB 129 
#define  NFSMB_DEVICEID_NF4_SMB 128 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_attach (int /*<<< orphan*/ ) ; 
 void* device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct nfsmb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsmb_detach (int /*<<< orphan*/ ) ; 
 int pci_get_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfsmb_attach(device_t dev)
{
	struct nfsmb_softc *nfsmb_sc = device_get_softc(dev);

	/* Allocate I/O space */
	nfsmb_sc->rid = NF2PCI_SMBASE_1;

	nfsmb_sc->res = bus_alloc_resource_any(dev, SYS_RES_IOPORT,
		&nfsmb_sc->rid, RF_ACTIVE);

	if (nfsmb_sc->res == NULL) {
		/* Older incarnations of the device used non-standard BARs. */
		nfsmb_sc->rid = 0x50;
		nfsmb_sc->res = bus_alloc_resource_any(dev,
		    SYS_RES_IOPORT, &nfsmb_sc->rid, RF_ACTIVE);
		if (nfsmb_sc->res == NULL) {
			device_printf(dev, "could not map i/o space\n");
			return (ENXIO);
		}
	}

	mtx_init(&nfsmb_sc->lock, device_get_nameunit(dev), "nfsmb", MTX_DEF);

	/* Allocate a new smbus device */
	nfsmb_sc->smbus = device_add_child(dev, "smbus", -1);
	if (!nfsmb_sc->smbus) {
		nfsmb_detach(dev);
		return (EINVAL);
	}

	nfsmb_sc->subdev = NULL;
	switch (pci_get_device(dev)) {
	case NFSMB_DEVICEID_NF2_SMB:
	case NFSMB_DEVICEID_NF2_ULTRA_SMB:
	case NFSMB_DEVICEID_NF3_PRO150_SMB:
	case NFSMB_DEVICEID_NF3_250GB_SMB:
	case NFSMB_DEVICEID_NF4_SMB:
	case NFSMB_DEVICEID_NF4_04_SMB:
	case NFSMB_DEVICEID_NF4_51_SMB:
	case NFSMB_DEVICEID_NF4_55_SMB:
	case NFSMB_DEVICEID_NF4_61_SMB:
	case NFSMB_DEVICEID_NF4_65_SMB:
	case NFSMB_DEVICEID_NF4_67_SMB:
	case NFSMB_DEVICEID_NF4_73_SMB:
	case NFSMB_DEVICEID_NF4_78S_SMB:
	case NFSMB_DEVICEID_NF4_79_SMB:
		/* Trying to add secondary device as slave */
		nfsmb_sc->subdev = device_add_child(dev, "nfsmb", -1);
		if (!nfsmb_sc->subdev) {
			nfsmb_detach(dev);
			return (EINVAL);
		}
		break;
	default:
		break;
	}

	bus_generic_attach(dev);

	return (0);
}