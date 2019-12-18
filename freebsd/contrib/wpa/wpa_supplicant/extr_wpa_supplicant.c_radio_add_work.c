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
struct wpa_supplicant {int drv_flags; struct wpa_radio* radio; } ;
struct wpa_radio_work {unsigned int freq; char const* type; void (* cb ) (struct wpa_radio_work*,int) ;int /*<<< orphan*/  list; void* bands; void* ctx; struct wpa_supplicant* wpa_s; int /*<<< orphan*/  time; } ;
struct wpa_radio {int /*<<< orphan*/  num_active_works; int /*<<< orphan*/  work; } ;
struct wpa_driver_scan_params {int /*<<< orphan*/ * freqs; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_ACTIVE_WORKS ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int WPA_DRIVER_FLAGS_OFFCHANNEL_SIMULTANEOUS ; 
 int /*<<< orphan*/  dl_list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dl_list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int dl_list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_get_reltime (int /*<<< orphan*/ *) ; 
 scalar_t__ os_strcmp (char const*,char*) ; 
 struct wpa_radio_work* os_zalloc (int) ; 
 int /*<<< orphan*/  radio_work_check_next (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpa_dbg (struct wpa_supplicant*,int /*<<< orphan*/ ,char*,...) ; 
 void* wpas_freq_to_band (unsigned int) ; 
 void* wpas_get_bands (struct wpa_supplicant*,int /*<<< orphan*/ *) ; 

int radio_add_work(struct wpa_supplicant *wpa_s, unsigned int freq,
		   const char *type, int next,
		   void (*cb)(struct wpa_radio_work *work, int deinit),
		   void *ctx)
{
	struct wpa_radio *radio = wpa_s->radio;
	struct wpa_radio_work *work;
	int was_empty;

	work = os_zalloc(sizeof(*work));
	if (work == NULL)
		return -1;
	wpa_dbg(wpa_s, MSG_DEBUG, "Add radio work '%s'@%p", type, work);
	os_get_reltime(&work->time);
	work->freq = freq;
	work->type = type;
	work->wpa_s = wpa_s;
	work->cb = cb;
	work->ctx = ctx;

	if (freq)
		work->bands = wpas_freq_to_band(freq);
	else if (os_strcmp(type, "scan") == 0 ||
		 os_strcmp(type, "p2p-scan") == 0)
		work->bands = wpas_get_bands(wpa_s,
					     ((struct wpa_driver_scan_params *)
					      ctx)->freqs);
	else
		work->bands = wpas_get_bands(wpa_s, NULL);

	was_empty = dl_list_empty(&wpa_s->radio->work);
	if (next)
		dl_list_add(&wpa_s->radio->work, &work->list);
	else
		dl_list_add_tail(&wpa_s->radio->work, &work->list);
	if (was_empty) {
		wpa_dbg(wpa_s, MSG_DEBUG, "First radio work item in the queue - schedule start immediately");
		radio_work_check_next(wpa_s);
	} else if ((wpa_s->drv_flags & WPA_DRIVER_FLAGS_OFFCHANNEL_SIMULTANEOUS)
		   && radio->num_active_works < MAX_ACTIVE_WORKS) {
		wpa_dbg(wpa_s, MSG_DEBUG,
			"Try to schedule a radio work (num_active_works=%u)",
			radio->num_active_works);
		radio_work_check_next(wpa_s);
	}

	return 0;
}