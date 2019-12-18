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
struct wpa_supplicant {scalar_t__ ext_work_in_progress; struct wpa_radio* radio; } ;
struct wpa_radio {int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ dl_list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct wpa_radio*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eloop_register_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wpa_radio*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radio_start_next_work ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

void radio_work_check_next(struct wpa_supplicant *wpa_s)
{
	struct wpa_radio *radio = wpa_s->radio;

	if (dl_list_empty(&radio->work))
		return;
	if (wpa_s->ext_work_in_progress) {
		wpa_printf(MSG_DEBUG,
			   "External radio work in progress - delay start of pending item");
		return;
	}
	eloop_cancel_timeout(radio_start_next_work, radio, NULL);
	eloop_register_timeout(0, 0, radio_start_next_work, radio, NULL);
}