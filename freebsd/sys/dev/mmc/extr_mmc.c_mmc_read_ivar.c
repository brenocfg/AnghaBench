#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {uintptr_t spec_vers; uintptr_t dsr_imp; } ;
struct mmc_ivars {uintptr_t sec_count; uintptr_t rca; uintptr_t read_only; uintptr_t high_cap; uintptr_t mode; uintptr_t bus_width; uintptr_t erase_sector; uintptr_t cmd6_time; uintptr_t quirks; char* card_id_string; char* card_sn_string; TYPE_1__ csd; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
#define  MMC_IVAR_BUS_WIDTH 143 
#define  MMC_IVAR_CARD_ID_STRING 142 
#define  MMC_IVAR_CARD_SN_STRING 141 
#define  MMC_IVAR_CARD_TYPE 140 
#define  MMC_IVAR_CMD6_TIMEOUT 139 
#define  MMC_IVAR_DSR_IMP 138 
#define  MMC_IVAR_ERASE_SECTOR 137 
#define  MMC_IVAR_HIGH_CAP 136 
#define  MMC_IVAR_MAX_DATA 135 
#define  MMC_IVAR_MEDIA_SIZE 134 
#define  MMC_IVAR_QUIRKS 133 
#define  MMC_IVAR_RCA 132 
#define  MMC_IVAR_READ_ONLY 131 
#define  MMC_IVAR_SECTOR_SIZE 130 
#define  MMC_IVAR_SPEC_VERS 129 
#define  MMC_IVAR_TRAN_SPEED 128 
 uintptr_t MMC_SECTOR_SIZE ; 
 struct mmc_ivars* device_get_ivars (int /*<<< orphan*/ ) ; 
 uintptr_t mmcbr_get_clock (int /*<<< orphan*/ ) ; 
 uintptr_t mmcbr_get_max_data (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mmc_read_ivar(device_t bus, device_t child, int which, uintptr_t *result)
{
	struct mmc_ivars *ivar = device_get_ivars(child);

	switch (which) {
	default:
		return (EINVAL);
	case MMC_IVAR_SPEC_VERS:
		*result = ivar->csd.spec_vers;
		break;
	case MMC_IVAR_DSR_IMP:
		*result = ivar->csd.dsr_imp;
		break;
	case MMC_IVAR_MEDIA_SIZE:
		*result = ivar->sec_count;
		break;
	case MMC_IVAR_RCA:
		*result = ivar->rca;
		break;
	case MMC_IVAR_SECTOR_SIZE:
		*result = MMC_SECTOR_SIZE;
		break;
	case MMC_IVAR_TRAN_SPEED:
		*result = mmcbr_get_clock(bus);
		break;
	case MMC_IVAR_READ_ONLY:
		*result = ivar->read_only;
		break;
	case MMC_IVAR_HIGH_CAP:
		*result = ivar->high_cap;
		break;
	case MMC_IVAR_CARD_TYPE:
		*result = ivar->mode;
		break;
	case MMC_IVAR_BUS_WIDTH:
		*result = ivar->bus_width;
		break;
	case MMC_IVAR_ERASE_SECTOR:
		*result = ivar->erase_sector;
		break;
	case MMC_IVAR_MAX_DATA:
		*result = mmcbr_get_max_data(bus);
		break;
	case MMC_IVAR_CMD6_TIMEOUT:
		*result = ivar->cmd6_time;
		break;
	case MMC_IVAR_QUIRKS:
		*result = ivar->quirks;
		break;
	case MMC_IVAR_CARD_ID_STRING:
		*(char **)result = ivar->card_id_string;
		break;
	case MMC_IVAR_CARD_SN_STRING:
		*(char **)result = ivar->card_sn_string;
		break;
	}
	return (0);
}