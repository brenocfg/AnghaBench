#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct agp_i810_softc {unsigned int stolen_size; unsigned int stolen; TYPE_2__* match; int /*<<< orphan*/  bdev; int /*<<< orphan*/ * sc_res; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_4__ {TYPE_1__* driver; } ;
struct TYPE_3__ {int chiptype; int gen; } ;

/* Variables and functions */
#define  AGP_G33_GCC1_GMS_STOLEN_128M 154 
#define  AGP_G33_GCC1_GMS_STOLEN_256M 153 
 unsigned int AGP_G33_MGGC_GGMS_MASK ; 
#define  AGP_G33_MGGC_GGMS_SIZE_1M 152 
#define  AGP_G33_MGGC_GGMS_SIZE_2M 151 
#define  AGP_G4X_GCC1_GMS_STOLEN_160M 150 
#define  AGP_G4X_GCC1_GMS_STOLEN_224M 149 
#define  AGP_G4X_GCC1_GMS_STOLEN_352M 148 
#define  AGP_G4X_GCC1_GMS_STOLEN_96M 147 
 int /*<<< orphan*/  AGP_I810_PGTBL_CTL ; 
#define  AGP_I810_PGTBL_SIZE_128KB 146 
#define  AGP_I810_PGTBL_SIZE_256KB 145 
#define  AGP_I810_PGTBL_SIZE_512KB 144 
 int AGP_I810_PGTBL_SIZE_MASK ; 
 int /*<<< orphan*/  AGP_I855_GCC1 ; 
 unsigned int AGP_I855_GCC1_GMS ; 
#define  AGP_I855_GCC1_GMS_STOLEN_16M 143 
#define  AGP_I855_GCC1_GMS_STOLEN_1M 142 
#define  AGP_I855_GCC1_GMS_STOLEN_32M 141 
#define  AGP_I855_GCC1_GMS_STOLEN_4M 140 
#define  AGP_I855_GCC1_GMS_STOLEN_8M 139 
#define  AGP_I915_GCC1_GMS_STOLEN_48M 138 
#define  AGP_I915_GCC1_GMS_STOLEN_64M 137 
#define  AGP_I965_PGTBL_SIZE_1MB 136 
#define  AGP_I965_PGTBL_SIZE_1_5MB 135 
#define  AGP_I965_PGTBL_SIZE_2MB 134 
#define  CHIP_G33 133 
#define  CHIP_G4X 132 
#define  CHIP_I855 131 
#define  CHIP_I915 130 
#define  CHIP_I965 129 
#define  CHIP_IGD 128 
 int EINVAL ; 
 int bus_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct agp_i810_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 unsigned int pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
