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
struct eapol_sm {struct eapol_sm* ctx; int /*<<< orphan*/  eapReqData; struct eapol_sm* last_rx_key; int /*<<< orphan*/  eap_proxy; int /*<<< orphan*/  eap; } ;

/* Variables and functions */
 int /*<<< orphan*/  eap_peer_sm_deinit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_proxy_deinit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eapol_port_timers_tick ; 
 int /*<<< orphan*/  eapol_sm_step_timeout ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct eapol_sm*) ; 
 int /*<<< orphan*/  os_free (struct eapol_sm*) ; 
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ ) ; 

void eapol_sm_deinit(struct eapol_sm *sm)
{
	if (sm == NULL)
		return;
	eloop_cancel_timeout(eapol_sm_step_timeout, NULL, sm);
	eloop_cancel_timeout(eapol_port_timers_tick, NULL, sm);
	eap_peer_sm_deinit(sm->eap);
#ifdef CONFIG_EAP_PROXY
	eap_proxy_deinit(sm->eap_proxy);
#endif /* CONFIG_EAP_PROXY */
	os_free(sm->last_rx_key);
	wpabuf_free(sm->eapReqData);
	os_free(sm->ctx);
	os_free(sm);
}