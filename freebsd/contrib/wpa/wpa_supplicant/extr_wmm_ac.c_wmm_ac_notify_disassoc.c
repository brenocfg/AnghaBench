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
struct wpa_supplicant {int /*<<< orphan*/  wmm_ac_assoc_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  wmm_ac_deinit (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

void wmm_ac_notify_disassoc(struct wpa_supplicant *wpa_s)
{
	if (!wpa_s->wmm_ac_assoc_info)
		return;

	wmm_ac_deinit(wpa_s);
	wpa_printf(MSG_DEBUG, "WMM AC: WMM AC is disabled");
}