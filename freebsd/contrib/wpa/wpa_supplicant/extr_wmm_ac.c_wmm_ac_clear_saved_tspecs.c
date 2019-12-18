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
struct wpa_supplicant {scalar_t__ last_tspecs_count; int /*<<< orphan*/ * last_tspecs; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

void wmm_ac_clear_saved_tspecs(struct wpa_supplicant *wpa_s)
{
	if (wpa_s->last_tspecs) {
		wpa_printf(MSG_DEBUG, "WMM AC: Clear saved tspecs");
		os_free(wpa_s->last_tspecs);
		wpa_s->last_tspecs = NULL;
		wpa_s->last_tspecs_count = 0;
	}
}