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
struct eapol_sm {int /*<<< orphan*/  eap_proxy; int /*<<< orphan*/  eap; int /*<<< orphan*/ * eapReqData; int /*<<< orphan*/ * last_rx_key; } ;

/* Variables and functions */
 int /*<<< orphan*/  eap_proxy_sm_abort (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_sm_abort (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void eapol_sm_abortSupp(struct eapol_sm *sm)
{
	/* release system resources that may have been allocated for the
	 * authentication session */
	os_free(sm->last_rx_key);
	sm->last_rx_key = NULL;
	wpabuf_free(sm->eapReqData);
	sm->eapReqData = NULL;
	eap_sm_abort(sm->eap);
#ifdef CONFIG_EAP_PROXY
	eap_proxy_sm_abort(sm->eap_proxy);
#endif /* CONFIG_EAP_PROXY */
}