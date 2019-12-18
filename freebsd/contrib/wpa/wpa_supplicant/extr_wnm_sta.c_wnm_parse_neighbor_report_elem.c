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
typedef  int u8 ;
struct neighbor_report {int tsf_present; int country_present; int preference; int preference_present; int bss_term_present; int bearing_present; int rm_capab_present; TYPE_1__* mul_bssid; int /*<<< orphan*/  rm_capab; TYPE_1__* meas_pilot; void* rel_height; int /*<<< orphan*/  distance; void* bearing; void* bss_term_dur; int /*<<< orphan*/  bss_term_tsf; int /*<<< orphan*/  country; void* beacon_int; void* tsf_offset; } ;
struct multiple_bssid {int dummy; } ;
struct measurement_pilot {int dummy; } ;
struct TYPE_2__ {int measurement_pilot; int max_bssid_indicator; int /*<<< orphan*/  subelems; int /*<<< orphan*/  subelem_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
#define  WNM_NEIGHBOR_BEARING 135 
#define  WNM_NEIGHBOR_BSS_TERMINATION_DURATION 134 
#define  WNM_NEIGHBOR_BSS_TRANSITION_CANDIDATE 133 
#define  WNM_NEIGHBOR_CONDENSED_COUNTRY_STRING 132 
#define  WNM_NEIGHBOR_MEASUREMENT_PILOT 131 
#define  WNM_NEIGHBOR_MULTIPLE_BSSID 130 
#define  WNM_NEIGHBOR_RRM_ENABLED_CAPABILITIES 129 
#define  WNM_NEIGHBOR_TSF 128 
 void* WPA_GET_LE16 (int const*) ; 
 int /*<<< orphan*/  WPA_GET_LE32 (int const*) ; 
 int /*<<< orphan*/  WPA_GET_LE64 (int const*) ; 
 int /*<<< orphan*/  os_free (TYPE_1__*) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int const*,int) ; 
 void* os_zalloc (int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void wnm_parse_neighbor_report_elem(struct neighbor_report *rep,
					   u8 id, u8 elen, const u8 *pos)
{
	switch (id) {
	case WNM_NEIGHBOR_TSF:
		if (elen < 2 + 2) {
			wpa_printf(MSG_DEBUG, "WNM: Too short TSF");
			break;
		}
		rep->tsf_offset = WPA_GET_LE16(pos);
		rep->beacon_int = WPA_GET_LE16(pos + 2);
		rep->tsf_present = 1;
		break;
	case WNM_NEIGHBOR_CONDENSED_COUNTRY_STRING:
		if (elen < 2) {
			wpa_printf(MSG_DEBUG, "WNM: Too short condensed "
				   "country string");
			break;
		}
		os_memcpy(rep->country, pos, 2);
		rep->country_present = 1;
		break;
	case WNM_NEIGHBOR_BSS_TRANSITION_CANDIDATE:
		if (elen < 1) {
			wpa_printf(MSG_DEBUG, "WNM: Too short BSS transition "
				   "candidate");
			break;
		}
		rep->preference = pos[0];
		rep->preference_present = 1;
		break;
	case WNM_NEIGHBOR_BSS_TERMINATION_DURATION:
		if (elen < 10) {
			wpa_printf(MSG_DEBUG,
				   "WNM: Too short BSS termination duration");
			break;
		}
		rep->bss_term_tsf = WPA_GET_LE64(pos);
		rep->bss_term_dur = WPA_GET_LE16(pos + 8);
		rep->bss_term_present = 1;
		break;
	case WNM_NEIGHBOR_BEARING:
		if (elen < 8) {
			wpa_printf(MSG_DEBUG, "WNM: Too short neighbor "
				   "bearing");
			break;
		}
		rep->bearing = WPA_GET_LE16(pos);
		rep->distance = WPA_GET_LE32(pos + 2);
		rep->rel_height = WPA_GET_LE16(pos + 2 + 4);
		rep->bearing_present = 1;
		break;
	case WNM_NEIGHBOR_MEASUREMENT_PILOT:
		if (elen < 1) {
			wpa_printf(MSG_DEBUG, "WNM: Too short measurement "
				   "pilot");
			break;
		}
		os_free(rep->meas_pilot);
		rep->meas_pilot = os_zalloc(sizeof(struct measurement_pilot));
		if (rep->meas_pilot == NULL)
			break;
		rep->meas_pilot->measurement_pilot = pos[0];
		rep->meas_pilot->subelem_len = elen - 1;
		os_memcpy(rep->meas_pilot->subelems, pos + 1, elen - 1);
		break;
	case WNM_NEIGHBOR_RRM_ENABLED_CAPABILITIES:
		if (elen < 5) {
			wpa_printf(MSG_DEBUG, "WNM: Too short RRM enabled "
				   "capabilities");
			break;
		}
		os_memcpy(rep->rm_capab, pos, 5);
		rep->rm_capab_present = 1;
		break;
	case WNM_NEIGHBOR_MULTIPLE_BSSID:
		if (elen < 1) {
			wpa_printf(MSG_DEBUG, "WNM: Too short multiple BSSID");
			break;
		}
		os_free(rep->mul_bssid);
		rep->mul_bssid = os_zalloc(sizeof(struct multiple_bssid));
		if (rep->mul_bssid == NULL)
			break;
		rep->mul_bssid->max_bssid_indicator = pos[0];
		rep->mul_bssid->subelem_len = elen - 1;
		os_memcpy(rep->mul_bssid->subelems, pos + 1, elen - 1);
		break;
	}
}