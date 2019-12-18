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
struct TYPE_2__ {int sched_obss_scan; int /*<<< orphan*/  obss_scan_int; } ;
struct wpa_supplicant {TYPE_1__ sme; int /*<<< orphan*/  current_bss; } ;
struct wpa_driver_scan_params {int low_priority; int /*<<< orphan*/  freqs; } ;
typedef  int /*<<< orphan*/  params ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  eloop_register_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void (*) (void*,void*),struct wpa_supplicant*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_memset (struct wpa_driver_scan_params*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_obss_scan_freqs_list (struct wpa_supplicant*,struct wpa_driver_scan_params*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ wpa_supplicant_trigger_scan (struct wpa_supplicant*,struct wpa_driver_scan_params*) ; 

__attribute__((used)) static void sme_obss_scan_timeout(void *eloop_ctx, void *timeout_ctx)
{
	struct wpa_supplicant *wpa_s = eloop_ctx;
	struct wpa_driver_scan_params params;

	if (!wpa_s->current_bss) {
		wpa_printf(MSG_DEBUG, "SME OBSS: Ignore scan request");
		return;
	}

	os_memset(&params, 0, sizeof(params));
	wpa_obss_scan_freqs_list(wpa_s, &params);
	params.low_priority = 1;
	wpa_printf(MSG_DEBUG, "SME OBSS: Request an OBSS scan");

	if (wpa_supplicant_trigger_scan(wpa_s, &params))
		wpa_printf(MSG_DEBUG, "SME OBSS: Failed to trigger scan");
	else
		wpa_s->sme.sched_obss_scan = 1;
	os_free(params.freqs);

	eloop_register_timeout(wpa_s->sme.obss_scan_int, 0,
			       sme_obss_scan_timeout, wpa_s, NULL);
}