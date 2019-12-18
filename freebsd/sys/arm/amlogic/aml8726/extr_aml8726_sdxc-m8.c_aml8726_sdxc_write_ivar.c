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
struct TYPE_3__ {uintptr_t bus_mode; uintptr_t bus_width; uintptr_t chip_select; uintptr_t clock; uintptr_t power_mode; uintptr_t vdd; uintptr_t vccq; uintptr_t timing; } ;
struct TYPE_4__ {uintptr_t mode; uintptr_t ocr; TYPE_1__ ios; } ;
struct aml8726_sdxc_softc {TYPE_2__ host; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
#define  MMCBR_IVAR_BUS_MODE 142 
#define  MMCBR_IVAR_BUS_WIDTH 141 
#define  MMCBR_IVAR_CAPS 140 
#define  MMCBR_IVAR_CHIP_SELECT 139 
#define  MMCBR_IVAR_CLOCK 138 
#define  MMCBR_IVAR_F_MAX 137 
#define  MMCBR_IVAR_F_MIN 136 
#define  MMCBR_IVAR_HOST_OCR 135 
#define  MMCBR_IVAR_MAX_DATA 134 
#define  MMCBR_IVAR_MODE 133 
#define  MMCBR_IVAR_OCR 132 
#define  MMCBR_IVAR_POWER_MODE 131 
#define  MMCBR_IVAR_TIMING 130 
#define  MMCBR_IVAR_VCCQ 129 
#define  MMCBR_IVAR_VDD 128 
 struct aml8726_sdxc_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
aml8726_sdxc_write_ivar(device_t bus, device_t child,
    int which, uintptr_t value)
{
	struct aml8726_sdxc_softc *sc = device_get_softc(bus);

	switch (which) {
	case MMCBR_IVAR_BUS_MODE:
		sc->host.ios.bus_mode = value;
		break;
	case MMCBR_IVAR_BUS_WIDTH:
		sc->host.ios.bus_width = value;
		break;
	case MMCBR_IVAR_CHIP_SELECT:
		sc->host.ios.chip_select = value;
		break;
	case MMCBR_IVAR_CLOCK:
		sc->host.ios.clock = value;
		break;
	case MMCBR_IVAR_MODE:
		sc->host.mode = value;
		break;
	case MMCBR_IVAR_OCR:
		sc->host.ocr = value;
		break;
	case MMCBR_IVAR_POWER_MODE:
		sc->host.ios.power_mode = value;
		break;
	case MMCBR_IVAR_VDD:
		sc->host.ios.vdd = value;
		break;
	case MMCBR_IVAR_VCCQ:
		sc->host.ios.vccq = value;
		break;
	case MMCBR_IVAR_TIMING:
		sc->host.ios.timing = value;
		break;
	/* These are read-only */
	case MMCBR_IVAR_CAPS:
	case MMCBR_IVAR_HOST_OCR:
	case MMCBR_IVAR_F_MIN:
	case MMCBR_IVAR_F_MAX:
	case MMCBR_IVAR_MAX_DATA:
	default:
		return (EINVAL);
	}

	return (0);
}