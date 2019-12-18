#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct wpabuf {int dummy; } ;
struct TYPE_4__ {int next_neighbor_rep_token; int /*<<< orphan*/ * neighbor_rep_cb_ctx; int /*<<< orphan*/  (* notify_neighbor_rep ) (int /*<<< orphan*/ *,struct wpabuf*) ;} ;
struct wpa_supplicant {TYPE_1__ rrm; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/  (*) (TYPE_1__*,int /*<<< orphan*/ *),TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,struct wpabuf*) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 struct wpabuf* wpabuf_alloc (size_t) ; 
 int /*<<< orphan*/  wpabuf_put_data (struct wpabuf*,int const*,size_t) ; 
 int /*<<< orphan*/  wpas_rrm_neighbor_rep_timeout_handler (TYPE_1__*,int /*<<< orphan*/ *) ; 

void wpas_rrm_process_neighbor_rep(struct wpa_supplicant *wpa_s,
				   const u8 *report, size_t report_len)
{
	struct wpabuf *neighbor_rep;

	wpa_hexdump(MSG_DEBUG, "RRM: New Neighbor Report", report, report_len);
	if (report_len < 1)
		return;

	if (report[0] != wpa_s->rrm.next_neighbor_rep_token - 1) {
		wpa_printf(MSG_DEBUG,
			   "RRM: Discarding neighbor report with token %d (expected %d)",
			   report[0], wpa_s->rrm.next_neighbor_rep_token - 1);
		return;
	}

	eloop_cancel_timeout(wpas_rrm_neighbor_rep_timeout_handler, &wpa_s->rrm,
			     NULL);

	if (!wpa_s->rrm.notify_neighbor_rep) {
		wpa_printf(MSG_ERROR, "RRM: Unexpected neighbor report");
		return;
	}

	/* skipping the first byte, which is only an id (dialog token) */
	neighbor_rep = wpabuf_alloc(report_len - 1);
	if (!neighbor_rep) {
		wpas_rrm_neighbor_rep_timeout_handler(&wpa_s->rrm, NULL);
		return;
	}
	wpabuf_put_data(neighbor_rep, report + 1, report_len - 1);
	wpa_printf(MSG_DEBUG, "RRM: Notifying neighbor report (token = %d)",
		   report[0]);
	wpa_s->rrm.notify_neighbor_rep(wpa_s->rrm.neighbor_rep_cb_ctx,
				       neighbor_rep);
	wpa_s->rrm.notify_neighbor_rep = NULL;
	wpa_s->rrm.neighbor_rep_cb_ctx = NULL;
}