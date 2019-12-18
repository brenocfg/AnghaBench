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
struct TYPE_2__ {int timer; int /*<<< orphan*/  buf_len; int /*<<< orphan*/ * buf; int /*<<< orphan*/  peer_capab; int /*<<< orphan*/  status_code; int /*<<< orphan*/  dialog_token; int /*<<< orphan*/  action_code; int /*<<< orphan*/  dest; scalar_t__ count; } ;
struct wpa_tdls_peer {TYPE_1__ sm_tmr; int /*<<< orphan*/  initiator; } ;
struct wpa_sm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  WLAN_REASON_TDLS_TEARDOWN_UNSPECIFIED ; 
 int /*<<< orphan*/  eloop_cancel_timeout (void (*) (void*,void*),struct wpa_sm*,struct wpa_tdls_peer*) ; 
 int /*<<< orphan*/  eloop_register_timeout (int,int,void (*) (void*,void*),struct wpa_sm*,struct wpa_tdls_peer*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpa_tdls_do_teardown (struct wpa_sm*,struct wpa_tdls_peer*,int /*<<< orphan*/ ) ; 
 scalar_t__ wpa_tdls_send_tpk_msg (struct wpa_sm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wpa_tdls_tpk_retry_timeout(void *eloop_ctx, void *timeout_ctx)
{

	struct wpa_sm *sm = eloop_ctx;
	struct wpa_tdls_peer *peer = timeout_ctx;

	if (peer->sm_tmr.count) {
		peer->sm_tmr.count--;

		wpa_printf(MSG_INFO, "TDLS: Retrying sending of message "
			   "(action_code=%u)",
			   peer->sm_tmr.action_code);

		if (peer->sm_tmr.buf == NULL) {
			wpa_printf(MSG_INFO, "TDLS: No retry buffer available "
				   "for action_code=%u",
				   peer->sm_tmr.action_code);
			eloop_cancel_timeout(wpa_tdls_tpk_retry_timeout, sm,
					     peer);
			return;
		}

		/* resend TPK Handshake Message to Peer */
		if (wpa_tdls_send_tpk_msg(sm, peer->sm_tmr.dest,
					  peer->sm_tmr.action_code,
					  peer->sm_tmr.dialog_token,
					  peer->sm_tmr.status_code,
					  peer->sm_tmr.peer_capab,
					  peer->initiator,
					  peer->sm_tmr.buf,
					  peer->sm_tmr.buf_len)) {
			wpa_printf(MSG_INFO, "TDLS: Failed to retry "
				   "transmission");
		}

		eloop_cancel_timeout(wpa_tdls_tpk_retry_timeout, sm, peer);
		eloop_register_timeout(peer->sm_tmr.timer / 1000,
				       (peer->sm_tmr.timer % 1000) * 1000,
				       wpa_tdls_tpk_retry_timeout, sm, peer);
	} else {
		eloop_cancel_timeout(wpa_tdls_tpk_retry_timeout, sm, peer);

		wpa_printf(MSG_DEBUG, "TDLS: Sending Teardown Request");
		wpa_tdls_do_teardown(sm, peer,
				     WLAN_REASON_TDLS_TEARDOWN_UNSPECIFIED);
	}
}