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
struct wpa_sm {scalar_t__ key_mgmt; TYPE_1__* ctx; int /*<<< orphan*/  pmk_len; int /*<<< orphan*/  pmk; int /*<<< orphan*/  xxkey_len; int /*<<< orphan*/  xxkey; } ;
struct TYPE_2__ {int /*<<< orphan*/  msg_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ WPA_KEY_MGMT_FT_IEEE8021X ; 
 int /*<<< orphan*/  wpa_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ wpa_sm_key_mgmt_set_pmk (struct wpa_sm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wpa_supplicant_key_mgmt_set_pmk(struct wpa_sm *sm)
{
#ifdef CONFIG_IEEE80211R
	if (sm->key_mgmt == WPA_KEY_MGMT_FT_IEEE8021X) {
		if (wpa_sm_key_mgmt_set_pmk(sm, sm->xxkey, sm->xxkey_len))
			wpa_dbg(sm->ctx->msg_ctx, MSG_DEBUG,
				"RSN: Cannot set low order 256 bits of MSK for key management offload");
	} else {
#endif /* CONFIG_IEEE80211R */
		if (wpa_sm_key_mgmt_set_pmk(sm, sm->pmk, sm->pmk_len))
			wpa_dbg(sm->ctx->msg_ctx, MSG_DEBUG,
				"RSN: Cannot set PMK for key management offload");
#ifdef CONFIG_IEEE80211R
	}
#endif /* CONFIG_IEEE80211R */
}