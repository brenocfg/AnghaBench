#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int bus_mode; int bus_width; int chip_select; int clock; int power_mode; int vdd; int vccq; int timing; } ;
struct TYPE_5__ {int f_min; int f_max; int host_ocr; int mode; int ocr; int caps; TYPE_1__ ios; } ;
struct aw_mmc_softc {TYPE_3__* aw_mmc_conf; TYPE_2__ aw_host; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_6__ {int dma_xferlen; } ;

/* Variables and functions */
 int AW_MMC_DMA_SEGS ; 
 int EINVAL ; 
#define  MMCBR_IVAR_BUS_MODE 143 
#define  MMCBR_IVAR_BUS_WIDTH 142 
#define  MMCBR_IVAR_CAPS 141 
#define  MMCBR_IVAR_CHIP_SELECT 140 
#define  MMCBR_IVAR_CLOCK 139 
#define  MMCBR_IVAR_F_MAX 138 
#define  MMCBR_IVAR_F_MIN 137 
#define  MMCBR_IVAR_HOST_OCR 136 
#define  MMCBR_IVAR_MAX_DATA 135 
#define  MMCBR_IVAR_MODE 134 
#define  MMCBR_IVAR_OCR 133 
#define  MMCBR_IVAR_POWER_MODE 132 
#define  MMCBR_IVAR_RETUNE_REQ 131 
#define  MMCBR_IVAR_TIMING 130 
#define  MMCBR_IVAR_VCCQ 129 
#define  MMCBR_IVAR_VDD 128 
 int MMC_SECTOR_SIZE ; 
 struct aw_mmc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int retune_req_none ; 

__attribute__((used)) static int
aw_mmc_read_ivar(device_t bus, device_t child, int which,
    uintptr_t *result)
{
	struct aw_mmc_softc *sc;

	sc = device_get_softc(bus);
	switch (which) {
	default:
		return (EINVAL);
	case MMCBR_IVAR_BUS_MODE:
		*(int *)result = sc->aw_host.ios.bus_mode;
		break;
	case MMCBR_IVAR_BUS_WIDTH:
		*(int *)result = sc->aw_host.ios.bus_width;
		break;
	case MMCBR_IVAR_CHIP_SELECT:
		*(int *)result = sc->aw_host.ios.chip_select;
		break;
	case MMCBR_IVAR_CLOCK:
		*(int *)result = sc->aw_host.ios.clock;
		break;
	case MMCBR_IVAR_F_MIN:
		*(int *)result = sc->aw_host.f_min;
		break;
	case MMCBR_IVAR_F_MAX:
		*(int *)result = sc->aw_host.f_max;
		break;
	case MMCBR_IVAR_HOST_OCR:
		*(int *)result = sc->aw_host.host_ocr;
		break;
	case MMCBR_IVAR_MODE:
		*(int *)result = sc->aw_host.mode;
		break;
	case MMCBR_IVAR_OCR:
		*(int *)result = sc->aw_host.ocr;
		break;
	case MMCBR_IVAR_POWER_MODE:
		*(int *)result = sc->aw_host.ios.power_mode;
		break;
	case MMCBR_IVAR_VDD:
		*(int *)result = sc->aw_host.ios.vdd;
		break;
	case MMCBR_IVAR_VCCQ:
		*(int *)result = sc->aw_host.ios.vccq;
		break;
	case MMCBR_IVAR_CAPS:
		*(int *)result = sc->aw_host.caps;
		break;
	case MMCBR_IVAR_TIMING:
		*(int *)result = sc->aw_host.ios.timing;
		break;
	case MMCBR_IVAR_MAX_DATA:
		*(int *)result = (sc->aw_mmc_conf->dma_xferlen *
		    AW_MMC_DMA_SEGS) / MMC_SECTOR_SIZE;
		break;
	case MMCBR_IVAR_RETUNE_REQ:
		*(int *)result = retune_req_none;
		break;
	}

	return (0);
}