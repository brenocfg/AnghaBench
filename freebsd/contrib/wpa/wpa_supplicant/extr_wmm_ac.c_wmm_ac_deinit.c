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
struct wpa_supplicant {int /*<<< orphan*/ * wmm_ac_assoc_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  TS_DIR_IDX_ALL ; 
 int WMM_AC_NUM ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmm_ac_del_req (struct wpa_supplicant*,int) ; 
 int /*<<< orphan*/  wmm_ac_del_ts (struct wpa_supplicant*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wmm_ac_deinit(struct wpa_supplicant *wpa_s)
{
	int i;

	for (i = 0; i < WMM_AC_NUM; i++)
		wmm_ac_del_ts(wpa_s, i, TS_DIR_IDX_ALL);

	/* delete pending add_ts request */
	wmm_ac_del_req(wpa_s, 1);

	os_free(wpa_s->wmm_ac_assoc_info);
	wpa_s->wmm_ac_assoc_info = NULL;
}