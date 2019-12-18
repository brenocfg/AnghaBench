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
struct TYPE_3__ {int bus_mode; int bus_width; int chip_select; int clock; int power_mode; int vdd; int vccq; int timing; } ;
struct TYPE_4__ {int f_min; int f_max; int host_ocr; int mode; int ocr; int caps; TYPE_1__ ios; } ;
struct dwmmc_softc {int desc_count; TYPE_2__ host; } ;
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
 struct dwmmc_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dwmmc_read_ivar(device_t bus, device_t child, int which, uintptr_t *result)
{
	struct dwmmc_softc *sc;

	sc = device_get_softc(bus);

	switch (which) {
	default:
		return (EINVAL);
	case MMCBR_IVAR_BUS_MODE:
		*(int *)result = sc->host.ios.bus_mode;
		break;
	case MMCBR_IVAR_BUS_WIDTH:
		*(int *)result = sc->host.ios.bus_width;
		break;
	case MMCBR_IVAR_CHIP_SELECT:
		*(int *)result = sc->host.ios.chip_select;
		break;
	case MMCBR_IVAR_CLOCK:
		*(int *)result = sc->host.ios.clock;
		break;
	case MMCBR_IVAR_F_MIN:
		*(int *)result = sc->host.f_min;
		break;
	case MMCBR_IVAR_F_MAX:
		*(int *)result = sc->host.f_max;
		break;
	case MMCBR_IVAR_HOST_OCR:
		*(int *)result = sc->host.host_ocr;
		break;
	case MMCBR_IVAR_MODE:
		*(int *)result = sc->host.mode;
		break;
	case MMCBR_IVAR_OCR:
		*(int *)result = sc->host.ocr;
		break;
	case MMCBR_IVAR_POWER_MODE:
		*(int *)result = sc->host.ios.power_mode;
		break;
	case MMCBR_IVAR_VDD:
		*(int *)result = sc->host.ios.vdd;
		break;
	case MMCBR_IVAR_VCCQ:
		*(int *)result = sc->host.ios.vccq;
		break;
	case MMCBR_IVAR_CAPS:
		*(int *)result = sc->host.caps;
		break;
	case MMCBR_IVAR_MAX_DATA:
		*(int *)result = sc->desc_count;
		break;
	case MMCBR_IVAR_TIMING:
		*(int *)result = sc->host.ios.timing;
		break;
	}
	return (0);
}