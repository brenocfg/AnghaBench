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
struct TYPE_3__ {int bus_mode; int bus_width; int chip_select; int clock; int power_mode; int vdd; uintptr_t vccq; int timing; } ;
struct TYPE_4__ {int f_min; int f_max; int host_ocr; int mode; int ocr; int caps; TYPE_1__ ios; } ;
struct jz4780_mmc_softc {TYPE_2__ sc_host; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
#define  MMCBR_IVAR_BUS_MODE 144 
#define  MMCBR_IVAR_BUS_WIDTH 143 
#define  MMCBR_IVAR_CAPS 142 
#define  MMCBR_IVAR_CHIP_SELECT 141 
#define  MMCBR_IVAR_CLOCK 140 
#define  MMCBR_IVAR_F_MAX 139 
#define  MMCBR_IVAR_F_MIN 138 
#define  MMCBR_IVAR_HOST_OCR 137 
#define  MMCBR_IVAR_MAX_BUSY_TIMEOUT 136 
#define  MMCBR_IVAR_MAX_DATA 135 
#define  MMCBR_IVAR_MODE 134 
#define  MMCBR_IVAR_OCR 133 
#define  MMCBR_IVAR_POWER_MODE 132 
#define  MMCBR_IVAR_RETUNE_REQ 131 
#define  MMCBR_IVAR_TIMING 130 
#define  MMCBR_IVAR_VCCQ 129 
#define  MMCBR_IVAR_VDD 128 
 struct jz4780_mmc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int retune_req_none ; 

__attribute__((used)) static int
jz4780_mmc_read_ivar(device_t bus, device_t child, int which,
    uintptr_t *result)
{
	struct jz4780_mmc_softc *sc;

	sc = device_get_softc(bus);
	switch (which) {
	default:
		return (EINVAL);
	case MMCBR_IVAR_BUS_MODE:
		*(int *)result = sc->sc_host.ios.bus_mode;
		break;
	case MMCBR_IVAR_BUS_WIDTH:
		*(int *)result = sc->sc_host.ios.bus_width;
		break;
	case MMCBR_IVAR_CHIP_SELECT:
		*(int *)result = sc->sc_host.ios.chip_select;
		break;
	case MMCBR_IVAR_CLOCK:
		*(int *)result = sc->sc_host.ios.clock;
		break;
	case MMCBR_IVAR_F_MIN:
		*(int *)result = sc->sc_host.f_min;
		break;
	case MMCBR_IVAR_F_MAX:
		*(int *)result = sc->sc_host.f_max;
		break;
	case MMCBR_IVAR_HOST_OCR:
		*(int *)result = sc->sc_host.host_ocr;
		break;
	case MMCBR_IVAR_MODE:
		*(int *)result = sc->sc_host.mode;
		break;
	case MMCBR_IVAR_OCR:
		*(int *)result = sc->sc_host.ocr;
		break;
	case MMCBR_IVAR_POWER_MODE:
		*(int *)result = sc->sc_host.ios.power_mode;
		break;
	case MMCBR_IVAR_RETUNE_REQ:
		*(int *)result = retune_req_none;
		break;
	case MMCBR_IVAR_VDD:
		*(int *)result = sc->sc_host.ios.vdd;
		break;
	case MMCBR_IVAR_VCCQ:
		*result = sc->sc_host.ios.vccq;
		break;
	case MMCBR_IVAR_CAPS:
		*(int *)result = sc->sc_host.caps;
		break;
	case MMCBR_IVAR_TIMING:
		*(int *)result = sc->sc_host.ios.timing;
		break;
	case MMCBR_IVAR_MAX_DATA:
		*(int *)result = 65535;
		break;
	case MMCBR_IVAR_MAX_BUSY_TIMEOUT:
		*(int *)result = 1000000;	/* 1s max */
		break;
	}

	return (0);
}