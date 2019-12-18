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
struct wpa_supplicant {int /*<<< orphan*/  last_tspecs_count; int /*<<< orphan*/ *** tspecs; int /*<<< orphan*/ * last_tspecs; int /*<<< orphan*/  wmm_ac_assoc_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int TS_DIR_IDX_COUNT ; 
 int WMM_AC_NUM ; 
 int /*<<< orphan*/ * os_calloc (int,int) ; 
 int /*<<< orphan*/  wmm_ac_clear_saved_tspecs (struct wpa_supplicant*) ; 
 int wmm_ac_get_tspecs_count (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

void wmm_ac_save_tspecs(struct wpa_supplicant *wpa_s)
{
	int ac, dir, tspecs_count;

	wpa_printf(MSG_DEBUG, "WMM AC: Save last configured tspecs");

	if (!wpa_s->wmm_ac_assoc_info)
		return;

	tspecs_count = wmm_ac_get_tspecs_count(wpa_s);
	if (!tspecs_count) {
		wpa_printf(MSG_DEBUG, "WMM AC: No configured TSPECs");
		return;
	}

	wpa_printf(MSG_DEBUG, "WMM AC: Saving tspecs");

	wmm_ac_clear_saved_tspecs(wpa_s);
	wpa_s->last_tspecs = os_calloc(tspecs_count,
				       sizeof(*wpa_s->last_tspecs));
	if (!wpa_s->last_tspecs) {
		wpa_printf(MSG_ERROR, "WMM AC: Failed to save tspecs!");
		return;
	}

	for (ac = 0; ac < WMM_AC_NUM; ac++) {
		for (dir = 0; dir < TS_DIR_IDX_COUNT; dir++) {
			if (!wpa_s->tspecs[ac][dir])
				continue;

			wpa_s->last_tspecs[wpa_s->last_tspecs_count++] =
				*wpa_s->tspecs[ac][dir];
		}
	}

	wpa_printf(MSG_DEBUG, "WMM AC: Successfully saved %d TSPECs",
		   wpa_s->last_tspecs_count);
}