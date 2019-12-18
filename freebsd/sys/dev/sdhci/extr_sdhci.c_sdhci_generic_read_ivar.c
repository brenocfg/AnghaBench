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
struct TYPE_4__ {uintptr_t f_min; uintptr_t f_max; uintptr_t host_ocr; uintptr_t mode; uintptr_t ocr; uintptr_t caps; TYPE_1__ ios; } ;
struct sdhci_slot {int opt; int retune_req; int /*<<< orphan*/  retune_mode; TYPE_2__ host; } ;
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
 int MMC_SECTOR_SIZE ; 
 int /*<<< orphan*/  SDHCI_RETUNE_MODE_1 ; 
 int /*<<< orphan*/  SDHCI_RETUNE_MODE_2 ; 
 int SDHCI_RETUNE_REQ_NEEDED ; 
 int SDHCI_RETUNE_REQ_RESET ; 
 int SDHCI_TUNING_ENABLED ; 
 struct sdhci_slot* device_get_ivars (int /*<<< orphan*/ ) ; 
 uintptr_t retune_req_none ; 
 uintptr_t retune_req_normal ; 
 uintptr_t retune_req_reset ; 

int
sdhci_generic_read_ivar(device_t bus, device_t child, int which,
    uintptr_t *result)
{
	const struct sdhci_slot *slot = device_get_ivars(child);

	switch (which) {
	default:
		return (EINVAL);
	case MMCBR_IVAR_BUS_MODE:
		*result = slot->host.ios.bus_mode;
		break;
	case MMCBR_IVAR_BUS_WIDTH:
		*result = slot->host.ios.bus_width;
		break;
	case MMCBR_IVAR_CHIP_SELECT:
		*result = slot->host.ios.chip_select;
		break;
	case MMCBR_IVAR_CLOCK:
		*result = slot->host.ios.clock;
		break;
	case MMCBR_IVAR_F_MIN:
		*result = slot->host.f_min;
		break;
	case MMCBR_IVAR_F_MAX:
		*result = slot->host.f_max;
		break;
	case MMCBR_IVAR_HOST_OCR:
		*result = slot->host.host_ocr;
		break;
	case MMCBR_IVAR_MODE:
		*result = slot->host.mode;
		break;
	case MMCBR_IVAR_OCR:
		*result = slot->host.ocr;
		break;
	case MMCBR_IVAR_POWER_MODE:
		*result = slot->host.ios.power_mode;
		break;
	case MMCBR_IVAR_VDD:
		*result = slot->host.ios.vdd;
		break;
	case MMCBR_IVAR_RETUNE_REQ:
		if (slot->opt & SDHCI_TUNING_ENABLED) {
			if (slot->retune_req & SDHCI_RETUNE_REQ_RESET) {
				*result = retune_req_reset;
				break;
			}
			if (slot->retune_req & SDHCI_RETUNE_REQ_NEEDED) {
				*result = retune_req_normal;
				break;
			}
		}
		*result = retune_req_none;
		break;
	case MMCBR_IVAR_VCCQ:
		*result = slot->host.ios.vccq;
		break;
	case MMCBR_IVAR_CAPS:
		*result = slot->host.caps;
		break;
	case MMCBR_IVAR_TIMING:
		*result = slot->host.ios.timing;
		break;
	case MMCBR_IVAR_MAX_DATA:
		/*
		 * Re-tuning modes 1 and 2 restrict the maximum data length
		 * per read/write command to 4 MiB.
		 */
		if (slot->opt & SDHCI_TUNING_ENABLED &&
		    (slot->retune_mode == SDHCI_RETUNE_MODE_1 ||
		    slot->retune_mode == SDHCI_RETUNE_MODE_2)) {
			*result = 4 * 1024 * 1024 / MMC_SECTOR_SIZE;
			break;
		}
		*result = 65535;
		break;
	case MMCBR_IVAR_MAX_BUSY_TIMEOUT:
		/*
		 * Currently, sdhci_start_data() hardcodes 1 s for all CMDs.
		 */
		*result = 1000000;
		break;
	}
	return (0);
}