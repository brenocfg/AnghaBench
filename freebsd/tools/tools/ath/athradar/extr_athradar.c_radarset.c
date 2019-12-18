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
typedef  void* u_int32_t ;
struct TYPE_4__ {int ad_id; int ad_in_size; int /*<<< orphan*/  ad_name; scalar_t__ ad_in_data; scalar_t__ ad_out_size; int /*<<< orphan*/ * ad_out_data; } ;
struct radarhandler {TYPE_2__ atd; int /*<<< orphan*/  s; } ;
typedef  scalar_t__ caddr_t ;
struct TYPE_3__ {void* pe_en_relstep_check; void* pe_enrelpwr; void* pe_extchannel; void* pe_enmaxrssi; void* pe_blockradar; void* pe_usefir128; void* pe_maxlen; void* pe_relstep; void* pe_relpwr; void* pe_inband; void* pe_prssi; void* pe_height; void* pe_rrssi; void* pe_firpwr; void* pe_enabled; } ;
typedef  TYPE_1__ HAL_PHYERR_PARAM ;

/* Variables and functions */
 int ATH_DIAG_IN ; 
#define  DFS_PARAM_BLOCKRADAR 142 
#define  DFS_PARAM_ENABLE 141 
#define  DFS_PARAM_EN_EXTCH 140 
#define  DFS_PARAM_FIRPWR 139 
#define  DFS_PARAM_HEIGHT 138 
#define  DFS_PARAM_INBAND 137 
#define  DFS_PARAM_MAXLEN 136 
#define  DFS_PARAM_MAXRSSI_EN 135 
#define  DFS_PARAM_PRSSI 134 
#define  DFS_PARAM_RELPWR 133 
#define  DFS_PARAM_RELPWR_EN 132 
#define  DFS_PARAM_RELSTEP 131 
#define  DFS_PARAM_RELSTEP_EN 130 
#define  DFS_PARAM_RRSSI 129 
#define  DFS_PARAM_USEFIR128 128 
 int DFS_SET_THRESH ; 
 void* HAL_PHYERR_PARAM_NOVAL ; 
 int /*<<< orphan*/  SIOCGATHPHYERR ; 
 int /*<<< orphan*/  err (int,int /*<<< orphan*/ ) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 

void
radarset(struct radarhandler *radar, int op, u_int32_t param)
{
	HAL_PHYERR_PARAM pe;

	pe.pe_firpwr = HAL_PHYERR_PARAM_NOVAL;
	pe.pe_rrssi = HAL_PHYERR_PARAM_NOVAL;
	pe.pe_height = HAL_PHYERR_PARAM_NOVAL;
	pe.pe_prssi = HAL_PHYERR_PARAM_NOVAL;
	pe.pe_inband = HAL_PHYERR_PARAM_NOVAL;
	pe.pe_enabled = HAL_PHYERR_PARAM_NOVAL;

	pe.pe_relpwr = HAL_PHYERR_PARAM_NOVAL;
	pe.pe_relstep = HAL_PHYERR_PARAM_NOVAL;
	pe.pe_maxlen = HAL_PHYERR_PARAM_NOVAL;
	pe.pe_usefir128 = HAL_PHYERR_PARAM_NOVAL;
	pe.pe_blockradar = HAL_PHYERR_PARAM_NOVAL;
	pe.pe_enmaxrssi = HAL_PHYERR_PARAM_NOVAL;

	pe.pe_extchannel = HAL_PHYERR_PARAM_NOVAL;
	pe.pe_enrelpwr = HAL_PHYERR_PARAM_NOVAL;
	pe.pe_en_relstep_check = HAL_PHYERR_PARAM_NOVAL;

	switch (op) {
	case DFS_PARAM_ENABLE:
		pe.pe_enabled = param;
		break;
	case DFS_PARAM_FIRPWR:
		pe.pe_firpwr = param;
		break;
	case DFS_PARAM_RRSSI:
		pe.pe_rrssi = param;
		break;
	case DFS_PARAM_HEIGHT:
		pe.pe_height = param;
		break;
	case DFS_PARAM_PRSSI:
		pe.pe_prssi = param;
		break;
	case DFS_PARAM_INBAND:
		pe.pe_inband = param;
		break;
	case DFS_PARAM_RELPWR:
		pe.pe_relpwr = param;
		break;
	case DFS_PARAM_RELSTEP:
		pe.pe_relstep = param;
		break;
	case DFS_PARAM_MAXLEN:
		pe.pe_maxlen = param;
		break;
	case DFS_PARAM_USEFIR128:
		pe.pe_usefir128 = param;
		break;
	case DFS_PARAM_BLOCKRADAR:
		pe.pe_blockradar = param;
		break;
	case DFS_PARAM_MAXRSSI_EN:
		pe.pe_enmaxrssi = param;
		break;
	case DFS_PARAM_EN_EXTCH:
		pe.pe_extchannel = param;
		break;
	case DFS_PARAM_RELPWR_EN:
		pe.pe_enrelpwr = param;
		break;
	case DFS_PARAM_RELSTEP_EN:
		pe.pe_en_relstep_check = param;
		break;
	}

	radar->atd.ad_id = DFS_SET_THRESH | ATH_DIAG_IN;
	radar->atd.ad_out_data = NULL;
	radar->atd.ad_out_size = 0;
	radar->atd.ad_in_data = (caddr_t) &pe;
	radar->atd.ad_in_size = sizeof(HAL_PHYERR_PARAM);
	if (ioctl(radar->s, SIOCGATHPHYERR, &radar->atd) < 0)
		err(1, radar->atd.ad_name);
}