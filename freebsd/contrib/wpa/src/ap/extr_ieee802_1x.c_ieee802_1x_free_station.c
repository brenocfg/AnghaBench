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
struct sta_info {struct eapol_state_machine* eapol_sm; TYPE_1__* pending_eapol_rx; } ;
struct hostapd_data {int dummy; } ;
struct eapol_state_machine {int /*<<< orphan*/  radius_class; int /*<<< orphan*/  last_recv_radius; } ;
struct TYPE_2__ {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  eapol_auth_free (struct eapol_state_machine*) ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct hostapd_data*,struct sta_info*) ; 
 int /*<<< orphan*/  ieee802_1x_wnm_notif_send ; 
 int /*<<< orphan*/  os_free (TYPE_1__*) ; 
 int /*<<< orphan*/  radius_free_class (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radius_msg_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ ) ; 

void ieee802_1x_free_station(struct hostapd_data *hapd, struct sta_info *sta)
{
	struct eapol_state_machine *sm = sta->eapol_sm;

#ifdef CONFIG_HS20
	eloop_cancel_timeout(ieee802_1x_wnm_notif_send, hapd, sta);
#endif /* CONFIG_HS20 */

	if (sta->pending_eapol_rx) {
		wpabuf_free(sta->pending_eapol_rx->buf);
		os_free(sta->pending_eapol_rx);
		sta->pending_eapol_rx = NULL;
	}

	if (sm == NULL)
		return;

	sta->eapol_sm = NULL;

#ifndef CONFIG_NO_RADIUS
	radius_msg_free(sm->last_recv_radius);
	radius_free_class(&sm->radius_class);
#endif /* CONFIG_NO_RADIUS */

	eapol_auth_free(sm);
}