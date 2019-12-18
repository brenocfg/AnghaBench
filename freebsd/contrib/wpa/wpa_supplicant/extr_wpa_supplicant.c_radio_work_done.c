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
struct wpa_supplicant {int dummy; } ;
struct wpa_radio_work {unsigned int started; int /*<<< orphan*/  type; int /*<<< orphan*/  time; struct wpa_supplicant* wpa_s; } ;
struct os_reltime {int /*<<< orphan*/  usec; int /*<<< orphan*/  sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  os_get_reltime (struct os_reltime*) ; 
 int /*<<< orphan*/  os_reltime_sub (struct os_reltime*,int /*<<< orphan*/ *,struct os_reltime*) ; 
 int /*<<< orphan*/  radio_work_check_next (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  radio_work_free (struct wpa_radio_work*) ; 
 int /*<<< orphan*/  wpa_dbg (struct wpa_supplicant*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct wpa_radio_work*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void radio_work_done(struct wpa_radio_work *work)
{
	struct wpa_supplicant *wpa_s = work->wpa_s;
	struct os_reltime now, diff;
	unsigned int started = work->started;

	os_get_reltime(&now);
	os_reltime_sub(&now, &work->time, &diff);
	wpa_dbg(wpa_s, MSG_DEBUG, "Radio work '%s'@%p %s in %ld.%06ld seconds",
		work->type, work, started ? "done" : "canceled",
		diff.sec, diff.usec);
	radio_work_free(work);
	if (started)
		radio_work_check_next(wpa_s);
}