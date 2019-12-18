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
typedef  int u8 ;
struct sta_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
#define  WFA_WNM_NOTIF_SUBELEM_CELL_DATA_CAPA 129 
#define  WFA_WNM_NOTIF_SUBELEM_NON_PREF_CHAN_REPORT 128 
 int /*<<< orphan*/  mbo_ap_parse_non_pref_chan (struct sta_info*,int const*,size_t) ; 
 int /*<<< orphan*/  mbo_ap_sta_free (struct sta_info*) ; 
 int /*<<< orphan*/  mbo_ap_wnm_notif_req_cell_capa (struct sta_info*,int const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void mbo_ap_wnm_notif_req_elem(struct sta_info *sta, u8 type,
				      const u8 *buf, size_t len,
				      int *first_non_pref_chan)
{
	switch (type) {
	case WFA_WNM_NOTIF_SUBELEM_NON_PREF_CHAN_REPORT:
		if (*first_non_pref_chan) {
			/*
			 * Need to free the previously stored entries now to
			 * allow the update to replace all entries.
			 */
			*first_non_pref_chan = 0;
			mbo_ap_sta_free(sta);
		}
		mbo_ap_parse_non_pref_chan(sta, buf, len);
		break;
	case WFA_WNM_NOTIF_SUBELEM_CELL_DATA_CAPA:
		mbo_ap_wnm_notif_req_cell_capa(sta, buf, len);
		break;
	default:
		wpa_printf(MSG_DEBUG,
			   "MBO: Ignore unknown WNM Notification WFA subelement %u",
			   type);
		break;
	}
}