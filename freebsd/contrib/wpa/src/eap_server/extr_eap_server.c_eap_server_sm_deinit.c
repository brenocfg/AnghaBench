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
struct TYPE_4__ {int /*<<< orphan*/  aaaEapKeyDataLen; int /*<<< orphan*/  aaaEapKeyData; int /*<<< orphan*/  aaaEapRespData; int /*<<< orphan*/  aaaEapReqData; int /*<<< orphan*/  eapRespData; struct eap_sm* eapSessionId; int /*<<< orphan*/  eapKeyDataLen; int /*<<< orphan*/  eapKeyData; int /*<<< orphan*/  eapReqData; } ;
struct eap_sm {int /*<<< orphan*/  assoc_p2p_ie; int /*<<< orphan*/  assoc_wps_ie; int /*<<< orphan*/  user; TYPE_2__ eap_if; struct eap_sm* eap_fast_a_id_info; struct eap_sm* eap_fast_a_id; struct eap_sm* pac_opaque_encr_key; struct eap_sm* serial_num; struct eap_sm* identity; int /*<<< orphan*/  lastReqData; scalar_t__ eap_method_priv; TYPE_1__* m; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* reset ) (struct eap_sm*,scalar_t__) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  bin_clear_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_user_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_free (struct eap_sm*) ; 
 int /*<<< orphan*/  stub1 (struct eap_sm*,scalar_t__) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ ) ; 

void eap_server_sm_deinit(struct eap_sm *sm)
{
	if (sm == NULL)
		return;
	wpa_printf(MSG_DEBUG, "EAP: Server state machine removed");
	if (sm->m && sm->eap_method_priv)
		sm->m->reset(sm, sm->eap_method_priv);
	wpabuf_free(sm->eap_if.eapReqData);
	bin_clear_free(sm->eap_if.eapKeyData, sm->eap_if.eapKeyDataLen);
	os_free(sm->eap_if.eapSessionId);
	wpabuf_free(sm->lastReqData);
	wpabuf_free(sm->eap_if.eapRespData);
	os_free(sm->identity);
	os_free(sm->serial_num);
	os_free(sm->pac_opaque_encr_key);
	os_free(sm->eap_fast_a_id);
	os_free(sm->eap_fast_a_id_info);
	wpabuf_free(sm->eap_if.aaaEapReqData);
	wpabuf_free(sm->eap_if.aaaEapRespData);
	bin_clear_free(sm->eap_if.aaaEapKeyData, sm->eap_if.aaaEapKeyDataLen);
	eap_user_free(sm->user);
	wpabuf_free(sm->assoc_wps_ie);
	wpabuf_free(sm->assoc_p2p_ie);
	os_free(sm);
}