#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wpabuf {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  token; } ;
struct TYPE_3__ {int /*<<< orphan*/  dst_addr; } ;
struct wpa_supplicant {TYPE_2__ beacon_rep_data; TYPE_1__ rrm; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEASUREMENT_REPORT_MODE_REJECT_REFUSED ; 
 int /*<<< orphan*/  MEASURE_TYPE_BEACON ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  is_multicast_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/  wpas_clear_beacon_rep_data (struct wpa_supplicant*) ; 
 scalar_t__ wpas_rrm_report_elem (struct wpabuf**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpas_rrm_send_msr_report (struct wpa_supplicant*,struct wpabuf*) ; 

void wpas_rrm_refuse_request(struct wpa_supplicant *wpa_s)
{
	if (!is_multicast_ether_addr(wpa_s->rrm.dst_addr)) {
		struct wpabuf *buf = NULL;

		if (wpas_rrm_report_elem(&buf, wpa_s->beacon_rep_data.token,
					 MEASUREMENT_REPORT_MODE_REJECT_REFUSED,
					 MEASURE_TYPE_BEACON, NULL, 0)) {
			wpa_printf(MSG_ERROR, "RRM: Memory allocation failed");
			wpabuf_free(buf);
			return;
		}

		wpas_rrm_send_msr_report(wpa_s, buf);
		wpabuf_free(buf);
	}

	wpas_clear_beacon_rep_data(wpa_s);
}