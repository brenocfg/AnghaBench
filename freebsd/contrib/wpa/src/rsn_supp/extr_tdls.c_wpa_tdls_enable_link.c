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
typedef  int u32 ;
struct wpa_tdls_peer {int tpk_success; int lifetime; int /*<<< orphan*/  addr; scalar_t__ reconfig_key; scalar_t__ initiator; scalar_t__ tpk_in_progress; } ;
struct wpa_sm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  TDLS_ENABLE_LINK ; 
 int TDLS_TESTING_NO_TPK_EXPIRATION ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct wpa_sm*,struct wpa_tdls_peer*) ; 
 int /*<<< orphan*/  eloop_register_timeout (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wpa_sm*,struct wpa_tdls_peer*) ; 
 int tdls_testing ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int wpa_sm_tdls_oper (struct wpa_sm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ wpa_tdls_get_privacy (struct wpa_sm*) ; 
 scalar_t__ wpa_tdls_set_key (struct wpa_sm*,struct wpa_tdls_peer*) ; 
 int /*<<< orphan*/  wpa_tdls_tpk_timeout ; 

__attribute__((used)) static int wpa_tdls_enable_link(struct wpa_sm *sm, struct wpa_tdls_peer *peer)
{
	peer->tpk_success = 1;
	peer->tpk_in_progress = 0;
	eloop_cancel_timeout(wpa_tdls_tpk_timeout, sm, peer);
	if (wpa_tdls_get_privacy(sm)) {
		u32 lifetime = peer->lifetime;
		/*
		 * Start the initiator process a bit earlier to avoid race
		 * condition with the responder sending teardown request.
		 */
		if (lifetime > 3 && peer->initiator)
			lifetime -= 3;
		eloop_register_timeout(lifetime, 0, wpa_tdls_tpk_timeout,
				       sm, peer);
#ifdef CONFIG_TDLS_TESTING
		if (tdls_testing & TDLS_TESTING_NO_TPK_EXPIRATION) {
			wpa_printf(MSG_DEBUG,
				   "TDLS: Testing - disable TPK expiration");
			eloop_cancel_timeout(wpa_tdls_tpk_timeout, sm, peer);
		}
#endif /* CONFIG_TDLS_TESTING */
	}

	if (peer->reconfig_key && wpa_tdls_set_key(sm, peer) < 0) {
		wpa_printf(MSG_INFO, "TDLS: Could not configure key to the "
			   "driver");
		return -1;
	}
	peer->reconfig_key = 0;

	return wpa_sm_tdls_oper(sm, TDLS_ENABLE_LINK, peer->addr);
}