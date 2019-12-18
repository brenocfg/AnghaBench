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
struct wpa_sm {scalar_t__ pmk_r1_len; int /*<<< orphan*/ * pmk_r1; scalar_t__ pmk_r0_len; int /*<<< orphan*/ * pmk_r0; scalar_t__ xxkey_len; int /*<<< orphan*/ * xxkey; int /*<<< orphan*/  igtk_wnm_sleep; int /*<<< orphan*/  igtk; int /*<<< orphan*/  gtk_wnm_sleep; int /*<<< orphan*/  gtk; int /*<<< orphan*/  tptk; int /*<<< orphan*/  ptk; int /*<<< orphan*/ * pmk; scalar_t__ pmk_len; scalar_t__ tptk_set; scalar_t__ ptk_set; TYPE_1__* ctx; } ;
struct TYPE_2__ {int /*<<< orphan*/  msg_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

void wpa_sm_drop_sa(struct wpa_sm *sm)
{
	wpa_dbg(sm->ctx->msg_ctx, MSG_DEBUG, "WPA: Clear old PMK and PTK");
	sm->ptk_set = 0;
	sm->tptk_set = 0;
	sm->pmk_len = 0;
	os_memset(sm->pmk, 0, sizeof(sm->pmk));
	os_memset(&sm->ptk, 0, sizeof(sm->ptk));
	os_memset(&sm->tptk, 0, sizeof(sm->tptk));
	os_memset(&sm->gtk, 0, sizeof(sm->gtk));
	os_memset(&sm->gtk_wnm_sleep, 0, sizeof(sm->gtk_wnm_sleep));
#ifdef CONFIG_IEEE80211W
	os_memset(&sm->igtk, 0, sizeof(sm->igtk));
	os_memset(&sm->igtk_wnm_sleep, 0, sizeof(sm->igtk_wnm_sleep));
#endif /* CONFIG_IEEE80211W */
#ifdef CONFIG_IEEE80211R
	os_memset(sm->xxkey, 0, sizeof(sm->xxkey));
	sm->xxkey_len = 0;
	os_memset(sm->pmk_r0, 0, sizeof(sm->pmk_r0));
	sm->pmk_r0_len = 0;
	os_memset(sm->pmk_r1, 0, sizeof(sm->pmk_r1));
	sm->pmk_r1_len = 0;
#endif /* CONFIG_IEEE80211R */
}