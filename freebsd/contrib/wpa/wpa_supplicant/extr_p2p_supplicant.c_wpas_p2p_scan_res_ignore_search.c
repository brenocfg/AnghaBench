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
struct wpa_supplicant {TYPE_1__* global; struct wpa_radio_work* p2p_scan_work; } ;
struct wpa_scan_results {int dummy; } ;
struct wpa_radio_work {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * p2p; scalar_t__ p2p_disabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  p2p_scan_res_handled (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radio_work_done (struct wpa_radio_work*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void wpas_p2p_scan_res_ignore_search(struct wpa_supplicant *wpa_s,
					    struct wpa_scan_results *scan_res)
{
	wpa_printf(MSG_DEBUG, "P2P: Ignore scan results");

	if (wpa_s->p2p_scan_work) {
		struct wpa_radio_work *work = wpa_s->p2p_scan_work;
		wpa_s->p2p_scan_work = NULL;
		radio_work_done(work);
	}

	if (wpa_s->global->p2p_disabled || wpa_s->global->p2p == NULL)
		return;

	/*
	 * Indicate that results have been processed so that the P2P module can
	 * continue pending tasks.
	 */
	p2p_scan_res_handled(wpa_s->global->p2p);
}