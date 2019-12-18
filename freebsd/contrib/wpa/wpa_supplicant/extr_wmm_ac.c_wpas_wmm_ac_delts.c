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
typedef  int /*<<< orphan*/  u8 ;
struct wpa_supplicant {int /*<<< orphan*/  bssid; struct wmm_tspec_element*** tspecs; int /*<<< orphan*/  wmm_ac_assoc_info; } ;
struct wmm_tspec_element {int dummy; } ;
typedef  enum ts_dir_idx { ____Placeholder_ts_dir_idx } ts_dir_idx ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  wmm_ac_del_ts_idx (struct wpa_supplicant*,int,int) ; 
 int wmm_ac_find_tsid (struct wpa_supplicant*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  wmm_ac_send_delts (struct wpa_supplicant*,struct wmm_tspec_element*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

int wpas_wmm_ac_delts(struct wpa_supplicant *wpa_s, u8 tsid)
{
	struct wmm_tspec_element tspec;
	int ac;
	enum ts_dir_idx dir;

	if (!wpa_s->wmm_ac_assoc_info) {
		wpa_printf(MSG_DEBUG,
			   "WMM AC: Failed to delete TS, WMM AC is disabled");
		return -1;
	}

	ac = wmm_ac_find_tsid(wpa_s, tsid, &dir);
	if (ac < 0) {
		wpa_printf(MSG_DEBUG, "WMM AC: TS does not exist");
		return -1;
	}

	tspec = *wpa_s->tspecs[ac][dir];

	wmm_ac_del_ts_idx(wpa_s, ac, dir);

	wmm_ac_send_delts(wpa_s, &tspec, wpa_s->bssid);

	return 0;
}