agp_i915_get_stolen_size(device_t dev)
{
	struct agp_i810_softc *sc;
	unsigned int gcc1, stolen, gtt_size;

	sc = device_get_softc(dev);

	/*
	 * Stolen memory is set up at the beginning of the aperture by
	 * the BIOS, consisting of the GATT followed by 4kb for the
	 * BIOS display.
	 */
	switch (sc->match->driver->chiptype) {
	case CHIP_I855:
		gtt_size = 128;
		break;
	case CHIP_I915:
		gtt_size = 256;
		break;
	case CHIP_I965:
		switch (bus_read_4(sc->sc_res[0], AGP_I810_PGTBL_CTL) &
			AGP_I810_PGTBL_SIZE_MASK) {
		case AGP_I810_PGTBL_SIZE_128KB:
			gtt_size = 128;
			break;
		case AGP_I810_PGTBL_SIZE_256KB:
			gtt_size = 256;
			break;
		case AGP_I810_PGTBL_SIZE_512KB:
			gtt_size = 512;
			break;
		case AGP_I965_PGTBL_SIZE_1MB:
			gtt_size = 1024;
			break;
		case AGP_I965_PGTBL_SIZE_2MB:
			gtt_size = 2048;
			break;
		case AGP_I965_PGTBL_SIZE_1_5MB:
			gtt_size = 1024 + 512;
			break;
		default:
			device_printf(dev, "Bad PGTBL size\n");
			return (EINVAL);
		}
		break;
	case CHIP_G33:
		gcc1 = pci_read_config(sc->bdev, AGP_I855_GCC1, 2);
		switch (gcc1 & AGP_G33_MGGC_GGMS_MASK) {
		case AGP_G33_MGGC_GGMS_SIZE_1M:
			gtt_size = 1024;
			break;
		case AGP_G33_MGGC_GGMS_SIZE_2M:
			gtt_size = 2048;
			break;
		default:
			device_printf(dev, "Bad PGTBL size\n");
			return (EINVAL);
		}
		break;
	case CHIP_IGD:
	case CHIP_G4X:
		gtt_size = 0;
		break;
	default:
		device_printf(dev, "Bad chiptype\n");
		return (EINVAL);
	}

	/* GCC1 is called MGGC on i915+ */
	gcc1 = pci_read_config(sc->bdev, AGP_I855_GCC1, 1);
	switch (gcc1 & AGP_I855_GCC1_GMS) {
	case AGP_I855_GCC1_GMS_STOLEN_1M:
		stolen = 1024;
		break;
	case AGP_I855_GCC1_GMS_STOLEN_4M:
		stolen = 4 * 1024;
		break;
	case AGP_I855_GCC1_GMS_STOLEN_8M:
		stolen = 8 * 1024;
		break;
	case AGP_I855_GCC1_GMS_STOLEN_16M:
		stolen = 16 * 1024;
		break;
	case AGP_I855_GCC1_GMS_STOLEN_32M:
		stolen = 32 * 1024;
		break;
	case AGP_I915_GCC1_GMS_STOLEN_48M:
		stolen = sc->match->driver->gen > 2 ? 48 * 1024 : 0;
		break;
	case AGP_I915_GCC1_GMS_STOLEN_64M:
		stolen = sc->match->driver->gen > 2 ? 64 * 1024 : 0;
		break;
	case AGP_G33_GCC1_GMS_STOLEN_128M:
		stolen = sc->match->driver->gen > 2 ? 128 * 1024 : 0;
		break;
	case AGP_G33_GCC1_GMS_STOLEN_256M:
		stolen = sc->match->driver->gen > 2 ? 256 * 1024 : 0;
		break;
	case AGP_G4X_GCC1_GMS_STOLEN_96M:
		if (sc->match->driver->chiptype == CHIP_I965 ||
		    sc->match->driver->chiptype == CHIP_G4X)
			stolen = 96 * 1024;
		else
			stolen = 0;
		break;
	case AGP_G4X_GCC1_GMS_STOLEN_160M:
		if (sc->match->driver->chiptype == CHIP_I965 ||
		    sc->match->driver->chiptype == CHIP_G4X)
			stolen = 160 * 1024;
		else
			stolen = 0;
		break;
	case AGP_G4X_GCC1_GMS_STOLEN_224M:
		if (sc->match->driver->chiptype == CHIP_I965 ||
		    sc->match->driver->chiptype == CHIP_G4X)
			stolen = 224 * 1024;
		else
			stolen = 0;
		break;
	case AGP_G4X_GCC1_GMS_STOLEN_352M:
		if (sc->match->driver->chiptype == CHIP_I965 ||
		    sc->match->driver->chiptype == CHIP_G4X)
			stolen = 352 * 1024;
		else
			stolen = 0;
		break;
	default:
		device_printf(dev,
		    "unknown memory configuration, disabling (GCC1 %x)\n",
		    gcc1);
		return (EINVAL);
	}

	gtt_size += 4;
	sc->stolen_size = stolen * 1024;
	sc->stolen = (stolen - gtt_size) * 1024 / 4096;

	return (0);
}