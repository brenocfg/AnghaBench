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
typedef  int /*<<< orphan*/  u8 ;
struct wpabuf {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dst_addr; int /*<<< orphan*/  token; int /*<<< orphan*/  rrm_used; } ;
struct wpa_supplicant {scalar_t__ wpa_state; TYPE_1__ rrm; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  MSG_INFO ; 
 scalar_t__ WPA_COMPLETED ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 struct wpabuf* wpas_rrm_process_msr_req_elems (struct wpa_supplicant*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpas_rrm_send_msr_report (struct wpa_supplicant*,struct wpabuf*) ; 

void wpas_rrm_handle_radio_measurement_request(struct wpa_supplicant *wpa_s,
					       const u8 *src, const u8 *dst,
					       const u8 *frame, size_t len)
{
	struct wpabuf *report;

	if (wpa_s->wpa_state != WPA_COMPLETED) {
		wpa_printf(MSG_INFO,
			   "RRM: Ignoring radio measurement request: Not associated");
		return;
	}

	if (!wpa_s->rrm.rrm_used) {
		wpa_printf(MSG_INFO,
			   "RRM: Ignoring radio measurement request: Not RRM network");
		return;
	}

	if (len < 3) {
		wpa_printf(MSG_INFO,
			   "RRM: Ignoring too short radio measurement request");
		return;
	}

	wpa_s->rrm.token = *frame;
	os_memcpy(wpa_s->rrm.dst_addr, dst, ETH_ALEN);

	/* Number of repetitions is not supported */

	report = wpas_rrm_process_msr_req_elems(wpa_s, frame + 3, len - 3);
	if (!report)
		return;

	wpas_rrm_send_msr_report(wpa_s, report);
	wpabuf_free(report);
}